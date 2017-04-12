//
// Created by lxs on 17-3-28.
//

#ifndef CAMERA_CAMERA_H
#define CAMERA_CAMERA_H

#include "viewplane.h"
#include "sample.h"
#include "../util/transform.h"
#include "../util/geometry.h"

class Camera
{
public:
    // method
    Camera():cam2World(), world2Cam() { view_plane = NULL; }
    Camera(const Transform &world_to_camera, ViewPlane *vp):
            cam2World(world_to_camera.Inverse()), world2Cam(world_to_camera) {
        view_plane = vp;
    }
    virtual void generate_ray(CameraSampler &sample, Ray &ray) = 0;
    // value
    ViewPlane *view_plane;
    Transform cam2World, world2Cam;
};

#endif //CAMERA_CAMERA_H
