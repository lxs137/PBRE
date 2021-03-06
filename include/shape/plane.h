//
// Created by lxs on 17-3-21.
//

#ifndef PBRE_SHAPE_PLANE_H
#define PBRE_SHAPE_PLANE_H

#define PLANE_EPSILON 1e-3

#include "shape.h"

namespace pbre {

  class Plane : public Shape {
  public:
    Plane() : Shape(), Epsilon(PLANE_EPSILON) {
      p = Point3D();
      n = Normal();
    }

    Plane(const Point3D &pp, const Normal &nn) : Shape(), Epsilon(PLANE_EPSILON) {
      p = pp, n = nn;
    }

    Plane(const Point3D &p1, const Point3D &p2, const Point3D &p3) : Shape(), Epsilon(PLANE_EPSILON) {
      p = p1;
      Vector3D v1 = p1 - p2, v2 = p1 - p3;
      n = Normal(Cross(v1, v2));
    }

    Plane(const Plane *plane) : Shape(), Epsilon(PLANE_EPSILON) {
      p = plane->p, n = plane->n;
    }

    virtual BBox getBBox() const ;
    virtual bool intersectP(const Ray &ray) const ;
    virtual bool intersect(const Ray &ray, float &t_hit, IntersectInfo &info) const ;

  private:
    Point3D p;
    Normal n;
    const float Epsilon;
  };

}

#endif //PBRE_SHAPE_PLANE_H
