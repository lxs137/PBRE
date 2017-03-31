//
// Created by lxs on 17-3-25.
//

#ifndef UTIL_FILE_HELPER_H
#define UTIL_FILE_HELPER_H

#include <vector>
#include "../shape/polygon.h"

void parse_obj2polygon(std::vector<Polygon> &shape, const char *filename);
void write_png_file(int image_x, int image_y, float rgb[], const std::string &filename);

#endif //UTIL_FILE_HELPER_H
