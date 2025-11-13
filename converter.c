#include "converter.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "image.h"

static const char ASCII_CHARS[] = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

char pixel_to_ascii(unsigned char red, unsigned char green, unsigned char blue){
    float brightness = (0.2126*red + 0.7152*green + 0.0722*blue ) / 255.0f; //normalised
    
    int index = (int)(brightness * (strlen(ASCII_CHARS) - 1));

    return ASCII_CHARS[index];

}


void convert_to_ascii(Image *img, int target_width){
    if(target_width == 0){
        target_width = img->width;
    }
    float scale_x = (float)img->width / target_width;
    int target_height = (int)((float)img->height / scale_x / 2.0f);
    float scale_y = (float)img->height / target_height;

    for(int x = 0 ; x < target_width; x++){
        for(int y = 0; y< target_height; y++){
            int img_x = (int)(x * scale_x);
            int img_y = (int)(y * scale_y);

            if (img_x >= img->width) img_x = img->width - 1;
            if (img_y >= img->height) img_y = img->height - 1;

            int index = (img_x * img->width + img_y) * img->channels;
            unsigned char r = img->data[index + 0];
            unsigned char g = img->data[index + 1];
            unsigned char b = img->data[index + 2];
            
            // Convert to ASCII and print
            char ascii_char = pixel_to_ascii(r, g, b);
            putchar(ascii_char);
        }
        putchar('\n');
    }
}