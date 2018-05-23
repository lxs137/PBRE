//
// Created by liao xiangsen on 2018/5/23.
//

#ifndef PBRE_FILE_UTIL_H
#define PBRE_FILE_UTIL_H

unsigned char *get_png_file_data(int png_x, int png_y, unsigned char *image_data, int *file_data_len);

unsigned char *stbi_zlib_compress(unsigned char *data, int data_len, int *out_len, int quality);

#endif //PBRE_FILE_UTIL_H
