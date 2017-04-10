#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <exception>
#include "polygon.h"
#include "../util/file_util/file_helper.h"
//#include "../util/transform.h"
int main(int argv, char** argc)
{
    int x_resolution = 100, y_resolution = 100;
    int pixel_size = y_resolution*x_resolution*3;
    int **rgb;
    rgb = new int* [pixel_size];
    for(int i = 0; i < pixel_size; i++)
    {
        rgb[i] = new int [3];
        rgb[i][0] = 250, rgb[i][1] = 0, rgb[i][2] = 0;
    }
    write_png_file(x_resolution, y_resolution, rgb, "output.png");
    for(int i = 0; i < pixel_size; i++)
        delete []rgb[i];
    delete []rgb;
//    stbi_write_png("output.png", 1, 100, 3, rgb, 3);
//    Matrix4_4 matrix(-1,-1,-2,3,
//                     -3,2,5,-5,
//                     3,2,1,-4,
//                     4,-3,-2,-1);
//    Matrix4_4 inverse = matrix.Inverse();
//    float a = matrix.Norm();
//    inverse.Norm();
//    if(argv <= 1 || (argv >= 2 && strcmp(argc[1], "--help") == 0)) {
//        std::cout<<"usage:"<<std::endl;
//        std::cout<<"--file OBJ_file --ray [Ox,Oy,Oz] [Dx,Dy,Dz]"<<std::endl;
//        return 0;
//    }
//    else if(strcmp(argc[1], "--file") == 0){
//        std::vector<Polygon> polygons;
//        parse_obj2polygon(polygons, argc[2]);
//        Ray test_ray;
//        if(strcmp(argc[3], "--ray") == 0)
//        {
//            try {
//                std::string o_str(argc[4]);
//                std::string d_str(argc[5]);
//                o_str = o_str.substr(1, o_str.size() - 2);
//                d_str = d_str.substr(1, d_str.size() - 2);
//                unsigned long index1 = o_str.find(','), index2 = o_str.rfind(',');
//                float x, y, z;
//                x = std::stof(o_str.substr(0, index1));
//                y = std::stof(o_str.substr(index1 + 1, index2 - index1 - 1));
//                z = std::stof(o_str.substr(index2 + 1));
//                Point3D origin(x, y, z);
//                index1 = d_str.find(','), index2 = d_str.rfind(',');
//                x = std::stof(d_str.substr(0, index1));
//                y = std::stof(d_str.substr(index1 + 1, index2 - index1 - 1));
//                z = std::stof(d_str.substr(index2 + 1));
//                Vector3D direction(x, y, z);
//                test_ray = Ray(origin, direction);
//            } catch (std::exception &e)
//            {
//                std::cout<<"Error coordinate syntax"<<std::endl;
//            }
//        }
//        IntersectInfo info;
//        float hit_t;
//
//        double start_t = clock(), end_t;
//        for(Polygon polygon : polygons)
//        {
//            if(polygon.intersect(test_ray, hit_t, info))
//            {
//                std::cout<<"Intersect: "<<std::endl;
//                std::vector<Point3D> hit_polygon_points = polygon.get_vertics();
//                std::cout<<"Hit polygon: ";
//                for(Point3D p : hit_polygon_points)
//                    std::cout<<"("<<p.x<<","<<p.y<<","<<p.z<<")  ";
//                std::cout<<std::endl;
//                std::cout<<"Hit point: ("<<info.hit_p.x<<","<<info.hit_p.y<<","<<info.hit_p.z<<")"<<std::endl;
//            }
//        }
//        end_t = clock();
//#ifdef WIN32
//        std::cout<<"Cost time: "<<(end_t - start_t)/CLK_TCK<<" s\n";
//#elif linux
//        std::cout<<"Cost time: "<<(end_t - start_t)/CLOCKS_PER_SEC<<" s\n";
//#endif
//    }
//
//    return 0;
}
