//
// Created by lxs on 17-4-12.
//

#include "shape/triangle.h"

#include "shape/mesh.h"

BBox Triangle::get_BBox() {
    if(owner == nullptr)
        return BBox();
    BBox b;
    b.update(owner->vertics[v1]);
    b.update(owner->vertics[v2]);
    b.update(owner->vertics[v3]);
    return b;
}

// Fast,Minimum Storage Ray Triangle Intersection
// http://www.graphics.cornell.edu/pubs/1997/MT97.pdf
// 运用克莱姆法则和向量混合积公式
// 交点 = u*p1 + v*p2 + (1-u-v)*p3 = ray.o + t*ray.d
// E2 = p2 - p1, E3 = p3 - p1, T = ray.o - p1, P = Cross(ray.d, E3), Q = Cross(T, E2)
// t = Dot(Q, E3)/Dot(P, E2)
// u = Dot(P, T)/Dot(P, E2)
// v = Dot(Q, ray.d)/Dot(P, E2)
bool Triangle::intersect(const Ray &ray, float &t_hit, IntersectInfo &info) {
    Point3D &p1 = owner->vertics[v1], &p2 = owner->vertics[v2], &p3 = owner->vertics[v3];
    Vector3D E2 = p2 - p1, E3 = p3 - p1, P = Cross(ray.d, E3), Q, T;
    float parallel_test = Dot(P, E2), parallel_1, u, v;
    // 判断是否光线与三角形是否平行
    if(std::fabs(parallel_test) < INTERSECT_TEST_PRECISION)
        return false;
    parallel_1 = 1.f/parallel_test;
    // 判断交点是否在三角形内
    T = ray.o - p1;
    u = Dot(P, T) * parallel_1;
    if(u < 0.f || u > 1.f)
        return false;
    Q = Cross(T, E2);
    v = Dot(Q, ray.d) * parallel_1;
    if(v < 0.f || v > 1.f || (u+v) > 1.f)
        return false;
    // 计算t
    float t = Dot(Q, E3) * parallel_1;
    if(t < ray.min_t || t > ray.max_t)
        return false;
    t_hit = t;
    // 计算交点坐标
    info.hit_p = ray(t_hit);
    info.shape = this;
    info.hit_n = Normal();
//    info.hit_n = Normalize(owner->normals[v1] + owner->normals[v2] + owner->normals[v3]);
    return true;
}

bool Triangle::intersectP(const Ray &ray) {
    Point3D &p1 = owner->vertics[v1], &p2 = owner->vertics[v2], &p3 = owner->vertics[v3];
    Vector3D E2 = p2 - p1, E3 = p3 - p1, P = Cross(ray.d, E3), Q, T;
    float parallel_test = Dot(P, E2), parallel_1, u, v;
    // 判断是否光线与三角形是否平行
    if(std::fabs(parallel_test) < INTERSECT_TEST_PRECISION)
        return false;
    parallel_1 = 1.f/parallel_test;
    // 判断交点是否在三角形内
    T = ray.o - p1;
    u = Dot(P, T) * parallel_1;
    if(u < 0.f || u > 1.f)
        return false;
    Q = Cross(T, E2);
    v = Dot(Q, ray.d) * parallel_1;
    if(v < 0.f || v > 1.f || (u+v) > 1.f)
        return false;
    // 计算t
    float t = Dot(Q, E3) * parallel_1;
    if(t < ray.min_t || t > ray.max_t)
        return false;
    return true;
}