//
// Created by lxs on 17-3-31.
//

#ifndef CAMERA_PINHOLE_H
#define CAMERA_PINHOLE_H

#define NEAR_PLANE 1e-2f   // 近平面与观察点的距离
#define FAR_PLANE 1000.f   // 远平面与观察点的距离

#include "camera.h"

// 小孔成像相机采用透视投影
class PinHoleCamera : Camera
{
public:
    PinHoleCamera():Camera(), raster2Screen(), screen2Raster(), screen2Camera(),
                    camera2Screen(), raster2Camera(), camera2Raster() {}
    PinHoleCamera(const Point3D &eye, const Point3D &lookat, const Vector3D &up,
                  float y_fov_degree, float d, ViewPlane *vp);
    virtual void generate_ray(CameraSample &sample, Ray &ray);
private:
    Transform raster2Screen, screen2Raster;
    Transform screen2Camera, camera2Screen;
    Transform raster2Camera, camera2Raster;
};

#endif //CAMERA_PINHOLE_H
