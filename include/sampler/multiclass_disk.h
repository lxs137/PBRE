//
// Created by lxs on 17-4-25.
//

#ifndef PBRE_SAMPLER_MULTICLASS_DISK_H
#define PBRE_SAMPLER_MULTICLASS_DISK_H

#include <vector>
#include <array>
#include <list>

#include "sampler.h"

// Multi-Class Blue Noise Sampling
// http://www.liyiwei.org/papers/noise-sig10/paper_short.pdf
class MultiClassDiskSampler: public Sampler {
public:
    MultiClassDiskSampler() : Sampler() {
        x_pos = y_pos = 0;
        class_n = 0;
    }
    MultiClassDiskSampler(int xStart, int xEnd, int yStart,
                          int yEnd, int class_count, float min_distance[]);
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
    // 获取采样点总数
    int get_sampler_count() {
        int sum = 0;
        for(int i = 0; i < class_n; i++)
            sum += image_sp_pw[i];
        return sum;
    }
    int get_sampler_count(int class_index) {
        return image_sp_pw[class_index];
    }
    // 下一个采样窗口, 返回false则所有窗口已被返回过
    virtual bool next_window();
    // 返回为false, 说明要切换到下一个窗口
    virtual bool get_sample(ComplexSample &sample);
    bool get_sample(int class_index, ComplexSample &sample);
    // 得到该窗口所有采样点
    virtual int get_all_samples(std::vector<ComplexSample> &samples);
    int get_all_samples(int class_index, std::vector<ComplexSample> &samples);
private:
    // 每种采样类的单窗口采样点数,采样点集合
    int *image_sp_pw;
    SAMPLES *image_samples;
    int *image_sample_index;
    int x_pos, y_pos;

    // 采样点类别数
    int class_n;
    // 同类采样点之间的最小距离
    float *distance;
    // 任意两类采样点之间的最小距离的平方
    float **r;
    int *target_sample_n;
    float *target_sample_n_1;
    int target_sample_sum;

    float build_matrix_r();
    void calculate_target_sample(float max_dis);
    void hard_dart_throwing();
    void add_new_sample(int c, std::list<std::array<float, 2>> &samples,
                        std::array<float, 2> &p, float *fill_rate, int *order);
    void generate_samples();
};

#endif //PBRE_SAMPLER_MULTICLASS_DISK_H
