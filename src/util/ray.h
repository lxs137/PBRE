#ifndef UTIL_RAY_H
#define UTIL_RAY_H

#define RAY_T_MIN 1e-3

#include "geometry.h"

class Ray{
public:
    //method
    Ray():min_t(RAY_T_MIN), max_t(INFINITY), depth(0) {
        o = Point3D();
        d = Vector3D();
    }
    Ray(const Point3D &origin, const Vector3D &direction, int ray_depth=0) {
        o = Point3D(origin);
        d = Vector3D(direction);
        min_t = RAY_T_MIN;
        max_t = INFINITY;
        depth = ray_depth;
    }
    Ray(const Ray &ray) {
        o = ray.o, d = ray.d;
        min_t = ray.min_t, max_t = ray.max_t;
        depth = ray.depth;
    }
    ~Ray() {}
    // 可以对一个Ray型的变量ray(t),得到相应t时的点坐标
    Point3D operator() (float t) const {
        return (o + t*d);
    }

    // value
    Point3D o;
    Vector3D d;
    float min_t, max_t;
    int depth;

};

#endif // UTIL_RAY_H
