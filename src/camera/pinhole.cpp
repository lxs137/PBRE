//
// Created by lxs on 17-4-2.
//

#include "camera/pinhole.h"

PinHoleCamera::PinHoleCamera(const Point3D &eye, const Point3D &lookat, const Vector3D &up,
                             float y_fov_degree, float d, ViewPlane *vp):Camera(LookAt(eye, lookat, up), vp) {
    view_plane = vp;

    // 透视投影变换
    Matrix4_4 perspective(1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, FAR_PLANE/(FAR_PLANE- NEAR_PLANE), -FAR_PLANE*NEAR_PLANE/(FAR_PLANE - NEAR_PLANE),
                          0, 0, 1, 0);
    // fov为弧度制, fov为沿y方向上的视角大小
    // 将y方向投影到[-1, 1]
    float perspective_scale = 1.f/(tanf(0.5f*Radians(y_fov_degree)));
    camera2Screen = Scale(perspective_scale, perspective_scale, 1.f)*Transform(perspective, perspective.Inverse());
    screen2Camera = camera2Screen.Inverse();

    // 透视投影的缩放将y方向投影到[-1, 1], 还需计算投影后x方向上的取值范围
    float x_resolution = (float)view_plane->x_resolution, y_resolution = (float)view_plane->y_resolution;
    float scale_x = x_resolution/y_resolution, scale_y = 1.f;
    screen2Raster = Transform(Scale(x_resolution, y_resolution, 1.f)*
                                      Scale(1.f/(2.f*scale_x), -0.5f, 1.f)*
                                      Translate(Vector3D(scale_x, -scale_y, 0.f)));
    raster2Screen = screen2Raster.Inverse();

    raster2Camera = screen2Camera*raster2Screen;
    camera2Raster = screen2Raster*camera2Screen;
}

void PinHoleCamera::generate_ray(CameraSample &sample, Ray &ray) {
    Point3D sample_p(sample.x, sample.y, 0.f);
    // 计算相机坐标系下的光线参数
    Point3D ray_o = Point3D(0.f, 0.f, 0.f);
    Vector3D ray_d = Normalize(Vector3D(raster2Camera(sample_p) - ray_o));
    // 转换为世界坐标系下的光线参数
    ray.o = cam2World(ray_o);
    ray.d = cam2World(ray_d);
}
