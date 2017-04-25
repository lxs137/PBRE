//
// Created by lxs on 17-4-25.
//

#include "multi_class_disk_sampler.h"
#include <algorithm>
#include <functional>

#define R_EQUAL_MIN 1e-2

void MultiClassDiskSampler::build_matrix_r()
{
    float *d_order = new float[class_n];
    std::vector<int> P;
    P.reserve(class_n*2);
    for(int i = 0; i < class_n; i++) {
        r[i][i] = distance[i];
        d_order[i] = distance[i];
    }
    std::sort(d_order, d_order+class_n, std::greater_equal<float>());
    for(int i = 0, index[2] = {0, 0}; i < class_n; i++) {
        if(std::abs(d_order[i] - d_order[i + 1]) < R_EQUAL_MIN)
            index[1]++;
        else {
            P.push_back(index[0]);
            P.push_back(index[1]);
            index[1] = index[0] = index[1] + 1;
        }
    }
    int P_size = P.size()/2;
    std::vector<int> C;
    float D;
    for(int k = 0; k < P_size; k++)
    {

    }
}