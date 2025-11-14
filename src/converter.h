#ifndef CONVERTER_H
#define CONVERTER_H

#include "image.h"

char pixel_to_ascii(unsigned char red, unsigned char green, unsigned char blue);

void convert_to_ascii(Image *img, int target_width);

#endif