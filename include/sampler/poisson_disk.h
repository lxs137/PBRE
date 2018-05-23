//
// Created by lxs on 17-4-13.
//

#ifndef PBRE_SAMPLER_POISSON_DISK_H
#define PBRE_SAMPLER_POISSON_DISK_H

#include <vector>
#include <array>

#include "sampler.h"

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
        image_samples.reserve((unsigned long)image_sp_pw);
        len_samples.reserve((unsigned long)len_sp_pw);
        generate_samples();
    }
    // 获取采样点总数
    int get_sampler_count() {
        return (int)image_samples.size();
    }
    // 下一个采样窗口, 返回false则所有窗口已被返回过
    virtual bool next_window();
    // 返回为false, 说明要切换到下一个窗口
    virtual bool get_sample(ComplexSample &sample);
    virtual int get_all_samples(std::vector<ComplexSample> &samples);
private:
    // sample per window
    int image_sp_pw, len_sp_pw;
    // 两个采样点之间的最小距离
    float min_dis;
    int x_pos, y_pos;
    SAMPLES image_samples, len_samples;
    int image_sample_index, len_sample_index;

    void generate_samples();
};

void generate_poisson_sample(int width, int height, float min_distance, int new_points_count,
                            SAMPLES &image_samples);

std::array<float, 2> generate_random_point_around(const std::array<float, 2> &point, float min_dis);

#endif //PBRE_SAMPLER_POISSON_DISK_H
