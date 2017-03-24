//
// Created by lxs on 17-3-21.
//

#ifndef UTIL_INTERSECT_DETAIL_H
#define UTIL_INTERSECT_DETAIL_H

class Shape;

#include "geometry.h"

class IntersectInfo {
public:
    // method
    IntersectInfo():hit_p(), hit_n() {}
    IntersectInfo(const Point3D &p, const Normal &n, Shape *shape_ptr):hit_p(p), hit_n(n) {
        shape = shape_ptr;
    }
    IntersectInfo(const IntersectInfo &info):hit_p(info.hit_p), hit_n(info.hit_n) {
        shape = info.shape;
    }


    // value
    Point3D hit_p;
    Normal hit_n;
    Shape *shape;

};

#endif //UTIL_INTERSECT_DETAIL_H
