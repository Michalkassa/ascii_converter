#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include "stb_image.h"
#include "image.h"


Image* load_image(const char *filename){
    Image* img = malloc(sizeof(Image));
    if (img == NULL){
        fprintf(stderr, "Failed to Load image : %s", stbi_failure_reason());
        return NULL;
    }

    img->data = stbi_load(filename,&img->width, &img->height,&img->channels,4);

    if (!img->data) {
        fprintf(stderr, "Failed to load image: %s\n", stbi_failure_reason());
        free(img); 
        return NULL;
    }

    img->channels = 4;

    printf("Loaded image: %dx%d, %d channels\n", 
           img->width, img->height, img->channels);
    
    return img;

}

void free_image(Image* img){
    if(img){
        if(img->data){
            stbi_image_free(img->data);
        }
        free(img);
    }
}