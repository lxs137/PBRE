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
        image_sp_pw = new int [class_n];
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
        target_sample_n = new int [class_n];
        target_sample_n_1 = new float[class_n];
        float max_dis;
        if(class_n >= 2)
            max_dis = build_matrix_r();
        else
            max_dis = r[0][0] = distance[0];
        target_sample_sum = 0;
        calculate_target_sample(max_dis);
    }
    ~MultiClassDiskSampler() {
        delete []image_sp_pw;
        delete [](r[0]);
        delete []r;
        delete []distance;
        delete []image_sample_index;
        delete []image_samples;
        delete []target_sample_n;
        delete []target_sample_n_1;
    }
private:
    // 每种采样类的单窗口采样点数,采样点集合
    int *image_sp_pw;
    std::vector<std::array<float, 2>> *image_samples;
    int *image_sample_index;
    int x_pos, y_pos;

    // 采样点类别数
    int class_n;
    // 同类采样点之间的最小距离
    float *distance;
    // 任意种类采样点之间的最小距离
    float **r;
    int *target_sample_n;
    float *target_sample_n_1;
    int target_sample_sum;

    float build_matrix_r();
    void calculate_target_sample(float max_dis);
    void hard_dart_throwing();
    float fill_rate(int i) {
        return image_samples[i].size()/target_sample_n[i];
    }
    void add_new_sample(int i, std::array<float, 2> &p, float *fill_rate, int *order);
    void generate_samples();
};

#endif //SAMPLER_MULTI_CLASS_DISK_SAMPLER_H
