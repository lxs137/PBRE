//
// Created by lxs on 17-3-22.
//

#ifndef UTIL_MATH_FUNC_H
#define UTIL_MATH_FUNC_H

#define INTERSECT_TEST_PRECISION 1e-3
#define BBOX_TINY_TEST 1e-2

#include <stdlib.h>
#include <ctime>

const float PI = 3.14159f;

float min(const float a, const float b);
int min(const int a, const int b);
float max(const float a, const float b);
int max(const int a, const int b);
float Radians(const float degree);
float Degree(const float radians);
int Clamp(const int value, const int low, const int high);
int RandomInt(const int min, const int max);
float RandomFloat(const float min, const float max);


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
    if(value <= low)
        return low;
    else if(value >= high)
        return high;
    else
        return value;
}
inline int RandomInt(const int min, const int max) {
    if(min >= max)
        return min;
    srand(time(nullptr));
    int range = max - min + 1;
    return min + (rand() % range);
}
inline float RandomFloat(const float min, const float max) {
    if(min >= max)
        return min;
    srand(time(nullptr));
    int range = max - min;
    return (rand() / RAND_MAX * range) + min;
}

#endif //UTIL_MATH_FUNC_H
