#Makefile for the 3D Roller Coaster project
#include C:\Users\library\Makefile.defs
include /home/cs425/code-egs/Makefile.defs 

OBJECTS = main.o scene.o geometry.o cube.o camera.o

all: bsur clean

bsur: $(OBJECTS)
	$(CC) $(InitShader) $(OBJECTS) $(OPTIONS) $(LDLIBS) -o bsur

main.o: main.cc
	$(CC) -c $(OPTIONS) main.cc

scene.o: scene.h scene.cc 
	$(CC) -c $(OPTIONS) scene.cc

geometry.o: geometry.h geometry.cc
	$(CC) -c $(OPTIONS) geometry.cc

cube.o: cube.h cube.cc
	$(CC) -c $(OPTIONS) cube.cc

camera.o: camera.h camera.cc
	$(CC) -c $(OPTIONS) camera.cc

clean:
	rm *.o
