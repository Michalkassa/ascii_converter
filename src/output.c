#include <stdio.h>

void stdout_print(unsigned char red, unsigned char green, unsigned char blue, unsigned char character){
    printf("\x1b[38;2;%d;%d;%dm%c", red, green, blue, character);
    printf("\x1b[0m");
}

void file_print(FILE* file, unsigned char character){
    fputc(character,file);
}
