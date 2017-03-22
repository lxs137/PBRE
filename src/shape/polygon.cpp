//
// Created by lxs on 17-3-22.
//

#include "polygon.h"
#include "plane.h"
#include <vector>

BBox Polygon::get_BBox() {
    Point3D p_min =Point3D(vertics[0]), p_max = Point3D(vertics[0]);
    for(Point3D p : vertics)
    {
        p_min.x = min(p_min.x, p.x), p_max.x = max(p_max.x, p.x);
        p_min.y = min(p_min.y, p.y), p_max.y = max(p_max.y, p.y);
        p_min.z = min(p_min.z, p.z), p_max.z = max(p_max.z, p.z);
    }
    return BBox(p_min, p_min);
};
bool Polygon::intersectP(const Ray &ray) {
    BBox bound_box = get_BBox();
    if(!bound_box.intersectP(ray))
        return false;
    else
    {
        float t_hit;
        IntersectInfo info = IntersectInfo();
        if(Plane(this->vertics, this->n).intersect(ray, t_hit, info))
        {
            float hit_x = info.hit_p.x, hit_y = info.hit_p.y;

        } else
            return false;
    }
};
bool Polygon::intersect(const Ray &ray, float &t_hit, IntersectInfo &info) {
    return false;
}