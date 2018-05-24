#ifndef PBRE_BASE_GEOMETRY_H
#define PBRE_BASE_GEOMETRY_H

#include <cmath>

#include "util/math_func.h"

namespace pbre {
  class Vector3D {
  public:
  // method
  Vector3D() { x = y = z = 0; }

  Vector3D(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}

  Vector3D(const Vector3D &v) {
    x = v.x, y = v.y, z = v.z;
  }

  ~Vector3D() {}

  bool hasNan() const {
    return (std::isnan(x) || std::isnan(y) || std::isnan(z));
  }

  bool operator==(const Vector3D &v) const {
    return (floatEq(x, v.x) && floatEq(y, v.y) && floatEq(z, v.z));
  }

  bool operator!=(const Vector3D &v) const {
    return (!floatEq(x, v.x) || !floatEq(y, v.y) || !floatEq(z, v.z));
  }

  Vector3D &operator=(const Vector3D &v) {
    x = v.x, y = v.y, z = v.z;
    return *this;
  }

  Vector3D operator-() const {
    return Vector3D(-x, -y, -z);
  }

  Vector3D operator+(const Vector3D &v) const {
    return Vector3D(x + v.x, y + v.y, z + v.z);
  }

  Vector3D operator-(const Vector3D &v) const {
    return Vector3D(x - v.x, y - v.y, z - v.z);
  }

  Vector3D operator*(float f) const {
    return Vector3D(x * f, y * f, z * f);
  }

  Vector3D operator/(float f) const {
    return Vector3D(x / f, y / f, z / f);
  }

  Vector3D &operator+=(const Vector3D &v) {
    x += v.x, y += v.y, z += v.z;
    return *this;
  }

  Vector3D &operator-=(const Vector3D &v) {
    x -= v.x, y -= v.y, z -= v.z;
    return *this;
  }

  Vector3D &operator*=(float f) {
    x *= f, y *= f, z *= f;
    return *this;
  }

  Vector3D &operator/=(float f) {
    x /= f, y /= f, z *= f;
    return *this;
  }

  float length_square() const {
    return (x * x + y * y + z * z);
  }

  float length() const {
    return std::sqrt(length_square());
  }

  // value
  float x, y, z;
  };


  class Point3D {
  public:
  // method
  Point3D() { x = y = z = 0; }

  Point3D(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}

  Point3D(const Point3D &p) {
    x = p.x, y = p.y, z = p.z;
  }

  ~Point3D() {}

  bool hasNan() const {
    return (std::isnan(x) || std::isnan(y) || std::isnan(z));
  }

  bool operator==(const Point3D &p) const {
    return (floatEq(x, p.x) && floatEq(y, p.y) && floatEq(z, p.z));
  }

  bool operator!=(const Point3D &p) const {
    return (!floatEq(x, p.x) || !floatEq(y, p.y) || !floatEq(z, p.z));
  }

  Point3D &operator=(const Point3D &p) {
    x = p.x, y = p.y, z = p.z;
    return *this;
  }

  Point3D operator+(const Vector3D &v) const {
    return Point3D(x + v.x, y + v.y, z + v.z);
  }

  Point3D operator-(const Vector3D &v) const {
    return Point3D(x - v.x, y - v.y, z - v.z);
  }

  Vector3D operator-(const Point3D &p) const {
    return Vector3D(x - p.x, y - p.y, z - p.z);
  }

  Point3D operator*(float f) const {
    return Point3D(x * f, y * f, z * f);
  }

  Point3D operator/(float f) const {
    return Point3D(x / f, y / f, z / f);
  }

  Point3D &operator+=(const Vector3D &v) {
    x += v.x, y += v.y, z += v.z;
    return *this;
  }

  Point3D &operator-=(const Vector3D &v) {
    x -= v.x, y -= v.y, z -= v.x;
    return *this;
  }

  Point3D &operator*=(float f) {
    x *= f, y *= f, z *= f;
    return *this;
  }

  Point3D &operator/=(float f) {
    x /= f, y /= f, z /= f;
    return *this;
  }

  // value
  float x, y, z;
  };


  class Normal {
  public:
  // method
  Normal() { x = y = z = 0; }

  Normal(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}

  Normal(const Normal &n) {
    x = n.x, y = n.y, z = n.z;
  }

  explicit Normal(const Vector3D &v) {
    x = v.x, y = v.y, z = v.z;
  }

  ~Normal() {}

  bool hasNan() const {
    return (std::isnan(x) || std::isnan(y) || std::isnan(z));
  }

  bool operator==(const Normal &n) const {
    return (floatEq(x, n.x) && floatEq(y, n.y) && floatEq(z, n.z));
  }

  bool operator!=(const Normal &n) const {
    return (!floatEq(x, n.x) || !floatEq(y, n.y) || !floatEq(z, n.z));
  }

  Normal &operator=(const Normal &n) {
    x = n.x, y = n.y, z = n.z;
    return *this;
  }

  Normal operator-() const {
    return Normal(-x, -y, -z);
  }

  Normal operator+(const Normal &n) const {
    return Normal(x + n.x, y + n.y, z + n.z);
  }

  Normal operator-(const Normal &n) const {
    return Normal(x - n.x, y - n.y, z - n.z);
  }

  Normal operator*(float f) const {
    return Normal(x * f, y * f, z * f);
  }

  Normal operator/(float f) const {
    return Normal(x / f, y / f, z / f);
  }

  Normal &operator+=(const Normal &n) {
    x += n.x, y += n.y, z += n.z;
    return *this;
  }

