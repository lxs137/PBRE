#ifndef UTIL_GEOMETRY_H
#define UTIL_GEOMETRY_H

#include <cmath>

class Vector3D{
public:
    //method
    Vector3D();
    Vector3D(float xx, float yy, float zz):x(xx), y(xx), z(zz) {}
    Vector3D(const Vector3D &v){
        x = v.x, y = v.y, z = v.z;
    }
    virtual ~Vector3D();
    bool hasNan();
    Vector3D &operator= (const Vector3D &v);
    Vector3D operator- ();
    Vector3D operator+ (const Vector3D &v);
    Vector3D operator- (const Vector3D &v);
    Vector3D operator* (float f);
    Vector3D operator/ (float f);
    Vector3D &operator+= (const Vector3D &v);
    Vector3D &operator-= (const Vector3D &v);
    Vector3D &operator*= (float f);
    Vector3D &operator/= (float f);


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

// Class Vector3D method
inline bool Vector3D::hasNan(){
    return (std::isnan(x) || std::isnan(y) || std::isnan(z));
}
inline Vector3D &Vector3D::operator= (const Vector3D &v){
    x = v.x, y = v.y, z = v.z;
    return *this;
}
inline Vector3D Vector3D::operator-(){
    return Vector3D(-x, -y, -z);
}
inline Vector3D Vector3D::operator+ (const Vector3D &v){
    return Vector3D(x + v.x, y + v.y, z + v.z);
}
inline Vector3D Vector3D::operator- (const Vector3D &v){
    return Vector3D(x - v.x, y - v.y, z - v.z);
}
inline Vector3D Vector3D::operator* (float f){
    return Vector3D(x*f, y*f, z*f);
}
inline Vector3D &Vector3D::operator+= (const Vector3D &v){
    x += v.x, y += v.y, z += v.z;
    return *this;
}
inline Vector3D &Vector3D::operator-= (const Vector3D &v){
    x -= v.x, y -= v.y, z -= v.z;
    return *this;
}
inline Vector3D &Vector3D::operator*=(float f){
    x *= f, y *= f, z *= f;
    return *this;
}
inline Vector3D &Vector3D::operator/=(float f){
    x /= f, y /= f, z *= f;
    return *this;
}

#endif // UTIL_GEOMETRY_H
