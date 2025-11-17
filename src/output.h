#ifndef OUTPUT_H
#define OUTPUT_H
#include "image.h"

void stdout_print(unsigned char red, unsigned char green, unsigned char blue, unsigned char character);

void file_print(FILE* file, unsigned char character);

#endif