# ASCII Image Converter

A lightweight C program that loads an image and converts it into ASCII art for display in your terminal.

## Project Overview

The program:
- Prints the ASCII output directly to the terminal
- Allows specifying the output width to match your terminal size
- Makes use of stb_image.h ( in the future i am looking to implement a bitmap parser myself )


## Building

Run the following to compile:

```sh
make
```

## Usage
```sh
./main [filename] [terminal_width]
```

## Example
```sh
./main image.png 80
```