  Normal &operator-=(const Normal &n) {
    x -= n.x, y -= n.y, z -= n.z;
    return *this;
  }

  Normal &operator*=(float f) {
    x *= f, y *= f, z *= f;
    return *this;
  }

  Normal &operator/=(float f) {
    x /= f, y /= f, z *= f;
    return *this;
  }

  float length_square() const {
    return (x * x + y * y + z * z);
  }

  float length() const {
    return std::sqrt(length_square());
  }

  // value
  float x, y, z;
  };

  class Ray;

  class BBox {
  public:
  // method
  // 默认包围盒 p_min > p_max
  BBox() : p_min(INFINITY, INFINITY, INFINITY), p_max(-INFINITY, -INFINITY, -INFINITY) {}

  BBox(const Point3D &p): p_min(p), p_max(p) {}

  BBox(const Point3D &p1, const Point3D &p2) {
    float x_min = min(p1.x, p2.x), x_max = max(p1.x, p2.x),
      y_min = min(p1.y, p2.y), y_max = max(p1.y, p2.y),
      z_min = min(p1.z, p2.z), z_max = max(p1.z, p2.z);
    p_min = Point3D(x_min, y_min, z_min);
    p_max = Point3D(x_max, y_max, z_max);
  }

  BBox(const BBox &box) {
    p_min = box.p_min;
    p_max = box.p_max;
  }

  bool intersectP(const Ray &ray);

  // 判断包围盒是否为初始化状态或者坍缩为一个点
  bool is_tiny();

  bool check_point_inside(const Point3D &p);

  BBox Union(const BBox &b1, const BBox &b2);

  void update(const Point3D &p);

  // value
  Point3D p_min, p_max;
  };

// inline function
  inline Vector3D operator*(float f, const Vector3D &v) {
    return Vector3D(v.x * f, v.y * f, v.z * f);
  }

  inline Normal operator*(float f, const Normal &n) {
    return Normal(n.x * f, n.y * f, n.z * f);
  }

  inline float Dot(const Vector3D &v1, const Vector3D &v2) {
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
  }

  inline float Dot(const Vector3D &v, const Normal &n) {
    return (v.x * n.x + v.y * n.y + v.z * n.z);
  }

  inline float Dot(const Normal &n, const Vector3D &v) {
    return (v.x * n.x + v.y * n.y + v.z * n.z);
  }

  inline float AbsDot(const Vector3D &v1, const Vector3D &v2) {
    return std::fabs(Dot(v1, v2));
  }

  inline float AbsDot(const Vector3D &v, const Normal &n) {
    return std::fabs(Dot(v, n));
  }

  inline float AbsDot(const Normal &n, const Vector3D &v) {
    return std::fabs(Dot(v, n));
  }

  inline Vector3D Cross(const Vector3D &v1, const Vector3D &v2) {
    float x = v1.y * v2.z - v1.z * v2.y;
    float y = v1.z * v2.x - v1.x * v2.z;
    float z = v1.x * v2.y - v1.y * v2.x;
    return Vector3D(x, y, z);
  }

  inline Vector3D Cross(const Vector3D &v, const Normal &n) {
    float x = v.y * n.z - v.z * n.y;
    float y = v.z * n.x - v.x * n.z;
    float z = v.x * n.y - v.y * n.x;
    return Vector3D(x, y, z);
  }

  inline Vector3D Cross(const Normal &n, const Vector3D &v) {
    float x = n.y * v.z - n.z * v.y;
    float y = n.z * v.x - n.x * v.z;
    float z = n.x * v.y - n.y * v.x;
    return Vector3D(x, y, z);
  }

  inline Vector3D Normalize(const Vector3D &v) {
    return (v / v.length());
  }

  inline Normal Normalize(const Normal &n) {
    return (n / n.length());
  }

  inline float distance_square(Point3D &p1, Point3D &p2) {
    Vector3D dis = p1 - p2;
    return dis.length_square();
  }

  inline float distance(Point3D &p1, Point3D &p2) {
    Vector3D dis = p1 - p2;
    return dis.length();
  }

  inline bool BBox::is_tiny() {
    return (p_min.x > p_max.x || p_min.y > p_max.y || p_min.z > p_max.z
        || distance(p_min, p_max) < BBOX_TINY_TEST);
  }

  inline bool BBox::check_point_inside(const Point3D &p) {
    return (p.x > p_min.x && p.y > p_min.y && p.z > p_min.z
        && p.x < p_max.x && p.y < p_max.y && p.z < p_max.z);
  }

  inline BBox BBox::Union(const BBox &b1, const BBox &b2) {
    BBox b;
    const Point3D &b1_min = b1.p_min, &b1_max = b1.p_max, &b2_min = b2.p_min, &b2_max = b2.p_max;
    b.p_min.x = min(b1_min.x, b2_min.x);
    b.p_min.y = min(b1_min.y, b2_min.y);
    b.p_min.z = min(b1_min.z, b2_min.z);
    b.p_max.x = max(b1_max.x, b2_max.x);
    b.p_max.y = max(b1_max.y, b2_max.y);
    b.p_max.z = max(b1_max.z, b2_max.z);
    return b;
  }

  inline void BBox::update(const Point3D &p) {
    p_min.x = min(p_min.x, p.x);
    p_min.y = min(p_min.y, p.y);
    p_min.z = min(p_min.z, p.z);
    p_max.x = max(p_max.x, p.x);
    p_max.y = max(p_max.y, p.y);
    p_max.z = max(p_max.z, p.z);
  }
}

#endif // PBRE_BASE_GEOMETRY_H
