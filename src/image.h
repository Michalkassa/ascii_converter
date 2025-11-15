#ifndef IMAGE_H
#define IMAGE_H
typedef struct{
    unsigned char* data;
    int width;
    int height;
    int channels;
}Image;

Image* load_image(const char* file_name);

void free_image(Image* img);

#endif