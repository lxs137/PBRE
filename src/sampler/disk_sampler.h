//
// Created by lxs on 17-4-13.
//

#ifndef SAMPLER_DISK_SAMPLER_H
#define SAMPLER_DISK_SAMPLER_H

#include "sampler.h"
#include <vector>
#include <array>

// Poisson Disk Sampler
// http://devmag.org.za/2009/05/03/poisson-disk-sampling/
class DiskSampler : public Sampler
{
public:
    DiskSampler():Sampler() {
        x_pos = y_pos = 0;
        len_sample_index = image_sample_index = 0;
    }
    DiskSampler(int xStart, int xEnd, int yStart, int yEnd, float min_distance)
            :Sampler(xStart, xEnd, yStart, yEnd, (xEnd - xStart)*(yEnd - yStart)) {
        // 最大可能的单位窗口采样点数量
        min_dis = min_distance;
        len_sp_pw = image_sp_pw = (int)(1.f / (min_dis * min_dis) + 0.5f);
        x_pos = x_start, y_pos = y_start;
        len_sample_index = image_sample_index = 0;
        image_samples.reserve(image_sp_pw);
        len_samples.reserve(len_sp_pw);
    }
    // 获取采样点总数
    int get_sampler_count() {
        return (int)image_samples.size();
    }
    // 下一个采样窗口, 返回false则所有窗口已被返回过
    virtual bool next_window();
    // 返回为false, 说明要切换到下一个窗口
    virtual bool get_sample(ComplexSample *sample);
private:
    // sample per window
    int image_sp_pw, len_sp_pw;
    // 两个采样点之间的最小距离
    int min_dis;
    int x_pos, y_pos;
    std::vector<std::array<float, 2>> image_samples, len_samples;
    int image_sample_index, len_sample_index;

    void generate_sample();
};

void generate_poisson_sample(int width, int height, float min_distance, int new_points_count,
                            std::vector<std::array<float, 2>> &image_samples);

std::array<float, 2> generate_random_point_around(const std::array<float, 2> &point, float min_dis);

#endif //SAMPLER_DISK_SAMPLER_H
