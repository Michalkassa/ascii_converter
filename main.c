#include <stdio.h>
#include "image.h"
#include "converter.h"



int main(int argc, char** argv){
    char *filename = NULL;
    int target_width = 100;

    if( argc != 2 ){
        printf("Please run : main [filename] \n");
        return 1;
    }

    filename = argv[1];
    printf("Loading image: %s\n", filename);
    Image *img = load_image(filename);

    if (!img) {
        fprintf(stderr, "Error: Failed to load image '%s'\n", filename);
        return 1;
    }
    
    printf("Converting to ASCII (width: %d characters)...\n\n", target_width);
    convert_to_ascii(img, target_width);

    free_image(img);
    return 0;
}