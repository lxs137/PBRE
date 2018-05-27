#ifndef PBRE_SHAPE_SHAPE_H
#define PBRE_SHAPE_SHAPE_H

#include "base/ray.h"
#include "base/geometry.h"
#include "base/intersect_detail.h"

namespace pbre {

  class Shape {
  public:
    virtual ~Shape() {}

    virtual BBox getBBox() const = 0; // 默认得到世界坐标下的包围盒

    virtual bool intersectP(const Ray &ray) const = 0;

    virtual bool intersect(const Ray &ray, float &t_hit, IntersectInfo &info) const = 0;
  };

}
#endif // PBRE_SHAPE_SHAPE_H
