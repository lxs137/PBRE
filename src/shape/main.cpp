#include <iostream>
#include <cmath>
#include <vector>
#include "plane.h"
int main(int argv, char** argc)
{
    Point3D plane_p0 = Point3D(0.f, 0.f, 0.f), ray_o = Point3D(2.f, 2.f, 1.f);
    Vector3D ray_d = Vector3D(1.f, 2.f, 3.f);
    Normal plane_n = Normal(1.0f, 1.0f, 1.0f);
    Plane m_plane = Plane(plane_p0, plane_n);
    Ray m_ray = Ray(ray_o, ray_d);
    bool intersect = m_plane.intersectP(m_ray);
    std::cout<<"If intersect: "<<intersect<<std::endl;
    std::cout<<"Test: "<<min(1, 4)<<std::endl;
    return 0;
}
