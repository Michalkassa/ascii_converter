# ASCII Image Converter

A lightweight C program that loads an image and converts it into ASCII art for display in your terminal.

## Project Overview

The program:
- Prints the ASCII output directly to the terminal, text file and creates a png file 
- Allows for specifying the output width to match your terminal size and desired detail
- Makes use of stb_image.h for bitmap parsing and raylib for ui and png generation


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
### Original
![Original mp4 image](/examples/mclarenmp4/original.jpg "original image")
### Converted 
![Converted mp4 image](/examples/mclarenmp4/10.png "converted image")
### Converted 
![Converted mp4 image](/examples/mclarenmp4/100.png "converted image")
