//
// Created by lxs on 17-3-21.
//

#ifndef PBRE_BASE_INTERSECT_DETAIL_H
#define PBRE_BASE_INTERSECT_DETAIL_H

#include "base/geometry.h"

namespace pbre {
  class Shape;

  class IntersectInfo {
  public:
    IntersectInfo() {
      u = v = 0.f;
      shape = nullptr;
    }

    IntersectInfo(const Point3D &p, const Normal &n, const Shape *shape_ptr, float _u, float _v,
                  const Vector3D &_dpdu, const Vector3D &_dpdv, const Normal &_dndu, const Normal &_dndv) {
      hitP = p;
      hitN = n;
      shape = shape_ptr;
      u = _u, v = _v;
      dpdu = _dpdu, dpdv = _dpdv;
      dndu = _dndu, dndv = _dndv;
    }

    IntersectInfo(const IntersectInfo &info) {
      hitP = info.hitP;
      hitN = info.hitN;
      shape = info.shape;
      u = info.u, v = info.v;
      dpdu = info.dpdu, dpdv = info.dpdv;
      dndu = info.dndu, dndv = info.dndv;
    }

    Point3D hitP;
    Normal hitN;
    const Shape *shape;

    // Surface Parameter Coord
    // Point On Surface: p = f(u, v)
    float u, v;
    Vector3D dpdu, dpdv;
    // Normal Change Rate
    Normal dndu, dndv;
  };
}

#endif //PBRE_BASE_INTERSECT_DETAIL_H
