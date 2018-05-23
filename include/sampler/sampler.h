//
// Created by lxs on 17-4-13.
//

#ifndef PBRE_SAMPLER_SAMPLER_H
#define PBRE_SAMPLER_SAMPLER_H

#include <vector>
#include <array>

#include "sample.h"

typedef std::vector<std::array<float, 2>> SAMPLES;

class Sampler
{
public:
    Sampler() {
        x_start = y_start = x_end = y_end = 0;
        win_num = 0;
    }
    Sampler(int xStart, int xEnd, int yStart, int yEnd, int nwindows) {
        x_start = xStart, x_end = xEnd, y_start = yStart, y_end = yEnd;
        win_num = nwindows;
    }
    virtual ~Sampler() {}
    bool not_init() {
        return (x_start == x_end || y_start == y_end || win_num == 0);
    }
    // 获取采样点总数
    virtual int get_sampler_count() = 0;
    // 下一个采样窗口, 返回false则所有窗口已被返回过
    virtual bool next_window() = 0;
    // 返回为false, 说明要切换到下一个窗口
    virtual bool get_sample(ComplexSample &sample) = 0;
    // 得到该窗口所有的采样点, 返回值表示采样点数量
    virtual int get_all_samples(std::vector<ComplexSample> &samples) = 0;

    // 二维平面上采样点的生成范围
    int x_start, y_start, x_end, y_end;
    // 采样子窗口数, 默认情况下一个pixel一个窗口
    int win_num;
};

#endif //PBRE_SAMPLER_SAMPLER_H
