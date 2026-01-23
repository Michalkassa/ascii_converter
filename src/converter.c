#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "converter.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "stb_image_write.h"
#include "raylib.h"
#include "image.h"
#include "output.h"

#define IMAGE_CHANNELS 3

static const char ASCII_CHARS[] = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

char pixel_to_ascii(unsigned char red, unsigned char green, unsigned char blue){
    float brightness = (0.2126*red + 0.7152*green + 0.0722*blue) / 255.0f;
    int index = (int)(brightness * (strlen(ASCII_CHARS) - 1));
    return ASCII_CHARS[index];
}

int convert_to_ascii_stdout(Image *img, int target_width){
    int width = img->width;
    int height = img->height;

    if (target_width <= 0)
        target_width = width * 2; 

    float sample_width = target_width / 2.0f;

    float x_scale = (float)width / sample_width;
    float y_scale = x_scale;

    int target_height = (int)(height / y_scale);

    for (int y = 0; y < target_height; y++){
        int iy = (int)(y * y_scale);
        if (iy >= height) iy = height - 1;

        for (int x = 0; x < sample_width; x++){
            int ix = (int)(x * x_scale);
            if (ix >= width) ix = width - 1;

            int index = (iy * width + ix) * IMAGE_CHANNELS;
            unsigned char r = ((unsigned char*)img->data)[index + 0];
            unsigned char g = ((unsigned char*)img->data)[index + 1];
            unsigned char b = ((unsigned char*)img->data)[index + 2];

            char c = pixel_to_ascii(r, g, b);

            stdout_print(r, g, b, c);
            stdout_print(r, g, b, c);
        }
        stdout_print(0, 0, 0, '\n');
    }

    return 0;
}



int convert_to_ascii_txt(Image *img, char* file_name, int target_width){
    FILE *file = fopen(file_name, "w");
    if (!file) return 1;

    int width = img->width;
    int height = img->height;

    if (target_width <= 0)
        target_width = width * 2; 

    
    float sample_width = target_width / 2.0f;

    float x_scale = (float)width / sample_width;
    float y_scale = x_scale; 

    int target_height = (int)(height / y_scale);

    for (int y = 0; y < target_height; y++){
        int iy = (int)(y * y_scale);
        if (iy >= height) iy = height - 1;

        for (int x = 0; x < sample_width; x++){ 
            int ix = (int)(x * x_scale);
            if (ix >= width) ix = width - 1;

            int index = (iy * width + ix) * IMAGE_CHANNELS;
            unsigned char r = ((unsigned char*)img->data)[index + 0];
            unsigned char g = ((unsigned char*)img->data)[index + 1];
            unsigned char b = ((unsigned char*)img->data)[index + 2];

            char c = pixel_to_ascii(r, g, b);

            file_print(file, c);
            file_print(file, c); // double characters horizontally
        }
        file_print(file, '\n');
    }
    fclose(file);
    return 0;
}

