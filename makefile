#Makefile for the 3D Roller Coaster project
include C:\Users\library\Makefile.defs
#include /home/cs425/code-egs/Makefile.defs 

OBJECTS = main.o scene.o geometry.o cube.o camera.o plane.o mymatrix.o ground.o
OBJECTS += raycast.o player.o tree.o collision.o rock.o

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

plane.o: plane.h plane.cc
	$(CC) -c $(OPTIONS) plane.cc

mymatrix.o: mymatrix.h mymatrix.cc
	$(CC) -c $(OPTIONS) mymatrix.cc

ground.o: ground.h ground.cc
	$(CC) -c $(OPTIONS) ground.cc

raycast.o: raycast.h raycast.cc
	$(CC) -c $(OPTIONS) raycast.cc

player.o: player.h player.cc
	$(CC) -c $(OPTIONS) player.cc

tree.o: tree.h tree.cc
	$(CC) -c $(OPTIONS) tree.cc

collision.o: collision.h collision.cc
	$(CC) -c $(OPTIONS) collision.cc

rock.o: rock.h rock.cc
	$(CC) -c $(OPTIONS) rock.cc

clean:
	rm *.o #*~
