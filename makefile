WARNING = -Wall -Wshadow
ERROR = -Wvla -Werror
GCC = gcc -std=c11 -g $(WARNING) $(ERROR) -O3

SRCS = src/image.c src/main.c src/converter.c

TARGET = ascii-converter

all: $(TARGET)

$(TARGET): $(SRCS)
	$(GCC) $(SRCS) -o $(TARGET) $(LDFLAGS)

main.o: main.c image.h converter.h
	$(GCC) -c main.c

image.o: image.c image.h
	$(GCC) -c image.c

converter.o: converter.c converter.h image.h
	$(GCC) -c converter.c

clean:
	rm -f $(SRCS)
