//
// Created by lxs on 17-3-25.
//

#ifndef PBRE_UTIL_FILE_HELPER_H
#define PBRE_UTIL_FILE_HELPER_H

#include <vector>
#include <array>
#include <string>

#include "shape/polygon.h"
#include "shape/mesh.h"

namespace pbre {
  TriMesh *create_mesh_from_obj(Transform &obj_to_world, const char *filename);

  //void parse_obj2polygon(std::vector<Polygon> &shape, const char *filename);
  void write_png_file(int image_x, int image_y, int **rgb, const std::string &filename);
}

#endif //PBRE_UTIL_FILE_HELPER_H
