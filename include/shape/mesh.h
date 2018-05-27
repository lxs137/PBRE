//
// Created by lxs on 17-4-3.
//

#ifndef PBRE_SHAPE_MESH_H
#define PBRE_SHAPE_MESH_H

#include <vector>
#include <array>

#include "shape.h"
#include "triangle.h"
#include "util/transform.h"

namespace pbre {
  class TriMesh : public Shape
  {
  public:
    // method
    TriMesh():Shape() {
      vertics = nullptr;
      index = nullptr;
      normals = nullptr;
      texUV = nullptr;
    }
    TriMesh(const TriMesh &mesh);
    TriMesh(int nvert, int nface, std::vector<Point3D> &points, std::vector<std::vector<int>> &faces,
            std::vector<Normal> &ns, std::vector<std::array<float, 2>> &texture);
    void Triangulate(std::vector<std::vector<int>> &faces, int points_per_face);
    virtual BBox getBBox() const ; // 默认得到世界坐标下的包围盒
    virtual bool intersectP(const Ray &ray) const ;
    virtual bool intersect(const Ray &ray, float &t_hit, IntersectInfo &info) const ;
    ~TriMesh() {
      delete[] vertics;
      delete[] index;
      delete[] normals;
      delete[] texUV;
    }
    // value
    int num_vertic, num_tri;
    Point3D *vertics;
    std::array<int, 3> *index;
    Normal *normals;
    Point2D *texUV;
  };
}

#endif //PBRE_SHAPE_MESH_H
