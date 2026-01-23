#ifndef IMAGE_H
#define IMAGE_H
#include "raylib.h"

Image load_image(const char* file_name);

void free_image(Image img);

#endif