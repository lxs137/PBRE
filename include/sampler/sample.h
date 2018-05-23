//
// Created by lxs on 17-4-1.
//

#ifndef PBRE_SAMPLER_SAMPLE_H
#define PBRE_SAMPLER_SAMPLE_H

namespace pbre {

  struct CameraSample
  {
    float x, y;
    // 代表薄透镜相机中薄透镜上的采样点位置
    float len_u, len_v;
  };

  struct ComplexSample
  {
    CameraSample cam;
  };
}


#endif //PBRE_SAMPLER_SAMPLE_H
