//
// Created by lxs on 17-4-25.
//

#ifndef SAMPLER_MULTI_CLASS_DISK_SAMPLER_H
#define SAMPLER_MULTI_CLASS_DISK_SAMPLER_H

#include "sampler.h"
#include <vector>
#include <array>

// Multi-Class Blue Noise Sampling
// http://www.liyiwei.org/papers/noise-sig10/paper_short.pdf
class MultiClassDiskSampler: public Sampler {
public:
    MultiClassDiskSampler() : Sampler() {
        x_pos = y_pos = 0;
        class_n = 0;
    }
    MultiClassDiskSampler(int xStart, int xEnd, int yStart, int yEnd, int class_count, float min_distance[])
            : Sampler(xStart, xEnd, yStart, yEnd, (xEnd - xStart)*(yEnd - yStart)) {
        class_n = class_count;
        image_samples = new std::vector<std::array<float, 2>>[class_n];
        image_sample_index = new int[class_n];
        distance = new float[class_n];
        r = new float*[class_n];
        float *space_ptr = new float[class_n*class_n];
        for(int i = 0, line = sizeof(float)*class_n; i< class_n; i++) {
            distance[i] = min_distance[i];
            r[i] = space_ptr;
            space_ptr += line;
        }
    }
    ~MultiClassDiskSampler() {
        delete [](r[0]);
        delete []r;
        delete []distance;
        delete []image_sample_index;
        delete []image_samples;
    }
private:
    // sample per window
    int image_sp_pw;
    int x_pos, y_pos;
    std::vector<std::array<float, 2>> *image_samples;
    int *image_sample_index;

    // 采样点类别数
    int class_n;
    // 同类采样点之间的最小距离
    float *distance;
    // 任意种类采样点之间的最小距离
    float **r;

    void build_matrix_r();
    void generate_sample();
};

#endif //SAMPLER_MULTI_CLASS_DISK_SAMPLER_H
