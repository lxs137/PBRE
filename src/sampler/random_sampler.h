//
// Created by lxs on 17-4-13.
//

#ifndef SAMPLER_RANDOM_SAMPLER_H
#define SAMPLER_RANDOM_SAMPLER_H

#include "sampler.h"
#include <vector>
#include <array>
#include <random>

class RandomSampler : public Sampler
{
public:
    RandomSampler():Sampler() {
        x_pos = y_pos = 0;
        cur_sample_index = 0;
    }
    RandomSampler(int xStart, int xEnd, int yStart, int yEnd, int sample_per_win)
            : Sampler(xStart, xEnd, yStart, yEnd, (xEnd-xStart)*(yEnd-yStart), sample_per_win),
              distribution(0.f, 1.f) {
        x_pos = x_start, y_pos = y_start;
        cur_sample_index = 0;
        image_samples.reserve(win_num * sp_pw);
        len_samples.reserve(win_num * sp_pw);
        generate_samples();
    }
    ~RandomSampler() {
        image_samples.clear();
        len_samples.clear();
        image_samples.shrink_to_fit();
        len_samples.shrink_to_fit();
    }
    // 获取采样点总数
    int get_sampler_count() {
        return image_samples.size();
    }
    // 下一个采样窗口, 返回false则所有窗口已被返回过
    virtual bool next_window();
    // 返回为false, 说明要切换到下一个窗口
    virtual bool get_sample(ComplexSample *sample);
private:
    // 当前窗口位置
    int x_pos, y_pos;
    std::vector<std::array<float, 2>> image_samples, len_samples;
    int cur_sample_index;
    std::uniform_real_distribution<float> distribution;
    std::random_device device;
    bool not_init() {
        return (x_start == x_end || y_start == y_end || sp_pw == 0);
    }
    void generate_samples();
};

#endif //SAMPLER_RANDOM_SAMPLER_H
