//
// Created by lxs on 17-3-25.
//

#ifndef UTIL_FILE_HELPER_H
#define UTIL_FILE_HELPER_H

#include <vector>
#include <array>
#include <string>
#include "../../shape/polygon.h"
#include "../../shape/mesh/mesh.h"

TriMesh *create_mesh_from_obj(Transform &obj_to_world, const char *filename);
//void parse_obj2polygon(std::vector<Polygon> &shape, const char *filename);
void write_png_file(int image_x, int image_y, int **rgb, const std::string &filename);
unsigned char* get_png_file_data(int png_x, int png_y, unsigned char *image_data, int *file_data_len);
unsigned char* stbi_zlib_compress(unsigned char *data, int data_len, int *out_len, int quality);

#endif //UTIL_FILE_HELPER_H
