//
// Created by lxs on 17-3-25.
//

#ifndef UTIL_FILE_HELPER_H
#define UTIL_FILE_HELPER_H

#include <vector>
#include "../shape/polygon.h"

void parse_obj2polygon(std::vector<Polygon> &shape, const char *filename);

#endif //UTIL_FILE_HELPER_H
