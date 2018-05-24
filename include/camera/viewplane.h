//
// Created by lxs on 17-3-30.
//

#ifndef PBRE_CAMERA_VIEWPLANE_H
#define PBRE_CAMERA_VIEWPLANE_H

#include <string>

#include "util/file_helper.h"
#include "util/color_converse.h"

namespace pbre {
  struct Pixel
  {
    union {
      float xyz[3];
      struct {
        float x, y, z;
      };
    };
  };
  enum ImageFormat {
    PNG, JPG
  };

  class ViewPlane
  {
  public:
    ViewPlane() {
      x_resolution = y_resolution = 0;
      pixels = nullptr;
      image_name = "output.png";
    }
    ViewPlane(int x, int y, const std::string &file);
    ~ViewPlane() {
      if(pixels == nullptr)
        return;
      delete[] pixels[0];
      delete[] pixels;
    }
    void write_image(ImageFormat format = PNG);
    int x_resolution, y_resolution;
    Pixel **pixels;
    std::string image_name;
  };
}
#endif //PBRE_CAMERA_VIEWPLANE_H
