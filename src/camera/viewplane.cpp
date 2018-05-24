//
// Created by liao xiangsen on 2018/5/24.
//

#include "camera/viewplane.h"

namespace pbre {
  ViewPlane::ViewPlane(int x, int y, const std::string &file) {
    x_resolution = x, y_resolution = y;
    pixels = new Pixel* [y_resolution];
    Pixel *data = new Pixel[x_resolution * y_resolution];
    for(int i = 0; i < y_resolution; i++, data += x_resolution)
      pixels[i] = data;
    image_name = file;
  }
  void ViewPlane::write_image(pbre::ImageFormat format)  {
    uint8_t **rgb, *rgbData;
    int pixels_num = x_resolution * y_resolution;
    rgb = new uint8_t* [pixels_num];
    rgbData = new uint8_t [pixels_num * 3];
    for(int i = 0; i < pixels_num; i++, rgbData += 3)
      rgb[i] = rgbData;
    for(int y = 0; y < y_resolution; y++) {
      for(int x = 0; x < x_resolution; x++) {
        pbre::XYZToSRGB(pixels[y][x].xyz, rgb[y * x_resolution + x]);
      }
    }
    switch(format)
    {
      case PNG:
        write_png_file(x_resolution, y_resolution, rgb, image_name);
        break;
      case JPG:
        break;
    }
  }
}