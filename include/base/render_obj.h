//
// Created by liao xiangsen on 2018/5/24.
//

#ifndef PBRE_BASE_RENDER_OBJ_H
#define PBRE_BASE_RENDER_OBJ_H

#include <memory>

#include "base/geometry.h"
#include "base/intersect_detail.h"
#include "shape/shape.h"
#include "util/transform.h"

namespace pbre {
  class Renderable {
  public:
    virtual ~Renderable() {}
    virtual BBox getBBox() const = 0;
    virtual bool intersectP(const Ray &ray) const = 0;
    virtual bool intersect(const Ray &ray, float &t_hit, IntersectInfo &info) const = 0;
  };

  class RenderObj : public Renderable {
  public:
    BBox getBBox() const {
      return shape->getBBox();
    }
    bool intersectP(const Ray &ray) const ;
    bool intersect(const Ray &ray, float &t_hit, IntersectInfo &info) const ;
  private:
    std::shared_ptr<Shape> shape;
  };

  class TransRenderObj : public Renderable {
  public:
    BBox getBBox() const {
      return world2Obj(renderObj->getBBox());
    }
    bool intersectP(const Ray &ray) const ;
    bool intersect(const Ray &ray, float &t_hit, IntersectInfo &info) const ;
  private:
    std::shared_ptr<RenderObj> renderObj;
    Transform world2Obj;
  };
}

#endif //PBRE_BASE_RENDER_OBJ_H
