//
// Created by lxs on 17-3-28.
//

#ifndef PBRE_CAMERA_CAMERA_H
#define PBRE_CAMERA_CAMERA_H

#include <memory>

#include "camera/viewplane.h"
#include "sampler/sample.h"
#include "util/transform.h"
#include "base/geometry.h"

namespace pbre {
  class Camera
  {
  public:
    // method
    Camera():cam2World(), world2Cam() { viewPlane = nullptr; }
    Camera(const Transform &world2Camera, std::shared_ptr<ViewPlane> vp):
        cam2World(world2Camera.Inverse()), world2Cam(world2Camera) {
      viewPlane = vp;
    }
    virtual ~Camera() {}
    virtual void generate_ray(CameraSample &sample, Ray &ray) = 0;
    // value
    std::shared_ptr<ViewPlane> viewPlane;
    Transform cam2World, world2Cam;
  };
}

#endif //PBRE_CAMERA_CAMERA_H
