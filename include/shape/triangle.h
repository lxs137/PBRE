//
// Created by lxs on 17-4-3.
//

#ifndef PBRE_SHAPE_TRIANGLE_H
#define PBRE_SHAPE_TRIANGLE_H

#include "shape.h"

class TriMesh;

// 特指mesh中的三角形
class Triangle : public Shape
{
public:
    Triangle():owner(nullptr) {}
    Triangle(TriMesh *mesh, int index_1, int index_2, int index_3) {
        owner = mesh;
        v1 = index_1, v2 = index_2, v3 = index_3;
    }
    virtual BBox get_BBox(); // 默认得到世界坐标下的包围盒
    virtual bool intersectP(const Ray &ray);
    virtual bool intersect(const Ray &ray, float &t_hit, IntersectInfo &info);

private:
    TriMesh *owner;
    // 在owner中的顶点序号
    int v1, v2, v3;
};

#endif //PBRE_SHAPE_TRIANGLE_H
