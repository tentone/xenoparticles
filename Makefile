#Check if PATH is configured correctly
prefix :=$(shell xeno-config --prefix)

ifeq ($(prefix),)
$(error Please add <xeno-install-path>/bin to your PATH variable)
endif

#Get compiler and linker flags
CC := $(shell xeno-config --cc)
CFLAGS := $(shell xeno-config --skin=native --cflags)
LDFLAGS := -lnative $(shell xeno-config --skin=native --ldflags)

all: constellations

constellations: src/* #Constellations.cpp src/Vector2.cpp src/Particle.cpp
	g++ -O1 --std=c++11 -lSDL2 -lSDL2_image -lSDL2_ttf -lm -o constellations $< $(CFLAGS) $(LDFLAGS) -Xlinker -rpath -Xlinker /usr/xenomai/lib

clean: 
	rm constellations
