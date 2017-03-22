//
// Created by lxs on 17-3-22.
//

#ifndef SHAPE_POLYGON_H
#define SHAPE_POLYGON_H

#include <vector>
#include "shape.h"

// 这个多边形特指所有顶点共面的多边形
class Polygon: public Shape {
public:
    Polygon():n(Normal) {
        vertics = new std::vector<Point3D>();
    }
    Polygon(const Polygon &polygon):n(polygon.n), vertics(polygon.vertics) {}
    Polygon(const std::vector<Point3D> &points) {
        if(points.size() < 3)
            Polygon();
        else
        {
            vertics = new std::vector<Point3D>(points);
            // 根据前三个顶点确定该多边形所在平面
            Vector3D v1 = points[0] - points[1], v2 = points[0] - points[2];
            n = Normal(Cross(v1, v2));
        }
    }
    virtual BBox get_BBox();
    virtual bool intersectP(const Ray &ray);
    virtual bool intersect(const Ray &ray, float &t_hit, IntersectInfo &info);

private:
    std::vector<Point3D> vertics;
    Normal n;
};

#endif //SHAPE_POLYGON_H
