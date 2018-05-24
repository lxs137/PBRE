//
// Created by lxs on 17-3-22.
//

#include "shape/polygon.h"

namespace pbre {
  BBox Polygon::getBBox() {
    Point3D p_min = Point3D(vertics[0]), p_max = Point3D(vertics[0]);
    for (Point3D p : vertics) {
      p_min.x = min(p_min.x, p.x), p_max.x = max(p_max.x, p.x);
      p_min.y = min(p_min.y, p.y), p_max.y = max(p_max.y, p.y);
      p_min.z = min(p_min.z, p.z), p_max.z = max(p_max.z, p.z);
    }
    return BBox(p_min, p_min);
  }

  bool Polygon::intersectP(const Ray &ray) {
    float parallel_test = AbsDot(ray.d, this->n);
    // 当多边形所在平面与光线平行时,多边形与光线一点没有交点
    if (parallel_test < INTERSECT_TEST_PRECISION)
      return false;
    else {
      float hit_t = Dot((this->vertics[0] - ray.o), this->n) / Dot(ray.d, this->n);
      if (hit_t > ray.min_t && hit_t < ray.max_t) {
        // 将3维的点与多边形投影到平面上,判断交点是否落在平面内
        Point3D hit_p = ray(hit_t);
        float hit_p_x = hit_p.x, hit_p_y = hit_p.y;
        int intersect_num = 0;
        int vertics_num = (int) (this->vertics.size());
        // 以投影后的交点为起点,向x轴正方向做一条射线
        // 根据射线与多边形交点个数的奇偶性判断改点是否在多边形内
        Point2D p1, p2 = {vertics[0].x, vertics[0].y};
        for (int i = 0; i < vertics_num; i++) {
          p1 = p2;
          p2 = {vertics[(i + 1) % vertics_num].x, vertics[(i + 1) % vertics_num].y};
          float dy1 = hit_p_y - p1.y, dy2 = hit_p_y - p2.y;
          if ((hit_p_x - p1.x > INTERSECT_TEST_PRECISION && hit_p_x - p2.x > INTERSECT_TEST_PRECISION)
              || (dy1 > INTERSECT_TEST_PRECISION && dy2 > INTERSECT_TEST_PRECISION)
              || (-dy1 > INTERSECT_TEST_PRECISION && -dy2 > INTERSECT_TEST_PRECISION))
            continue;
            // 判断多边形是否有顶点与射线相交
          else if ((std::fabs(dy1) < INTERSECT_TEST_PRECISION && std::fabs(dy2) < INTERSECT_TEST_PRECISION)
                   || (std::fabs(dy1) < INTERSECT_TEST_PRECISION && p1.y < p2.y)
                   || (std::fabs(dy2) < INTERSECT_TEST_PRECISION && p2.y < p1.y))
            continue;
          else
            intersect_num++;
        }
        return (intersect_num % 2 != 0);
      } else
        return false;
    }

//    BBox bound_box = get_BBox();
//    if(!bound_box.intersectP(ray))
//        return false;
  }

  bool Polygon::intersect(const Ray &ray, float &t_hit, IntersectInfo &info) {
    float parallel_test = AbsDot(ray.d, this->n);
    // 当多边形所在平面与光线平行时,多边形与光线一点没有交点
    if (parallel_test < 1e-5)
      return false;
    else {
      t_hit = Dot((this->vertics[0] - ray.o), this->n) / Dot(ray.d, this->n);
      if (t_hit > ray.min_t && t_hit < ray.max_t) {
        // 将3维的点与多边形投影到平面上,判断交点是否落在平面内
        Point3D hit_p = ray(t_hit);
        float hit_p_x = hit_p.x, hit_p_y = hit_p.y;
        int intersect_num = 0;
        int vertics_num = (int) (this->vertics.size());
        // 以投影后的交点为起点,向x轴正方向做一条射线
        // 根据射线与多边形交点个数的奇偶性判断改点是否在多边形内
        Point2D p1, p2 = {vertics[0].x, vertics[0].y};
        for (int i = 0; i < vertics_num; i++) {
          p1 = p2;
          p2 = {vertics[(i + 1) % vertics_num].x, vertics[(i + 1) % vertics_num].y};
          float dy1 = hit_p_y - p1.y, dy2 = hit_p_y - p2.y;
          if ((hit_p_x - p1.x > INTERSECT_TEST_PRECISION && hit_p_x - p2.x > INTERSECT_TEST_PRECISION)
              || (dy1 > INTERSECT_TEST_PRECISION && dy2 > INTERSECT_TEST_PRECISION)
              || (-dy1 > INTERSECT_TEST_PRECISION && -dy2 > INTERSECT_TEST_PRECISION))
            continue;
            // 判断多边形是否有顶点与射线相交
          else if ((std::fabs(dy1) < INTERSECT_TEST_PRECISION && std::fabs(dy2) < INTERSECT_TEST_PRECISION)
                   || (std::fabs(dy1) < INTERSECT_TEST_PRECISION && p1.y < p2.y)
                   || (std::fabs(dy2) < INTERSECT_TEST_PRECISION && p2.y < p1.y))
            continue;
          else
            intersect_num++;
        }
        if (intersect_num % 2 == 0)
          return false;
        else {
          info.hit_p = hit_p;
          info.hit_n = this->n;
          info.shape = this;
          return true;
        }
      } else
        return false;
    }
  }
}