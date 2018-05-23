//
// Created by lxs on 17-4-13.
//

#ifndef PBRE_SAMPLER_RANDOM_H
#define PBRE_SAMPLER_RANDOM_H

#include <vector>
#include <array>
#include <random>

#include "sampler.h"

namespace pbre {
  class RandomSampler : public Sampler
  {
  public:
    RandomSampler():Sampler() {
      x_pos = y_pos = 0;
      cur_sample_index = 0;
    }
    RandomSampler(int xStart, int xEnd, int yStart, int yEnd, int sample_per_win)
        : Sampler(xStart, xEnd, yStart, yEnd, (xEnd - xStart)*(yEnd - yStart)), distribution(0.f, 1.f) {
      sp_pw = sample_per_win;
      x_pos = x_start, y_pos = y_start;
      cur_sample_index = 0;
      image_samples.reserve((unsigned long)sp_pw);
      len_samples.reserve((unsigned long)sp_pw);
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
      return (int)image_samples.size();
    }
    // 下一个采样窗口, 返回false则所有窗口已被返回过
    bool next_window();
    // 返回为false, 说明要切换到下一个窗口
    bool get_sample(ComplexSample &sample);
    int get_all_samples(std::vector<ComplexSample> &samples);
  private:
    // sample per window
    int sp_pw;
    // 当前窗口位置
    int x_pos, y_pos;
    SAMPLES image_samples, len_samples;
    int cur_sample_index;
    std::uniform_real_distribution<float> distribution;
    std::random_device device;

    void generate_samples();
  };

}


#endif //PBRE_SAMPLER_RANDOM_H
