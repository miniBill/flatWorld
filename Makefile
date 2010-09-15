# A dirty, hacky little Makefile for the lazy =] 

all: flatWorld

flatWorld: build/Makefile
	cd build && make

build/Makefile: build
	cd build && cmake ..

build:
	mkdir build

clean:
	rm -rf build

.PHONY: all clean

