//
// Created by lxs on 17-3-22.
//

#ifndef UTIL_MATH_FUNC_H
#define UTIL_MATH_FUNC_H

const float PI = 3.14159f;

float min(float a, float b);
float max(float a, float b);
float Radians(float degree);
float Degree(float radians);


inline float min(float a, float b) {
    return ((a <= b) ? a : b);
}
inline float max(float a, float b) {
    return ((a > b) ? a : b);
}
inline float Radians(float degree) {
    return (degree*PI/180.0f);
}
inline float Degree(float radians) {
    return (radians*180.0f/Pi);
}

#endif //UTIL_MATH_FUNC_H
