GCC = gcc
WARNING = -Wall -Wshadow
CFLAGS = -std=c11 -g -O3 $(WARNING) -arch arm64 -Iinclude

SRCS = src/image.c src/main.c src/converter.c src/output.c
OBJS = image.o main.o converter.o output.o

TARGET = ascii_converter

LDFLAGS = /opt/homebrew/Cellar/raylib/5.5/lib/libraylib.dylib \
          -framework CoreVideo -framework IOKit -framework Cocoa \
          -framework OpenGL -framework GLUT


all: $(TARGET)

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) $(LDFLAGS) -o $(TARGET)

main.o: src/main.c
	$(GCC) $(CFLAGS) -c src/main.c -o main.o

image.o: src/image.c
	$(GCC) $(CFLAGS) -c src/image.c -o image.o

converter.o: src/converter.c
	$(GCC) $(CFLAGS) -c src/converter.c -o converter.o

output.o: src/output.c
	$(GCC) $(CFLAGS) -c src/output.c -o output.o

clean:
	rm -f $(OBJS) 

