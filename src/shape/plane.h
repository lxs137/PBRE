//
// Created by lxs on 17-3-21.
//

#ifndef SHAPE_PLANE_H
#define SHAPE_PLANE_H

#define PLANE_EPSILON 1e-3

#include "../shape/shape.h"
#include "../util/geometry.h"

class Plane:public Shape{
public:
    Plane():Shape(), Epsilon(PLANE_EPSILON) {
        p = Point3D();
        n = Normal();
    }
    Plane(const Point3D &pp, const Normal &nn):Shape(), Epsilon(PLANE_EPSILON) {
        p = pp, n = nn;
    }
    Plane(const Plane *plane):Shape(), Epsilon(PLANE_EPSILON) {
        p = plane.p, n = plane.n;
    }
    BBox get_BBox();
    bool intersectP(const Ray &ray);
    bool intersect(const Ray &ray, float t_hit, IntersectInfo &info);

private:
    Point3D p;
    Normal n;
    const float Epsilon;
};

#endif //SHAPE_PLANE_H
