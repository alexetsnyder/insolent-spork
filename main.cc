//******************************************************************* 
//                                                                    
//  Program:     3D Roller Coaster                                       
//      
//	File:		 main.cc
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: Where program starts             
//                                                                    
//  Date:        November 9, 2015
//                                                                    
//*******************************************************************
#include <cstdlib>
#include <time.h>
#include "scene.h"

//The class that controls the game.
Scene scene;

void init()
{
	scene.init("vshader.glsl", "fshader.glsl", "vPosition");
	scene.load_objects();
	
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.53, 0.80, 0.92, 1.0);	
}

/*extern "C" void keyboard(unsigned char key, int x, int y)
{
	scene.keyboard(key, x, y);
}

extern "C" void reshape(int width, int height)
{
	scene.reshape(width, height);
}

extern "C" void idle()
{
	static GLint time = glutGet(GLUT_ELAPSED_TIME);

	scene.animate(time);

	time = glutGet(GLUT_ELAPSED_TIME);
	glutPostRedisplay();
}
*/
//Display function for glut callback display
extern "C" void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.draw_objects();
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	srand(time(0));

	//Initialize glut and choose color option, single buffering, depth
	//and window size
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);

	//Create window with title
	glutCreateWindow("3D Survival Game");

	//Initialize glew
	glewInit();

	//Basic initializing.
	init();

	//Glut callback functions
/*	glutReshapeFunc(reshape); 
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);*/
	glutDisplayFunc(display);

	glutMainLoop();
	return EXIT_SUCCESS;
}
