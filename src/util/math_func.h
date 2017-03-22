//
// Created by lxs on 17-3-22.
//

#ifndef UTIL_MATH_FUNC_H
#define UTIL_MATH_FUNC_H

float min(float a, float b);
float max(float a, float b);


inline float min(float a, float b) {
    return ((a <= b) ? a : b);
}
inline float max(float a, float b) {
    return ((a > b) ? a : b);
}

#endif //UTIL_MATH_FUNC_H
