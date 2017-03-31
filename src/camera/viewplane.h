//
// Created by lxs on 17-3-30.
//

#ifndef CAMERA_VIEWPLANE_H
#define CAMERA_VIEWPLANE_H

#include <string>
#include "../util/file_helper.h"

struct Pixel
{
    float X, Y, Z;
};
enum ImageFormat {
    PNG, BMP, JPG
};

class ViewPlane
{
public:
    ViewPlane() {
        x_resolution = y_resolution = 0;
        pixels = NULL;
        image_name = "output.png";
    }
    ViewPlane(int x, int y, const std::string &file) {
        x_resolution = x, y_resolution = y;
        pixels = new Pixel* [y_resolution];
        for(int j = 0; j < y_resolution; j++)
            pixels[j] = new Pixel [x_resolution];
        image_name = file;
    }
    ~ViewPlane() {
        for(int j = 0; j < y_resolution; j++)
            delete [] pixels[j];
        delete []pixels;
    }
    static void write_image(ImageFormat format = PNG) {
        float rgb[];
        // TODO xyz2rgb function
        switch(format)
        {
            case PNG:
                write_png_file(x_resolution, y_resolution, rgb, image_name);
                break;
        }
    }

    int x_resolution, y_resolution;
    Pixel **pixels;
    std::string image_name;
};

#endif //CAMERA_VIEWPLANE_H
