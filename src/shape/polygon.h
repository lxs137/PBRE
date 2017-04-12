//
// Created by lxs on 17-3-22.
//

#ifndef SHAPE_POLYGON_H
#define SHAPE_POLYGON_H



#include <vector>
#include "shape.h"

struct Point2D{
    float x;
    float y;
};

// 这个多边形特指所有顶点共面的多边形
class Polygon: public Shape {
public:
    Polygon():Shape(), n() {}
    Polygon(const Polygon &polygon):Shape(), n(polygon.n), vertics(polygon.vertics) {}
    Polygon(const std::vector<Point3D> &points):Shape() {
        if(points.size() < 3)
            Polygon();
        else
        {
            vertics.insert(vertics.begin(), points.begin(), points.end());
            // 根据前三个顶点确定该多边形所在平面
            Vector3D v1 = points[0] - points[1], v2 = points[0] - points[2];
            n = Normal(Cross(v1, v2));
        }
    }
    std::vector<Point3D> get_vertics() {
        return vertics;
    }
    virtual BBox get_BBox();
    virtual bool intersectP(const Ray &ray);
    virtual bool intersect(const Ray &ray, float &t_hit, IntersectInfo &info);

private:
    std::vector<Point3D> vertics;
    Normal n;
};

#endif //SHAPE_POLYGON_H