int convert_to_png(Image *img, const char *file_name, int target_width) {
    if (!img || !img->data) return 1;
    if (!IsWindowReady()) return 1;
    
    int width = img->width;
    int height = img->height;
    unsigned char *pixels = (unsigned char*)img->data;
    
    // Determine bytes per pixel based on format
    int bytesPerPixel = 4; // Default to RGBA
    if (img->format == PIXELFORMAT_UNCOMPRESSED_R8G8B8) {
        bytesPerPixel = 3;
    } else if (img->format == PIXELFORMAT_UNCOMPRESSED_R8G8B8A8) {
        bytesPerPixel = 4;
    } else {
        // Convert unsupported formats to RGBA
        ImageFormat(img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
        pixels = (unsigned char*)img->data;
        bytesPerPixel = 4;
    }
    
    // Limit target_width to prevent excessive memory usage
    int max_target_width = 500;  // Adjust based on your needs
    if (target_width <= 0 || target_width > width) target_width = width;
    if (target_width > max_target_width) target_width = max_target_width;
    
    Font font = GetFontDefault();
    Vector2 charSize = MeasureTextEx(font, "A", font.baseSize, 0);
    int charWidth = (int)(charSize.x + 0.5f);
    int charHeight = font.baseSize;
    
    // Calculate aspect ratio of the original image
    float imageAspectRatio = (float)width / height;
    
    // Calculate target_height to match the image aspect ratio
    int target_height = (int)((target_width * 2 * charWidth) / (imageAspectRatio * charHeight) + 0.5f);
    
    int renderWidth = target_width * charWidth * 2;  // 2 chars per position
    int renderHeight = target_height * charHeight;
    
    // Check if dimensions are valid and within GPU limits
    if (renderWidth <= 0 || renderHeight <= 0) {
        fprintf(stderr, "Invalid render dimensions: %dx%d\n", renderWidth, renderHeight);
        return 1;
    }
    
    if (renderWidth > 16384 || renderHeight > 16384) {
        fprintf(stderr, "Render texture too large: %dx%d (max 16384x16384)\n", renderWidth, renderHeight);
        return 1;
    }
    
    // Estimate memory usage (rough approximation)
    long long estimatedMemory = (long long)renderWidth * renderHeight * 4; // 4 bytes per pixel
    long long maxMemory = 512 * 1024 * 1024; // 512MB limit
    if (estimatedMemory > maxMemory) {
        fprintf(stderr, "Estimated memory usage too high: %lld MB\n", estimatedMemory / (1024 * 1024));
        return 1;
    }
    
    RenderTexture2D targetTex = LoadRenderTexture(renderWidth, renderHeight);
    
    // Check if texture was created successfully
    if (targetTex.id == 0) {
        fprintf(stderr, "Failed to create render texture\n");
        return 1;
    }
    
    BeginTextureMode(targetTex);
        ClearBackground(BLACK);
        char charBuffer[2] = {0, 0};
        for (int y = 0; y < target_height; y++) {
            float iy_float = (float)y * height / target_height;
            int iy = (int)iy_float;
            if (iy >= height) iy = height - 1;
            for (int x = 0; x < target_width; x++) {
                float ix_float = (float)x * width / target_width;
                int ix = (int)ix_float;
                if (ix >= width) ix = width - 1;
                
                int index = (iy * width + ix) * bytesPerPixel;
                unsigned char r = pixels[index + 0];
                unsigned char g = pixels[index + 1];
                unsigned char b = pixels[index + 2];
                
                charBuffer[0] = pixel_to_ascii(r, g, b);
                DrawTextEx(font, charBuffer,
                           (Vector2){ x * charWidth * 2, y * charHeight },
                           font.baseSize, 0, (Color){ r, g, b, 255 });
                DrawTextEx(font, charBuffer,
                           (Vector2){ x * charWidth * 2 + charWidth, y * charHeight },
                           font.baseSize, 0, (Color){ r, g, b, 255 });
            }
        }
    EndTextureMode();
    
    Image renderedImg = LoadImageFromTexture(targetTex.texture);
    ImageFlipVertical(&renderedImg);
    ExportImage(renderedImg, file_name);
    UnloadImage(renderedImg);
    UnloadRenderTexture(targetTex);
    
    return 0;
}


int convert_video_raylib(const char *input_video, const char *output_dir, 
                         int target_width) {
    
    char cmd[512];
    sprintf(cmd, "ffmpeg -i %s temp_frames/frame_%%04d.png", input_video);
    system(cmd);
    
    for (int i = 0; ; i++) {
        char inputFile[256];
        sprintf(inputFile, "temp_frames/frame_%04d.png", i);
        
        Image img = LoadImage(inputFile);
        if (img.data == NULL) break; // No more frames
        
        char outputFile[256];
        sprintf(outputFile, "%s/ascii_frame_%04d.png", output_dir, i);
        convert_to_png(&img, outputFile, target_width);
        
        UnloadImage(img);
        printf("Processed frame %d\r", i);
    }
    
    return 0;
}