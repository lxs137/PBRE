//
// Created by lxs on 17-3-31.
//

#ifndef PBRE_CAMERA_PINHOLE_H
#define PBRE_CAMERA_PINHOLE_H

#define NEAR_PLANE 1e-2f   // 近平面与观察点的距离
#define FAR_PLANE 1000.f   // 远平面与观察点的距离

#include <memory>

#include "camera.h"

namespace pbre {
  // 小孔成像相机采用透视投影
  class PinHoleCamera : Camera
  {
  public:
    PinHoleCamera():Camera(), raster2Screen(), screen2Raster(), screen2Camera(),
                    camera2Screen(), raster2Camera(), camera2Raster() {}
    PinHoleCamera(const Point3D &eye, const Point3D &lookat, const Vector3D &up,
                  float y_fov_degree, float d, std::shared_ptr<ViewPlane> vp);
    void generate_ray(CameraSample &sample, Ray &ray);
  private:
    Transform raster2Screen, screen2Raster;
    Transform screen2Camera, camera2Screen;
    Transform raster2Camera, camera2Raster;
  };
}

#endif //PBRE_CAMERA_PINHOLE_H
