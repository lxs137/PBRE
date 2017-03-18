#ifndef SHAPE_SHAPE_H
#define SHAPE_SHAPE_H
#include "../util/ray.h"
#include "../util/geometry.h"

class Shape{
public:
    Shape();
    Shape(const Shape& object);
    virtual ~Shape();
    virtual bool intersectP(Ray &ray);

};

#endif // SHAPE_SHAPE_H
