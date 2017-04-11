//
// Created by lxs on 17-4-10.
//

#include "mesh.h"
#include <cstring>

Mesh::Mesh(const Mesh &mesh):Shape() {
    this->num_tri = mesh.num_tri;
    this->num_vertic = mesh.num_vertic;
    if(mesh.vertics) {
        vertics = new Point3D[num_vertic];
        memcpy(vertics, mesh.vertics, num_vertic * sizeof(Point3D));
    }
    if(mesh.index) {
        index = new std::array<int, 3>[num_tri];
        memcpy(index, mesh.index, num_tri * sizeof(std::array<int, 3>));
    }
    if(mesh.normals) {
        normals = new Normal[num_vertic];
        memcpy(normals, mesh.normals, num_vertic * sizeof(Normal));
    }
    if(mesh.tex_coord) {
        tex_coord = new std::array<float, 2>[num_vertic];
        memcpy(tex_coord, mesh.tex_coord, num_vertic * sizeof(std::array<float, 2>));
    }
}


Mesh::Mesh(int nvert, int ntri, std::vector<Point3D> &points, std::vector<std::vector<int>> &faces,
           std::vector<Normal> &ns, std::vector<std::array<float, 2>> &texture) {
    this->num_vertic = nvert;
    this->num_tri = ntri;
    if(!points.empty())
    {
        vertics = new Point3D[num_vertic];
        memcpy(vertics, &points[0], num_vertic * sizeof(Point3D));
    }
    if(!faces.empty())
    {
        index = new std::array<int, 3>[num_tri];
        for(int i = 0; i < num_tri; i++)
            index[i][0] = faces[i][0], index[i][1] = faces[i][1], index[i][2] = faces[i][2];
    }
    if(!ns.empty())
    {
        normals = new Normal[num_vertic];
        memcpy(normals, &ns[0], num_vertic * sizeof(Normal));
    }
    if(!texture.empty())
    {
        tex_coord = new std::array<float, 2>[num_vertic];
       for(int i = 0; i < num_vertic; i++)
           tex_coord[i][0] = texture[i][0], tex_coord[i][1] = texture[i][1];
    }
}

BBox Mesh::get_BBox() {

}

bool Mesh::intersect(const Ray &ray, float &t_hit, IntersectInfo &info) {}

bool Mesh::intersectP(const Ray &ray) {}

