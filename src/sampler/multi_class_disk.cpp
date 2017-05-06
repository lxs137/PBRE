//
// Created by lxs on 17-4-25.
//

#include "multi_class_disk.h"
#include "../util/math_func.h"
#include <algorithm>
#include <utility>
#include <functional>

#define R_EQUAL_MIN 1e-5

bool MultiClassDiskSampler::next_window()
{
    if(not_init())
        return false;
    x_pos++;
    if(x_pos == x_end) {
        x_pos = x_start;
        y_pos++;
    }
    if(y_pos == y_end)
        return false;
    generate_samples();
    return true;
}

bool MultiClassDiskSampler::get_sample(ComplexSample &sample)
{
    return get_sample(0, sample);
}

bool MultiClassDiskSampler::get_sample(int class_index, ComplexSample &sample)
{
    if(not_init())
        return false;
    int &sample_index = image_sample_index[class_index];
    if(sample_index == image_sp_pw[class_index])
        return false;
    sample.cam.x = x_pos + (image_samples[class_index])[sample_index][0];
    sample.cam.y = y_pos + (image_samples[class_index])[sample_index][1];
    sample_index++;
    return true;
}

int MultiClassDiskSampler::get_all_samples(std::vector<ComplexSample> &samples)
{
    return get_all_samples(0, samples);
}

int MultiClassDiskSampler::get_all_samples(int class_index, std::vector<ComplexSample> &samples)
{
    if(not_init())
        return 0;
    auto &img_samples = image_samples[class_index];
    int i = 0;
    for(auto &sample : img_samples)
    {
        samples[i].cam.x = x_pos + sample[0];
        samples[i].cam.y = y_pos + sample[1];
        i++;
    }
    image_sample_index[class_index] = image_sp_pw[class_index];
    return i;
}


void MultiClassDiskSampler::generate_samples()
{
    for(int i = 0; i < class_n; i++) {
        image_samples[i].clear();
        image_sp_pw[i] = 0;
        image_sample_index[i] = 0;
    }
    hard_dart_throwing();
}


bool distance_compare(std::pair<float, int> d1, std::pair<float, int> d2)
{
    return d1.first >= d2.first;
}

float MultiClassDiskSampler::build_matrix_r()
{
    std::vector<std::pair<float, int>> d_order;
    d_order.reserve((unsigned long)class_n);
    std::vector<int> P;
    P.reserve((unsigned long)(class_n * 2));
    for(int i = 0; i < class_n; i++) {
        r[i][i] = distance[i];
        d_order.push_back(std::make_pair(distance[i], i));
    }
    std::sort(d_order.begin(), d_order.end(), distance_compare);
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
    Pk.reserve((unsigned long)class_n);
    float D = 0.f;
    for(int k = 0, P_size = (int)P.size()/2; k < P_size; k++)
    {
        for(int index = P[2 * k], n = P[2 * k + 1]; index <= n; index++)
            Pk.push_back(d_order[index].second);
        C.insert(C.begin(), Pk.begin(), Pk.end());
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

#define ADD_FAIL_TIMES 20

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
    std::vector<std::pair<SAMPLES*, int>> ns;
    ns.reserve((unsigned long)target_sample_sum);
//    SAMPLES *sample_class;
    bool if_add;
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
            auto &sample_class = image_samples[i];
            for(int j = 0, n = (int)sample_class.size(); j < n; j++)
            {
                auto &s_ = sample_class[j];
                if(DIS(s_,sample) < r[i][class_s]) {
                    ns.push_back(std::make_pair(&sample_class, j));
                    if_add &= false;
                }
            }
        }
        if(if_add) {
            add_new_sample(class_s, sample, fill_rate, fill_rate_order);
            n_cur++;
        }
        else
            add_fail_n++;
    }

    for(int i = 0; i < class_n; i++)
    {
        image_sp_pw[i] = (int)(image_samples->size());
    }

    delete []fill_rate_order;
    delete []fill_rate;
}
