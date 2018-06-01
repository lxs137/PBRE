//
// Created by liao xiangsen on 2018/5/25.
//

#include "base/render_obj.h"

namespace pbre {
  bool RenderObj::intersect(const pbre::Ray &ray, float &t_hit, pbre::IntersectInfo &info) const {
    return false;
  }

  bool RenderObj::intersectP(const pbre::Ray &ray) const {
    return shape->intersectP(ray);
  }

  bool TransRenderObj::intersect(const pbre::Ray &ray, float &t_hit, pbre::IntersectInfo &info) const {
    return false;
  }

  bool TransRenderObj::intersectP(const pbre::Ray &ray) const {
    Ray transRay = world2Obj(ray);
    return renderObj->intersectP(transRay);
  }
}
