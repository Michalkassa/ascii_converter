#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"
#include "../include/converter.h"
#include "raylib.h"
#include "raymath.h"

#define SCREEN_WIDTH 1300
#define SCREEN_HEIGHT 1000


int main(int argc, char** argv){
    char *input_file_path = NULL;
    char *output_file_name = NULL;
    int target_width = 80;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ASCII Image Converter");
    SetTargetFPS(60);
    
    if( argc != 4 ){
        printf("Please run : ascii_converter [input_file_path] [output_file_name] [ascii_image_width]\n");
        return 1;
    }
    input_file_path = argv[1];
    output_file_name = argv[2];
    target_width = atoi(argv[3]);
    
    printf("Loading image: %s\n", input_file_path);
    Image img = load_image(input_file_path);
    
    if (img.data == NULL) {
        free_image(img);
        fprintf(stderr, "Error: Failed to load image '%s'\n", input_file_path);
        return 1;
    }
    
    printf("Converting to ASCII (width: %d characters)...\n\n", target_width);
    
    int terminal_display = convert_to_ascii_stdout(&img, target_width);
    if(terminal_display){
        fprintf(stderr, "Error: Failed to display to Terminal (STDOUT) \n");
        return 1;
    }

    int txt_file_display = convert_to_ascii_txt(&img, output_file_name ,target_width);
    int png_file_display = convert_to_png(&img, "output.png", target_width);

    if(txt_file_display || png_file_display){
        free_image(img);
        fprintf(stderr, "Error: Failed to display to file. \n");
        return 1;
    }
    
    double screen_aspect_ratio = (double) SCREEN_WIDTH/(double) SCREEN_HEIGHT;
    Image image = LoadImage("output.png");
    double image_aspect_ratio = (double)image.width / (double)image.height;
    Texture2D texture = LoadTextureFromImage(image);         

    texture.width = SCREEN_WIDTH;
    texture.height = SCREEN_HEIGHT * screen_aspect_ratio * 1/image_aspect_ratio;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(texture, SCREEN_WIDTH/2 - texture.width/2, SCREEN_HEIGHT/2 - texture.height/2, WHITE);
        EndDrawing();
    }
    
    UnloadImage(image);
    CloseWindow();
    free_image(img);
    return 0;
}
