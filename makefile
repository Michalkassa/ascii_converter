CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm

TARGET = ascii-converter
OBJS = main.o image.o converter.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

main.o: main.c image.h converter.h
	$(CC) $(CFLAGS) -c main.c

image.o: image.c image.h
	$(CC) $(CFLAGS) -c image.c

converter.o: converter.c converter.h image.h
	$(CC) $(CFLAGS) -c converter.c

clean:
	rm -f $(OBJS)

.PHONY: all clean