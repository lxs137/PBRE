#ifndef UTIL_GEOMETRY_H
#define UTIL_GEOMETRY_H

#include <math.h>

class Vector3D{
public:
    //method
    Vector3D();
    Vector3D(float xx, float yy, float zz):x(xx), y(xx), z(zz) {}
    Vector3D(const Vector3D &v){
        x = v.x, y = v.y, z = v.z;
    }
    virtual ~Vector3D();


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
    virtual ~Point3D();

    //value
    float x, y, z;
};

#endif // UTIL_GEOMETRY_H
