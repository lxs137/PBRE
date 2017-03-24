#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include "polygon.h"
#include "../util/intersect_detail.h"
int main(int argv, char** argc)
{
    std::vector<Point3D> vertics;
//    if(argv < 1 || (argv > 1 && strcmp(argc[1], "--help"))) {
//        std::cout<<"--points (x,y,z)"<<std::endl;
//        return 0;
//    }
//    else if(strcmp(argc[1], "--file")){
//        std::ifstream if_file(std::string(argc[2]));
//
//    }
//    else if(strcmp(argc[1], "--points")){
//        int points_n = argv - 1;
//
//    }
    vertics.push_back(Point3D(1,0,0));
    vertics.push_back(Point3D(0,1,0));
    vertics.push_back(Point3D(0,0,1));

    Point3D ray_o = Point3D(0,0,0);
    Vector3D ray_d = Vector3D(1, 0, 0);
    Ray m_ray = Ray(ray_o, ray_d);

    Polygon m_polygon = Polygon(vertics);
    IntersectInfo info;
    float hit_t;
    std::cout<<"intersect:"<<m_polygon.intersect(m_ray, hit_t, info)<<std::endl;
    std::cout<<"("<<info.hit_p.x<<","<<info.hit_p.y<<","<<info.hit_p.z<<")"<<std::endl;
    return 0;
}
