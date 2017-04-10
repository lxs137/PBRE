//
// Created by lxs on 17-4-3.
//

#ifndef SHAPE_MESH_TRIANGLE_H
#define SHAPE_MESH_TRIANGLE_H

#include "../shape.h"

class Triangle : Shape
{
public:
    virtual BBox get_BBox() = 0; // 默认得到世界坐标下的包围盒
    virtual bool intersectP(const Ray &ray) = 0 ;
    virtual bool intersect(const Ray &ray, float &t_hit, IntersectInfo &info) = 0;

private:
    Normal n;
    Point3D *p1, *p2, *p3;
};

#endif //SHAPE_MESH_TRIANGLE_H
