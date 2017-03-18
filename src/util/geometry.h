#ifndef UTIL_GEOMETRY_H
#define UTIL_GEOMETRY_H

#include <math.h>

class Vector3D{
public:
    //method


    //value
    float x, y, z;
};

class Point3D{
public:
    //method
    Point3D();
    Point3D(float xx, float yy, float zz):x(xx), y(yy), z(zz) {}
    Point3D(const Point3D &p){
        x = p.x, y = p.y, z = p.z;

    }

    //value
    float x, y, z;
};

#endif // UTIL_GEOMETRY_H
