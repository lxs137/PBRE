//
// Created by lxs on 17-5-6.
//

#ifndef PBRE_UTIL_COLOR_CONVERSE_H
#define PBRE_UTIL_COLOR_CONVERSE_H

#include "util/math_func.h"

namespace pbre {
  // r, g, b: 0 ~ 255
  void HSVToRGB(float *hsv, uint8_t *rgb);

  void XYZToRGB(float xyz[3], uint8_t rgb[3]);

  // sRGB Use Gamma
  // https://en.wikipedia.org/wiki/SRGB
  void XYZToSRGB(float xyz[3], uint8_t rgb[3]);
}

#endif //PBRE_UTIL_COLOR_CONVERSE_H
