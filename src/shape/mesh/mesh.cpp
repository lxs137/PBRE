//
// Created by lxs on 17-4-10.
//
#include "shape/mesh.h"

#include <cstring>

namespace pbre {
  TriMesh::TriMesh(const TriMesh &mesh) : Shape() {
    this->num_tri = mesh.num_tri;
    this->num_vertic = mesh.num_vertic;
    if (mesh.vertics) {
      vertics = new Point3D[num_vertic];
      memcpy(vertics, mesh.vertics, num_vertic * sizeof(Point3D));
    }
    if (mesh.index) {
      index = new TriIndex[num_tri];
      memcpy(index, mesh.index, num_tri * sizeof(TriIndex));
    }
    if (mesh.normals) {
      normals = new Normal[num_vertic];
      memcpy(normals, mesh.normals, num_vertic * sizeof(Normal));
    }
    if (mesh.texUV) {
      texUV = new Point2D[num_vertic];
      memcpy(texUV, mesh.texUV, num_vertic * sizeof(Point2D));
    }
  }


  TriMesh::TriMesh(int nvert, int nface, std::vector<Point3D> &points, std::vector<std::vector<int>> &faces,
                   std::vector<Normal> &ns, std::vector<std::array<float, 2>> &texture) {
    this->num_vertic = nvert;
    if (!points.empty()) {
      vertics = new Point3D[num_vertic];
      memcpy(vertics, points.data(), num_vertic * sizeof(Point3D));
    }
    if (!faces.empty()) {
      if (faces[0].size() > 3) {
        initFromPolygon(faces, nface);
      }
      else {
        this->num_tri = nface;
        index = new TriIndex[num_tri];
        for (int i = 0; i < num_tri; i++)
          index[i][0] = faces[i][0], index[i][1] = faces[i][1], index[i][2] = faces[i][2];
      }
    }
    if (!ns.empty()) {
      normals = new Normal[num_vertic];
      memcpy(normals, ns.data(), num_vertic * sizeof(Normal));
    }
    if (!texture.empty()) {
      texUV = new Point2D[num_vertic];
      for (int i = 0; i < num_vertic; i++)
        texUV[i].x = texture[i][0], texUV[i].y = texture[i][1];
    }
  }

  void TriMesh::initFromPolygon(std::vector<std::vector<int>> &faces, int nface) {
    int pointsPerFace = faces[0].size();
    if (pointsPerFace == 4) {
      num_tri = 2 * nface;
      index = new TriIndex[num_tri];
      int i = 0;
      for (std::vector<int> &per_face : faces) {
        index[i][0] = per_face[0], index[i][1] = per_face[1], index[i][2] = per_face[3];
        i++;
        index[i][0] = per_face[2], index[i][1] = per_face[1], index[i][2] = per_face[3];
        i++;
      }
    }
  }

  BBox TriMesh::getBBox() const {
    BBox bound;
    for (int i = 0; i < num_vertic; i++)
      bound.update(vertics[i]);
    return bound;
  }

  bool TriMesh::intersect(const Ray &ray, float &t_hit, IntersectInfo &info) const {
    return false;
  }

  bool TriMesh::intersectP(const Ray &ray) const {
    return false;
  }
}
