INCLUDE=include/

SOURCE_FILES=$(wildcard src/main.cpp)
OUTPUT=sgi

all: $(SOURCE_FILES)
	g++ `pkg-config --cflags gtk+-3.0` -o ${OUTPUT} $(SOURCE_FILES) `pkg-config --libs gtk+-3.0` -std=c++11 -rdynamic
clean:
	rm ${OUTPUT}
run:
	make clean
	make
	./${OUTPUT}
