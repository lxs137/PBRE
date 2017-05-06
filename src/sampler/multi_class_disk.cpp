//
// Created by lxs on 17-4-25.
//

#include "multi_class_disk.h"
#include "../util/math_func.h"
#include <algorithm>
#include <list>
#include <utility>
#include <functional>
#include <iostream>

#define R_EQUAL_MIN 1e-5

MultiClassDiskSampler::MultiClassDiskSampler(int xStart, int xEnd, int yStart,
                                             int yEnd, int class_count, float *min_distance)
        : Sampler(xStart, xEnd, yStart, yEnd, (xEnd - xStart)*(yEnd - yStart))
{
    x_pos = xStart, y_pos = yStart;
    class_n = class_count;
    image_sp_pw = new int [class_n];
    image_samples = new SAMPLES[class_n];
    image_sample_index = new int[class_n];
    distance = new float[class_n];
    r = new float*[class_n];
    float *space_ptr = new float[class_n * class_n];
    for(int i = 0; i< class_n; i++) {
        distance[i] = min_distance[i];
        r[i] = space_ptr;
        space_ptr += class_n;
    }
    target_sample_n = new int [class_n];
    target_sample_n_1 = new float[class_n];
    float max_dis;
    if(class_n >= 2)
        max_dis = build_matrix_r();
    else
        max_dis = r[0][0] = distance[0];
    target_sample_sum = 0;
    calculate_target_sample(max_dis);
    generate_samples();
}

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
    update_random_seed();
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
        image_samples[i].reserve((unsigned long)target_sample_n[i]);
    }
    delete []rate;
}

#define DIS(p1,p2) std::sqrt((p1[0]-p2[0])*(p1[0]-p2[0])+(p1[1]-p2[1])*(p1[1]-p2[1]))

typedef std::list<std::array<float, 2>> SAMPLES_SET;

// c: class, p: sample
void MultiClassDiskSampler::add_new_sample(int c, SAMPLES_SET &samples,
                                           std::array<float, 2> &p, float *fill_rate, int *order)
{
    samples.push_back(p);
    fill_rate[c] += target_sample_n_1[c];
    // 使order始终保持从小到大排列
    for(int i = 1; i < class_n; i++)
        if(fill_rate[c] > fill_rate[order[i]])
            std::swap(order[i - 1], order[i]);
        else
            break;
}

void MultiClassDiskSampler::hard_dart_throwing()
{
    // fill_rate从小到大排列
    int *fill_rate_order = new int[class_n];
    float *fill_rate = new float[class_n];
    for(int i = 0; i < class_n; i++) {
        fill_rate_order[i] = i;
        fill_rate[i] = 0.f;
    }

    std::array<float, 2> sample;
    std::vector<std::pair<int, SAMPLES_SET::iterator>> ns;
    ns.reserve((unsigned long)target_sample_sum);
    bool if_add, if_remove;
    auto *samples_li = new std::list<std::array<float, 2>>[class_n];
    int add_fail_n = 0, n_cur = 0, class_s;

//    int add_fail_times = 200*(int)std::sqrt(target_sample_sum);

    int add_fail_times = target_sample_sum ;

    while(add_fail_n < add_fail_times && n_cur < target_sample_sum)
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
            auto &samples_item = samples_li[i];
            for(auto it = samples_item.begin(); it != samples_item.end(); it++) {
                if(DIS((*it),sample) < r[i][class_s]) {
                    ns.push_back(std::make_pair(i, it));
                    if_add &= false;
                }
            }
        }
        if(if_add) {
            add_new_sample(class_s, samples_li[class_s], sample, fill_rate, fill_rate_order);
            add_fail_n = 0;
            n_cur++;
        }
        else
        {
            // Test Removable
            if_remove = true;
            for(auto &over_point : ns)
            {
                if(distance[over_point.first] >= distance[class_s]
                   || fill_rate[over_point.first] < fill_rate[class_s]) {
                    add_fail_n++;
                    if_remove = false;
                    break;
                }
            }
            if(if_remove)
            {
//                std::cout<<"Remove points: "<<ns.size()<<std::endl;
                for(auto &over_point : ns)
                    samples_li[over_point.first].erase(over_point.second);
                add_new_sample(class_s, samples_li[class_s], sample, fill_rate, fill_rate_order);
                add_fail_n = 0;
                n_cur++;
            }
        }
    }

    for(int i = 0; i < class_n; i++)
    {
        image_sp_pw[i] = (int)(samples_li[i].size());
        auto &samples_item = samples_li[i];
        auto &image_samples_item = image_samples[i];
        for(auto it = samples_item.begin(); it != samples_item.end(); it++)
            image_samples_item.push_back(*it);
    }

    delete []fill_rate_order;
    delete []fill_rate;
    delete []samples_li;
}
