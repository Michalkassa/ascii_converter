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
make clean
```

## Usage
```sh
./ascii_converter [input_file_path] [output_file_name] [ascii_image_width]
```

## Example
```sh
./ascii_converter images/image.png image.txt 80
```