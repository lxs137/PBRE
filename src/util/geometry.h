#ifndef UTIL_GEOMETRY_H
#define UTIL_GEOMETRY_H

#include <cmath>

class Vector3D{
public:
    // method
    Vector3D();
    Vector3D(float xx, float yy, float zz):x(xx), y(xx), z(zz) {}
    Vector3D(const Vector3D &v){
        x = v.x, y = v.y, z = v.z;
    }
    ~Vector3D() {}
    bool hasNan() {
        return (std::isnan(x) || std::isnan(y) || std::isnan(z));
    }
    bool operator== (const Vector3D &v) {
        return (x==v.x && y==v.y && z==v.z);
    }
    bool operator!= (const Vector3D &v) {
        return (x!=v.x || y!=v.y || z!=v.z);
    }
    Vector3D &operator= (const Vector3D &v){
        x = v.x, y = v.y, z = v.z;
        return *this;
    }
    Vector3D operator- () {
        return Vector3D(-x, -y, -z);
    }
    Vector3D operator+ (const Vector3D &v) {
        return Vector3D(x + v.x, y + v.y, z + v.z);
    }
    Vector3D operator- (const Vector3D &v) {
        return Vector3D(x - v.x, y - v.y, z - v.z); }
    }
    Vector3D operator* (float f) {
        return Vector3D(x*f, y*f, z*f);
    }
    Vector3D operator/ (float f) {
        return Vector3D(x/f, y/f, z/f);
    }
    Vector3D &operator+= (const Vector3D &v){
        x += v.x, y += v.y, z += v.z;
        return *this;
    }
    Vector3D &operator-= (const Vector3D &v){
        x -= v.x, y -= v.y, z -= v.z;
        return *this;
    }
    Vector3D &operator*= (float f){
        x *= f, y *= f, z *= f;
        return *this;
    }
    Vector3D &operator/= (float f){
        x /= f, y /= f, z *= f;
        return *this;
    }
    float length_square() {
        return (x*x + y*y + z*z);
    }
    float length() {
        return std::sqrt(length_square());
    }

    // value
    float x, y, z;
};

class Point3D{
public:
    // method
    Point3D();
    Point3D(float xx, float yy, float zz):x(xx), y(yy), z(zz) {}
    Point3D(const Point3D &p){
        x = p.x, y = p.y, z = p.z;
    }
    ~Point3D() {}
    bool hasNan() {
        return (std::isnan(x) || std::isnan(y) || std::isnan(z));
    }
    bool operator== (const Point3D &p) {
        return (x==p.x && y==p.y && z==p.z);
    }
    bool operator!= (const Point3D &p) {
        return (x!=p.x || y!=p.y || z!=p.z);
    }
    Point3D &operator= (const Point3D &p){
        x = p.x, y = p.y, z = p.z;
        return *this;
    }
    Point3D operator+ (const Vector3D &v){
        return Point3D(x + v.x, y + v.y, z + v.z);
    }
    Point3D operator- (const Vector3D &v){
        return Point3D(x - v.x, y - v.y, z - v.z);
    }
    Vector3D operator- (const Point3D &p){
        return Vector3D(x - p.x, y - p.y, z - p.z);
    }
    Point3D operator* (float f){
        return Point3D(x*f, y*f, z*f);
    }
    Point3D operator/ (float f){
        return Point3D(x/f, y/f, z/f);
    }
    Point3D &operator+= (const Vector3D &v){
        x += v.x, y += v.y, z += v.z;
        return *this;
    }
    Point3D &operator-= (const Vector3D &v){
        x -= v.x, y -= v.y, z -=v.x;
        return *this;
    }
    Point3D &operator*= (float f){
        x *= f, y *= f, z *= f;
        return *this;
    }
    Point3D &operator/= (float f){
        x /= f, y /= f, z /= f;
        return *this;
    }

    // value
    float x, y, z;
};

// inline function
inline Vector3D operator*(float f, const Vector3D &v){
    return Vector3D(v.x*f, v.y*f, v.z*f);
}

inline float Dot(const Vector3D &v1, const Vector3D &v2){
    return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}
inline float AbsDot(const Vector3D &v1, const Vector3D &v2){
    return std::abs(Dot(v1, v2));
}
inline Vector3D Cross(const Vector3D &v1, const Vector3D &v2){
    float x = v1.y*v2.z - v1.z*v2.y;
    float y = v1.z*v2.x - v1.x*v2.z;
    float z = v1.x*v2.y - v1.y*v2.x;
    return Vector3D(x, y, z);
}
inline Vector3D Normalize(const Vector3D &v){
    return (v / v.length());
}
inline float distance_square(Point3D &p1, Point3D &p2){
    Vector3D dis = p1 - p2;
    return dis.length_square();
}
inline float distance(Point3D &p1, Point3D &p2){
    Vector3D dis = p1 - p2;
    return dis.length();
}


#endif // UTIL_GEOMETRY_H
