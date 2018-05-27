//
// Created by liao xiangsen on 2018/5/25.
//

#include "base/render_obj.h"

namespace pbre {
  bool RenderObj::intersectP(const pbre::Ray &ray) const {
    return shape->intersectP(ray);
  }

  bool TransRenderObj::intersectP(const pbre::Ray &ray) const {
    Ray transRay = world2Obj(ray);
    return renderObj->intersectP(transRay);
  }
}
