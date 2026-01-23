#include "../include/image.h"
#include <stdio.h>
#include "raylib.h"

Image load_image(const char *filename) {
    Image img = LoadImage(filename);  
    if (img.data == NULL) {
        fprintf(stderr, "Failed to load image: %s\n", filename);
    } else {
        printf("Loaded image: %dx%d, 4 channels (RGBA)\n",
               img.width, img.height);
    }
    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8);
    return img;
}


void free_image(Image img) {
    UnloadImage(img);  
}
