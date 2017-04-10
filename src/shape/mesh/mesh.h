//
// Created by lxs on 17-4-3.
//

#ifndef SHAPE_MESH_MESH_H
#define SHAPE_MESH_MESH_H

#include "../shape.h"
#include "triangle.h"
#include <vector>

class Mesh : Shape
{
public:
    ~Shape() {
        vertics.clear();
    }
private:
    std::vector<Point3D> vertics;
};

#endif //SHAPE_MESH_MESH_H
