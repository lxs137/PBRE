//
// Created by lxs on 17-4-25.
//

#include "multi_class_disk_sampler.h"
#include <algorithm>
#include <utility>
#include <functional>

#define R_EQUAL_MIN 1e-2

#define DIS(p1,p2) std::sqrt((p1[0]-p2[0])*(p1[0]-p2[0])+(p1[1]-p2[1])*(p1[1]-p2[1]))

bool distance_compare(std::pair<float, int> d1, std::pair<float, int> d2)
{
    return d1.first >= d2.first;
}

void MultiClassDiskSampler::build_matrix_r()
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
    C.reserve(class_n);
    float D = 0.f;
    for(int k = 0, P_size = P.size()/2; k < P_size; k++)
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
}