WARNING = -Wall -Wshadow
#ERROR = -Wvla -Werror
#$(WARNING) $(ERROR)
GCC = gcc -std=c11 -g WARNING -O3

SRCS = src/image.c src/main.c src/converter.c src/output.c src/microui.c
OBJS = src/image.o src/main.o src/converter.o src/output.o src/microui.o

TARGET = ascii_converter

all: $(TARGET)

$(TARGET): $(SRCS)
	$(GCC) $(SRCS) -o $(TARGET) $(LDFLAGS)

main.o: main.c image.h converter.h
	$(GCC) -c main.c

image.o: image.c image.h
	$(GCC) -c image.c

converter.o: converter.c converter.h image.h
	$(GCC) -c converter.c

output.o: output.c output.h image.h
	$(GCC) -c output.c

microui.o: ./src/microui.c ./src/microui.h
	$(GCC) -c ./src/microui.c

clean:
	rm -f $(OBJS)
