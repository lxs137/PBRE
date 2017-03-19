#ifndef UTIL_RAY_H
#define UTIL_RAY_H

#include "geometry.h"

class Ray{
public:
    //method

    // value
    Point3D o;
    Vector3D d;
    float min_t, max_t;

};

#endif // UTIL_RAY_H
