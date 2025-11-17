#include "converter.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "image.h"
#include "output.h"

static const char ASCII_CHARS[] = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

char pixel_to_ascii(unsigned char red, unsigned char green, unsigned char blue){
    float brightness = (0.2126*red + 0.7152*green + 0.0722*blue ) / 255.0f; //normalised
    
    int index = (int)(brightness * (strlen(ASCII_CHARS) - 1));
    
    return ASCII_CHARS[index];
}

int convert_to_ascii_file(Image *img, char* file_name, int target_width){

    FILE *file = fopen(file_name, "w");
	
	if (file == NULL)
		return 1;

    if (target_width <= 0 || target_width > img->width)
        target_width = img->width;

    float scale = (float)img->width / (float)target_width;

    // Height adjusted for terminal character aspect ratio (~2:1)
    int target_height = (int)((float)img->height / scale / 2.0f);

    for (int y = 0; y < target_height; y++) {

        float img_y = y * scale * 2.0f;

        for (int x = 0; x < target_width; x++) {

            float img_x = x * scale;

            int ix = (int)img_x;
            int iy = (int)img_y;

            if (ix < 0) ix = 0;
            if (iy < 0) iy = 0;
            if (ix >= img->width)  ix = img->width - 1;
            if (iy >= img->height) iy = img->height - 1;

            int index = (iy * img->width + ix) * img->channels;

            unsigned char r = img->data[index + 0];
            unsigned char g = img->data[index + 1];
            unsigned char b = img->data[index + 2];

            char c = pixel_to_ascii(r, g, b);
            stdout_print(r,g,b,c);
            file_print(file,c);
        }
        file_print(file,'\n');
        stdout_print(0,0,0,'\n');
    }
    fclose(file);
    return 0;
}


int convert_to_ascii(Image *img, int target_width){

    if (target_width <= 0 || target_width > img->width)
        target_width = img->width;

    float scale = (float)img->width / (float)target_width;

    // Height adjusted for terminal character aspect ratio (~2:1)
    int target_height = (int)((float)img->height / scale / 2.0f);

    for (int y = 0; y < target_height; y++) {

        float img_y = y * scale * 2.0f;

        for (int x = 0; x < target_width; x++) {

            float img_x = x * scale;

            int ix = (int)img_x;
            int iy = (int)img_y;

            if (ix < 0) ix = 0;
            if (iy < 0) iy = 0;
            if (ix >= img->width)  ix = img->width - 1;
            if (iy >= img->height) iy = img->height - 1;

            int index = (iy * img->width + ix) * img->channels;

            unsigned char r = img->data[index + 0];
            unsigned char g = img->data[index + 1];
            unsigned char b = img->data[index + 2];

            char c = pixel_to_ascii(r, g, b);
            putchar(c);
        }
        putchar('\n');
    }
    return 0;
}