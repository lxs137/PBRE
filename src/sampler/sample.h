//
// Created by lxs on 17-4-1.
//

#ifndef CAMERA_SAMPLER_H
#define CAMERA_SAMPLER_H

struct CameraSample
{
    float x, y;
    // 代表薄透镜相机中薄透镜上的采样点位置
    float len_u, len_v;
};

struct ComplexSample
{
public:
    ComplexSample():cam() {}
    CameraSample cam;
};

#endif //CAMERA_SAMPLER_H
