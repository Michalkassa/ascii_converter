#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "converter.h"



int main(int argc, char** argv){
    char *input_file_path = NULL;
    char *output_file_name = NULL;
    int target_width = 80;

    if( argc != 4 ){
        printf("Please run : ascii_converter [input_file_path] [output_file_name] [ascii_image_width]\n");
        return 1;
    }
    input_file_path = argv[1];
    output_file_name = argv[2];
    target_width = atoi(argv[3]);

    printf("Loading image: %s\n", input_file_path);
    Image *img = load_image(input_file_path);

    if (!img) {
        free_image(img);
        fprintf(stderr, "Error: Failed to load image '%s'\n", input_file_path);
        return 1;
    }
    
    printf("Converting to ASCII (width: %d characters)...\n\n", target_width);
    // int terminal_display = convert_to_ascii(img, target_width);
    // if(terminal_display){
    //     fprintf(stderr, "Error: Failed to display to Terminal (STDOUT) \n");
    //     return 1;
    // }
    int file_display = convert_to_ascii_file(img, output_file_name ,target_width);

    if(file_display){
        free_image(img);
        fprintf(stderr, "Error: Failed to display to file. \n");
        return 1;
    }

    free_image(img);
    return 0;
}
