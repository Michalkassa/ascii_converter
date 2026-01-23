#ifndef CONVERTER_H
#define CONVERTER_H

#include "image.h"

char pixel_to_ascii(unsigned char red, unsigned char green, unsigned char blue);
int convert_to_ascii_stdout(Image *img,int target_width);
int convert_to_ascii_txt(Image *img, char* file_name, int target_width);
int convert_to_png(Image *img, const char *file_name, int target_width);
#endif