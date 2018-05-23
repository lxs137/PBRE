//
// Created by lxs on 17-4-10.
//
#include "shape/mesh.h"

#include <cstring>

TriMesh::TriMesh(const TriMesh &mesh):Shape() {
    vertics = NULL, index = NULL, normals = NULL, tex_coord = NULL;
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


TriMesh::TriMesh(int nvert, int nface, std::vector<Point3D> &points, std::vector<std::vector<int>> &faces,
           std::vector<Normal> &ns, std::vector<std::array<float, 2>> &texture) {
    vertics = NULL, index = NULL, normals = NULL, tex_coord = NULL;
    this->num_vertic = nvert;
    if(!points.empty())
    {
        vertics = new Point3D[num_vertic];
        memcpy(vertics, &points[0], num_vertic * sizeof(Point3D));
    }
    if(!faces.empty())
    {
        this->num_tri = nface;
        if(faces[0].size() > 3)
            Triangulate(faces, (int)faces[0].size());
        else
        {
            index = new std::array<int, 3>[num_tri];
            for(int i = 0; i < num_tri; i++)
                index[i][0] = faces[i][0], index[i][1] = faces[i][1], index[i][2] = faces[i][2];
        }
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

void TriMesh::Triangulate(std::vector<std::vector<int>> &faces, int points_per_face) {
    if(points_per_face == 4) {
        num_tri *= 2;
        index = new std::array<int, 3>[num_tri];
        int i = 0;
        for(std::vector<int> &per_face : faces)
        {
            index[i][0] = per_face[0], index[i][1] = per_face[1], index[i][2] = per_face[3];
            i++;
            index[i][0] = per_face[2], index[i][1] = per_face[1], index[i][2] = per_face[3];
            i++;
        }
    }
}

BBox TriMesh::get_BBox() {
    BBox bound;
    for(int i = 0; i < num_vertic; i++)
        bound.update(vertics[i]);
    return bound;
}

bool TriMesh::intersect(const Ray &ray, float &t_hit, IntersectInfo &info) {
    return false;
}

bool TriMesh::intersectP(const Ray &ray) {
    return false;
}


