//
// Created by lxs on 17-3-22.
//

#ifndef UTIL_MATH_FUNC_H
#define UTIL_MATH_FUNC_H

#define INTERSECT_TEST_PRECISION 1e-3
#define BBOX_TINY_TEST 1e-2

const float PI = 3.14159f;

float min(const float a, const float b);
int min(const int a, const int b);
float max(const float a, const float b);
int max(const int a, const int b);
float Radians(float degree);
float Degree(float radians);
int Clamp(int value, int low, int high);


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
inline float Radians(float degree) {
    return (degree*PI/180.0f);
}
inline float Degree(float radians) {
    return (radians*180.0f/PI);
}
inline int Clamp(int value, int low, int high) {
    if(value <= low)
        return low;
    else if(value >= high)
        return high;
    else
        return value;
}

#endif //UTIL_MATH_FUNC_H
