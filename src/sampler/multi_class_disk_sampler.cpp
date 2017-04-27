//
// Created by lxs on 17-4-25.
//

#include "multi_class_disk_sampler.h"
#include "../util/math_func.h"
#include <algorithm>
#include <utility>
#include <functional>

#define R_EQUAL_MIN 1e-5

void MultiClassDiskSampler::generate_samples()
{
    for(int i = 0; i < class_n; i++) {
        image_samples[i].clear();
        image_sp_pw[i] = 0;
        image_sample_index[i] = 0;
    }
}


bool distance_compare(std::pair<float, int> d1, std::pair<float, int> d2)
{
    return d1.first >= d2.first;
}

float MultiClassDiskSampler::build_matrix_r()
{
    std::pair<float, int> *d_order = new std::pair<float, int>[class_n];
    std::vector<int> P;
    P.reserve(class_n);
    for(int i = 0; i < class_n; i++) {
        r[i][i] = distance[i];
        d_order[i].first = distance[i];
        d_order[i].second = i;
    }
    std::sort(d_order, d_order + class_n, distance_compare);
    int d_order_index[2] = {0, 0};
    for(int i = 0, n = class_n - 1; i < n; i++) {
        if(std::abs(d_order[i].first - d_order[i + 1].first) < R_EQUAL_MIN)
            d_order_index[1]++;
        else {
            P.push_back(d_order_index[0]);
            P.push_back(d_order_index[1]);
            d_order_index[1] = d_order_index[0] = d_order_index[1] + 1;
        }
    }
    P.push_back(d_order_index[0]);
    P.push_back(d_order_index[1]);

    std::vector<int> C, Pk;
    C.reserve((unsigned long)class_n);
    float D = 0.f;
    for(int k = 0, P_size = (int)P.size()/2; k < P_size; k++)
    {
        for(int index = P[2 * k], n = P[2 * k + 1]; index <= n; index++)
            Pk.push_back(d_order[index].second);
        C.insert(C.end(), Pk.begin(), Pk.end());
        for(int i : Pk)
            D += 1.f/(distance[i] * distance[i]);
        for(int i : Pk) {
            for(int j : C) {
                if(i != j)
                    r[i][j] = r[j][i] = 1.f/std::sqrt(D);
            }
        }
        Pk.clear();
    }
    float max_dis = d_order[class_n/2].first;
    delete []d_order;
    return max_dis;
}

void MultiClassDiskSampler::calculate_target_sample(float max_dis)
{
    int N_sum = (int)(1.f / (max_dis * max_dis) + 0.5f);
    float rate_sum = 0.f;
    float *rate = new float[class_n];
    for(int i = 0; i < class_n; i++) {
        rate[i] = 1.f/(distance[i]*distance[i]);
        rate_sum += rate[i];
    }
    rate_sum = N_sum/rate_sum;
    for(int i = 0; i < class_n; i++) {
        target_sample_n[i] = (int)(rate[i]*rate_sum);
        target_sample_n_1[i] = 1.f/target_sample_n[i];
        target_sample_sum += target_sample_n[i];
    }
    delete []rate;
}

#define ADD_FAIL_TIMES 10

#define DIS(p1,p2) std::sqrt((p1[0]-p2[0])*(p1[0]-p2[0])+(p1[1]-p2[1])*(p1[1]-p2[1]))


// c: class, p: sample
void MultiClassDiskSampler::add_new_sample(int c, std::array<float, 2> &p, float *fill_rate, int *order)
{
    image_samples[c].push_back(p);
    fill_rate[c] += target_sample_n_1[c];
    // 使order始终保持从小到大排列
    for(int i = c + 1; i < class_n; i++)
        if(fill_rate[c] > fill_rate[i])
            std::swap(order[i], order[c]);
        else
            break;
}

void MultiClassDiskSampler::hard_dart_throwing()
{
    int add_fail_n = 0, n_cur = 0;
    int *fill_rate_order = new int[class_n];
    for(int i = 0; i < class_n; i++)
        fill_rate_order[i] = i;
    float *fill_rate = new float[class_n];
    std::array<float, 2> sample;
    update_random_seed();
    int class_s;
    std::vector<std::pair<std::vector<std::array<float, 2>>*, int>> ns;
    ns.reserve((unsigned long)target_sample_sum);
//    std::vector<std::array<float, 2>> *sample_class;
    bool if_add = true;
    while(add_fail_n < ADD_FAIL_TIMES && n_cur < target_sample_sum)
    {
        // generate new sample
        sample[0] = RandomFloat(0.f, 1.f);
        sample[1] = RandomFloat(0.f, 1.f);
        // get min(fill_rate)
        class_s = fill_rate_order[0];
        // init some temp value
        if_add = true;
        ns.clear();
        for(int i = 0; i < class_n; i++)
        {
            std::vector<std::array<float, 2>> &sample_class = image_samples[i];
            for(int j = 0, n = (int)sample_class.size(); j < n; j++)
            {
                std::array<float, 2> &s_ = sample_class[j];
                if(DIS(s_,sample) < r[i][class_s]) {
                    ns.push_back(std::make_pair(&sample_class, j));
                    if_add &= false;
                }
            }
        }
        if(if_add)
            add_new_sample(class_s, sample, fill_rate, fill_rate_order);
    }

}
