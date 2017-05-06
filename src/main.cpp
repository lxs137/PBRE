#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <cstring>
#include "shape/polygon.h"
#include "util/file_util/file_helper.h"
#include "sampler/disk_sampler.h"
#include "sampler/multi_class_disk.h"
#include "util/color_converse.h"
int main(int argv, char** argc)
{
    if(argv <= 1 || (argv >= 2 && strcmp(argc[1], "--help") == 0)) {
        std::cout<<"usage:"<<std::endl;
        std::cout<<"--class class_num --distance dis_1 dis_2 dis_3..."<<std::endl;
        return 0;
    }
    else if(strcmp(argc[1], "--class") == 0 && atoi(argc[2]) == 1 && argv >=5)
    {
        float distance = (float)atof(argc[4]);
        int resolution = 600;
        std::vector<std::array<float, 2>> samples;
        double start_t = clock(), end_t;
        generate_poisson_sample(1, 1, distance, 30, samples);
        end_t = clock();
        std::cout<<"Generate "<<samples.size()<<" samples."<<std::endl;
#ifdef WIN32
        std::cout<<"Cost time: "<<(end_t - start_t)/CLK_TCK<<" s\n";
#elif linux
        std::cout<<"Cost time: "<<(end_t - start_t)/CLOCKS_PER_SEC<<" s\n";
#endif

        int pixel_size = resolution * resolution * 3;
        int **rgb;
        rgb = new int* [pixel_size];
        int *ptr = new int [pixel_size*3];
        for(int i = 0; i < pixel_size; i++, ptr += 3)
        {
            rgb[i] = ptr;
            rgb[i][0] = 0, rgb[i][1] = 0, rgb[i][2] = 0;
        }
        int index;
        for(auto point: samples)
        {
            point[0] *= resolution, point[1] *= resolution;
            index = ((int)point[1]) * resolution + (int)point[0];
            rgb[index][0] = 255, rgb[index][1] = 255, rgb[index][2] = 255;
        }
        write_png_file(resolution, resolution, rgb, "output.png");
        delete [](rgb[0]);
        delete []rgb;
    }
    else if(strcmp(argc[1], "--class") == 0 && atoi(argc[2]) > 1 && argv >= 6)
    {
        int CLASS_N = atoi(argc[2]);
        int RESOLUTION = 600;

        float *min_dis = new float[CLASS_N];
        if(argv < 4 + CLASS_N)
            return 0;
        else {
            for(int i = 0; i < CLASS_N; i++)
                min_dis[i] = (float)atof(argc[4+i]);
        }
        double start_t = clock(), end_t;
        MultiClassDiskSampler sampler = MultiClassDiskSampler(0, 1, 0, 1, CLASS_N, min_dis);
        end_t = clock();
#ifdef WIN32
        std::cout<<"Cost time: "<<(end_t - start_t)/CLK_TCK<<" s\n";
#elif linux
        std::cout<<"Cost time: "<<(end_t - start_t)/CLOCKS_PER_SEC<<" s\n";
#endif
        int pixel_size = RESOLUTION * RESOLUTION * 3;
        int **rgb, **rgb_all;
        rgb = new int* [pixel_size];
        rgb_all = new int* [pixel_size];
        int *ptr = new int [pixel_size*3];
        int *ptr_all = new int [pixel_size*3];
        for(int i = 0; i < pixel_size; i++, ptr += 3, ptr_all += 3)
        {
            rgb[i] = ptr;
            rgb[i][0] = 0, rgb[i][1] = 0, rgb[i][2] = 0;
            rgb_all[i] = ptr_all;
            rgb_all[i][0] = 0, rgb_all[i][1] = 0, rgb_all[i][2] = 0;
        }
        ComplexSample point;
        int index;
        int point_color[3];
        float hsv_color[3] = {0, 0.7f, 1.f};
        for(int i = 0; i < CLASS_N; i++)
        {
            HSV_2_RGB(hsv_color, point_color);
            hsv_color[0] += 360.0/CLASS_N;
            std::cout<<"Class_"<<i<<" generate samples: "<<sampler.get_sampler_count(i)<<std::endl;
            while(sampler.get_sample(i, point))
            {
                point.cam.x *= RESOLUTION, point.cam.y *= RESOLUTION;
                index = ((int)point.cam.y) * RESOLUTION + (int)point.cam.x;
                rgb[index][0] = point_color[0];
                rgb[index][1] = point_color[1];
                rgb[index][2] = point_color[2];
                rgb_all[index][0] = point_color[0];
                rgb_all[index][1] = point_color[1];
                rgb_all[index][2] = point_color[2];
            }
            char file_name[20];
            std::sprintf(file_name, "output_class_%d.png", i);
            write_png_file(RESOLUTION, RESOLUTION, rgb, file_name);
            memset(rgb[0], 0, RESOLUTION*RESOLUTION*3*sizeof(int));
        }
        write_png_file(RESOLUTION, RESOLUTION, rgb_all, "output_total.png");
        delete []min_dis;
        delete [](rgb[0]);
        delete [](rgb_all[0]);
        delete []rgb;
        delete []rgb_all;

    }

    return 0;
}
