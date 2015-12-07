//******************************************************************* 
//                                                                    
//  Program:     3D Survival Game                                      
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
//  Date:       December 9, 2015
//                                                                    
//*******************************************************************
#include <cstdlib>
#include <time.h>
#include "scene.h"

//The class that controls the game.
Scene scene(800, 800);

void init()
{
	scene.init("vshader.glsl", "fshader.glsl", "vPosition");
	scene.load_objects();
	
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.53, 0.80, 0.92, 1.0);	
}

extern "C" void menu(int value)
{
	switch (value)
	{
		case Scene::LOGS:
			std::cout << "Place logs\n";
			break;
		case Scene::LEAFS:
			std::cout << "Place leafs\n";
			break;
		case Scene::ROCKS:
			std::cout << "Place Stone\n";
			break;
		case Scene::HUT:
			std::cout << "Craft Hut\n";
			break;
		default:
			std::cout << "Other\n";
	}

}

void create_menu()
{
	//std::cout << glutGetMenu() << std::endl;
	/*if (glutGetMenu() != 0)
	{
		glutDestroyMenu(glutGetMenu());
	}*/
	glutCreateMenu(menu);
	glutAddMenuEntry("Crafting Menu:", -1);

	scene.create_crafting_menu();

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

extern "C" void motion_func(int x, int y)
{
	scene.motion_func(x, y);
}

extern "C" void mouse_click(int button, int state, int x, int y)
{
	scene.mouse_click(button, state, x, y);
}

extern "C" void keyboard(unsigned char key, int x, int y)
{
	scene.keyboard(key, x, y);

	if (key == 'v' || key == 'e')
		create_menu();
}

extern "C" void reshape(int width, int height)
{
	scene.reshape(width, height);
}

extern "C" void idle()
{
	//static GLint time = glutGet(GLUT_ELAPSED_TIME);

	scene.idle_move_trackball();

	//time = glutGet(GLUT_ELAPSED_TIME);
	glutPostRedisplay();
}

extern "C" void mouse_motion(int x, int y)
{
	scene.mouse_motion(x, y);
}

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
	//create_menu();

	//Glut callback functions
    glutReshapeFunc(reshape); 
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMotionFunc(motion_func);
	glutPassiveMotionFunc(mouse_motion);
	glutMouseFunc(mouse_click);
	//glutMenuStateFunc(menu);
	glutDisplayFunc(display);

	glutMainLoop();
	return EXIT_SUCCESS;
}
