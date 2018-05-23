//
// Created by lxs on 17-5-6.
//

#ifndef PBRE_UTIL_COLOR_CONVERSE_H
#define PBRE_UTIL_COLOR_CONVERSE_H

void HSV_2_RGB(float hsv[3], int rgb[3])
{
    float h_i = hsv[0] / 60;
    float C = hsv[1]*hsv[2], m = hsv[2] - C;
    float X = C * (1- std::fabs( ((int)hsv[0]/60) % 2 - 1));
    float r_ = 0.f, g_ = 0.f, b_ = 0.f;
    if(h_i >= 0 && h_i < 1.f) {
        r_ = C, g_ = X, b_ = 0;
    } else if(h_i >= 1.f && h_i < 2.f) {
        r_ = X, g_ = C, b_ = 0;
    } else if(h_i >= 2.f && h_i < 3.f) {
        r_ = 0, g_ = C, b_ = X;
    } else if(h_i >= 3.f && h_i < 4.f) {
        r_ = 0, g_ = X, b_ = C;
    } else if(h_i >= 4.f && h_i < 5.f) {
        r_ = X, g_ = 0, b_ = C;
    } else if(h_i >= 5.f && h_i <= 6.f) {
        r_ = C, g_ = 0, b_ = X;
    }
    rgb[0] = (int)((r_ + m)*255);
    rgb[1] = (int)((g_ + m)*255);
    rgb[2] = (int)((b_ + m)*255);
}

#endif //PBRE_UTIL_COLOR_CONVERSE_H
