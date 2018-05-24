//
// Created by lxs on 17-3-22.
//

#ifndef PBRE_UTIL_MATH_FUNC_H
#define PBRE_UTIL_MATH_FUNC_H

#include <stdlib.h>
#include <ctime>

#define INTERSECT_TEST_PRECISION 1e-3
#define BBOX_TINY_TEST 1e-2
#define FLOAT_EQ_PERCISION 1e-4

namespace pbre {
  const float PI = 3.14159f;

  inline bool floatEq(const float a, const float b) {
    return (a - b <= FLOAT_EQ_PERCISION || a - b >= -FLOAT_EQ_PERCISION);
  }

  inline float min(const float a, const float b) {
    return ((a <= b) ? a : b);
  }

  inline int min(const int a, const int b) {
    return ((a <= b) ? a : b);
  }

  inline float max(const float a, const float b) {
    return ((a > b) ? a : b);
  }

  inline int max(const int a, const int b) {
    return ((a > b) ? a : b);
  }

  inline float Radians(const float degree) {
    return (degree * PI / 180.0f);
  }

  inline float Degree(const float radians) {
    return (radians * 180.0f / PI);
  }

  inline int Clamp(const int value, const int low, const int high) {
    if (value <= low)
      return low;
    else if (value >= high)
      return high;
    else
      return value;
  }

  inline float Clamp(const float value, const float low, const float high) {
    if (value <= low)
      return low;
    else if (value >= high)
      return high;
    else
      return value;
  }

  inline int RandomInt(const int min, const int max) {
    if (min >= max)
      return min;
    int range = max - min + 1;
    return min + (rand() % range);
  }

  inline float RandomFloat(const float min, const float max) {
    if (min >= max)
      return min;
    float range = max - min;
    return (rand() / (float) RAND_MAX * range) + min;
  }

  inline void UpdateRandomSeed() {
    srand(time(nullptr));
  }
}

#endif //PBRE_UTIL_MATH_FUNC_H
