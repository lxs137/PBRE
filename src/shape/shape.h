#ifndef SHAPE_SHAPE_H
#define SHAPE_SHAPE_H

#include "../util/ray.h"
#include "../util/geometry.h"
#include "../util/intersect_detail.h"

class Shape{
public:
    Shape() {}
    Shape(const Shape& object);
    ~Shape() {}
    virtual BBox get_BBox(); // 默认得到世界坐标下的包围盒
    virtual bool intersectP(const Ray &ray);
    virtual bool intersect(const Ray &ray, float t_hit, IntersectInfo &info);

};

#endif // SHAPE_SHAPE_H
