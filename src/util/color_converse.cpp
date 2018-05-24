//
// Created by liao xiangsen on 2018/5/24.
//

#include "util/color_converse.h"

#include <cmath>

namespace pbre {
  void HSVToRGB(float *hsv, uint8_t *rgb) {
    float h_i = hsv[0] / 60;
    float C = hsv[1] * hsv[2], m = hsv[2] - C;
    float X = C * (1 - std::fabs(((int) hsv[0] / 60) % 2 - 1));
    float r_ = 0.f, g_ = 0.f, b_ = 0.f;
    if (h_i >= 0 && h_i < 1.f) {
      r_ = C, g_ = X, b_ = 0;
    } else if (h_i >= 1.f && h_i < 2.f) {
      r_ = X, g_ = C, b_ = 0;
    } else if (h_i >= 2.f && h_i < 3.f) {
      r_ = 0, g_ = C, b_ = X;
    } else if (h_i >= 3.f && h_i < 4.f) {
      r_ = 0, g_ = X, b_ = C;
    } else if (h_i >= 4.f && h_i < 5.f) {
      r_ = X, g_ = 0, b_ = C;
    } else if (h_i >= 5.f && h_i <= 6.f) {
      r_ = C, g_ = 0, b_ = X;
    }
    rgb[0] = (uint8_t) ((r_ + m) * 255);
    rgb[1] = (uint8_t) ((g_ + m) * 255);
    rgb[2] = (uint8_t) ((b_ + m) * 255);
  }

  void XYZToRGB(float xyz[3], uint8_t rgb[3]) {
    float _rgb[3];
    _rgb[0] = 3.240479f * xyz[0] - 1.537150f * xyz[1] - 0.498535f * xyz[2];
    _rgb[1] = -0.969256f * xyz[0] + 1.875991f * xyz[1] + 0.041556f * xyz[2];
    _rgb[2] = 0.055648f * xyz[0] - 0.204043f * xyz[1] + 1.057311f * xyz[2];
    rgb[0] = (uint8_t)Clamp(_rgb[0] * 255.f, 0.f, 255.f);
    rgb[1] = (uint8_t)Clamp(_rgb[1] * 255.f, 0.f, 255.f);
    rgb[2] = (uint8_t)Clamp(_rgb[2] * 255.f, 0.f, 255.f);
  }

  void XYZToSRGB(float xyz[3], uint8_t rgb[3]) {
    float _rgb[3];
    _rgb[0] = 3.240479f * xyz[0] - 1.537150f * xyz[1] - 0.498535f * xyz[2];
    _rgb[1] = -0.969256f * xyz[0] + 1.875991f * xyz[1] + 0.041556f * xyz[2];
    _rgb[2] = 0.055648f * xyz[0] - 0.204043f * xyz[1] + 1.057311f * xyz[2];
    for(int i = 0; i < 3; i++) {
      _rgb[i] = _rgb[i] <= 0.00304f ? (12.92f * _rgb[i]) : (1.055f * std::powf(_rgb[i], 0.416f) - 0.055f);
    }
    rgb[0] = (uint8_t)Clamp(_rgb[0] * 255.f, 0.f, 255.f);
    rgb[1] = (uint8_t)Clamp(_rgb[1] * 255.f, 0.f, 255.f);
    rgb[2] = (uint8_t)Clamp(_rgb[2] * 255.f, 0.f, 255.f);
  }
}