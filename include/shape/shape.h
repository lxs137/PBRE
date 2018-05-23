#ifndef PBRE_SHAPE_SHAPE_H
#define PBRE_SHAPE_SHAPE_H

#include "util/ray.h"
#include "util/geometry.h"
#include "util/intersect_detail.h"

class Shape{
public:
    virtual BBox get_BBox() = 0; // 默认得到世界坐标下的包围盒
    virtual ~Shape() {}
    virtual bool intersectP(const Ray &ray) = 0 ;
    virtual bool intersect(const Ray &ray, float &t_hit, IntersectInfo &info) = 0;
};

#endif // PBRE_SHAPE_SHAPE_H
