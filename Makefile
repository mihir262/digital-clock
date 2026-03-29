CC = clang
TARGET = main
SRC = main.c
CFLAGS = $(shell pkg-config --cflags raylib)
LDFLAGS = $(shell pkg-config --libs raylib) \
	-framework OpenGL \
	-framework Cocoa \
	-framework IOKit \
	-framework CoreAudio \
	-framework CoreVideo

.PHONY: all build run clean

all: build

build: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET)
