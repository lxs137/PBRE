//
// Created by lxs on 17-3-22.
//

#include "shape/plane.h"

namespace pbre {
  BBox Plane::getBBox() const {
    return BBox(Point3D(-INFINITY, -INFINITY, -INFINITY), Point3D(INFINITY, INFINITY, INFINITY));
  }

  bool Plane::intersect(const Ray &ray, float &t_hit, IntersectInfo &info) const {
    // t = (plane.p*plane.n - ray.o*plane.n) / (ray.d*plane.n)
    float parallel_test = AbsDot(ray.d, this->n);
    // 通过平面法向量和光线的方向向量的点乘结果,判断两者是否平行
    if (std::fabs(parallel_test) < 1e-5)
      return false;
    else {
      float t = Dot((this->p - ray.o), this->n) / Dot(ray.d, this->n);
      if (t > this->Epsilon && t > ray.min_t && t < ray.max_t) {
        info.hitN = this->n;
        info.hitP = ray(t);
        info.shape = this;
        t_hit = t;
        return true;
      } else
        return false;
    }
  }

  bool Plane::intersectP(const Ray &ray) const {
    // t = (plane.p*plane.n - ray.o*plane.n) / (ray.d*plane.n)
    float parallel_test = Dot(ray.d, this->n);
    if (std::fabs(parallel_test) < 1e-5)
      return false;
    else {
      float t = Dot((this->p - ray.o), this->n) / Dot(ray.d, this->n);
      return (t > this->Epsilon && t > ray.min_t && t < ray.max_t);
    }
  }
}