//
// Created by lxs on 17-3-21.
//

#ifndef UTIL_INTERSECT_DETAIL_H
#define UTIL_INTERSECT_DETAIL_H

#include "../util/geometry.h"
#include "../shape/shape.h"

class IntersectInfo {
public:
    // method
    IntersectInfo() {}
    IntersectInfo(const Point3D &p, const Normal &n, Shape *shape_ptr) {
        hit_p = p;
        hit_n = n;
        shape = shape_ptr;
    }
    IntersectInfo(const IntersectInfo &info) {
        hit_p = info.hit_p;
        hit_n = info.hit_n;
        shape = info.shape;
    }


    // value
    Point3D hit_p;
    Normal hit_n;
    Shape *shape;

};

#endif //UTIL_INTERSECT_DETAIL_H
