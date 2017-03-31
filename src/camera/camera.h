//
// Created by lxs on 17-3-28.
//

#ifndef CAMERA_CAMERA_H
#define CAMERA_CAMERA_H

#include "viewplane.h"
#include "../util/transform.h"
#include "../util/geometry.h"

class Camera
{
public:
    // method

    virtual void generate_ray(Ray &ray) = 0;
    // value
    ViewPlane *view_plane;
    Transform cam2World, world2Cam;
};

#endif //CAMERA_CAMERA_H
