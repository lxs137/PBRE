//
// Created by lxs on 17-4-3.
//

#ifndef SHAPE_MESH_MESH_H
#define SHAPE_MESH_MESH_H

#include "../shape.h"
#include "triangle.h"
#include "../../util/transform.h"
#include <vector>
#include <array>

class Mesh : Shape
{
public:
    Mesh():Shape() {}
    Mesh(const Mesh &mesh);
    Mesh(int nvert, int ntri, std::vector<Point3D> &points, std::vector<std::vector<int>> &faces,
         std::vector<Normal> &ns, std::vector<std::array<float, 2>> &texture);
    virtual BBox get_BBox(); // 默认得到世界坐标下的包围盒
    virtual bool intersectP(const Ray &ray);
    virtual bool intersect(const Ray &ray, float &t_hit, IntersectInfo &info);
    ~Mesh() {
        delete []vertics;
        delete []index;
        delete []normals;
        delete []tex_coord;
    }
private:
    int num_vertic, num_tri;
    Point3D *vertics;
    std::array<int, 3> *index;
    Normal *normals;
    std::array<float, 2> *tex_coord;
};

#endif //SHAPE_MESH_MESH_H
