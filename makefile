#Makefile for the 3D Roller Coaster project
include C:\Users\library\Makefile.defs
#include /home/cs425/code-egs/Makefile.defs 

OBJECTS = main.o scene.o 

all: bsur clean

bsur: $(OBJECTS)
	$(CC) $(InitShader) $(OBJECTS) $(OPTIONS) $(LDLIBS) -o bsur

main.o: main.cc
	$(CC) -c $(OPTIONS) main.cc

scene.o: scene.h scene.cc 
	$(CC) -c $(OPTIONS) scene.cc

clean:
	rm *.o
