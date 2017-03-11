INCLUDE=include/

SOURCE_FILES=$(wildcard ./src/*.hpp) $(wildcard ./src/*.cpp)
all: $(SOURCE_FILES)
	g++ `pkg-config --cflags gtk+-3.0` -o sgi $(SOURCE_FILES) `pkg-config --libs gtk+-3.0` -std=c++11 -rdynamic
clean:
	rm sgi
