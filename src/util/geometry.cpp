//
// Created by lxs on 17-3-22.
//

#include "util/geometry.h"

#include "util/ray.h"

bool BBox::intersectP(const Ray &ray) {
    if(is_tiny())
        return false;
    float o_x = ray.o.x, o_y = ray.o.y, o_z = ray.o.z, d_x_1 = 1.0f / ray.d.x,
            d_y_1 = 1.0f / ray.d.y, d_z_1 = 1.0f / ray.d.z;
    float x_t0, x_t1, y_t0, y_t1, z_t0, z_t1, t0, t1;
    // 保证x_t0 < x_t1
    if(d_x_1 > 0)
    {
        x_t0 = (p_min.x - o_x) * d_x_1;
        x_t1 = (p_max.x - o_x) * d_x_1;
    } else{
        x_t1 = (p_min.x - o_x) * d_x_1;
        x_t0 = (p_max.x - o_x) * d_x_1;
    }
    // 保证y_t0 < y_t1
    if(d_y_1 > 0)
    {
        y_t0 = (p_min.y - o_y) * d_y_1;
        y_t1 = (p_max.y - o_y) * d_y_1;
    } else{
        y_t1 = (p_min.y - o_y) * d_y_1;
        y_t0 = (p_max.y - o_y) * d_y_1;
    }
    // 保证z_t0 < z_t1
    if(d_z_1 > 0)
    {
        z_t0 = (p_min.z - o_z) * d_z_1;
        z_t1 = (p_max.z - o_z) * d_z_1;
    } else{
        z_t1 = (p_min.z - o_z) * d_z_1;
        z_t0 = (p_max.z - o_z) * d_z_1;
    }

    t0 = max(x_t0, max(y_t0, z_t0));
    t1 = min(x_t1, min(y_t1, z_t1));
    return (t0 < t1 && t1 > ray.min_t);
}
