//******************************************************************* 
//                                                                    
//  Program:     3D Survival Game                                      
//      
//	File:		 scene.h
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: Holds opengl variables and does basic
//				 things that need done for opengl              
//                                                                    
//  Date:        November 9, 2015
//                                                                    
//*******************************************************************

#ifndef SCENE_CONTROL_CLASS
#define SCENE_CONTROL_CLASS

#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include "Angel.h"
#include "camera.h"
#include "cube.h"
#include "ground.h"
#include "raycast.h"

struct track_ball
{
	bool track_ball_on;
	int last_x, last_y;
	int current_x, current_y;
	float angle;
};

class Scene
{
	public:
		Scene(int width, int height);

		void init(std::string vshader, std::string fshader, std::string position);

		//Send all objects vertexs to the GPU
		void load_objects();

		//Draw all the objects on the screen.
		void draw_objects();

		//Callback functions
		void reshape(int width, int height);
		//Virtual Trackball functions
		void motion_func(int x, int y);
		void mouse_click(int button, int state, int x, int y);
		vec3 get_trackball_vector(int x, int y);
		void idle_move_trackball();
		/*void keyboard(unsigned char key, int x, int y);*/

	private:
		Camera camera;				    //The camera
		track_ball track_field;			//The virtual trackball

		Cube cube;
		mat4 cube_transform;

		Ground ground;					//The ground to walk on

		int window_width;				//the window width
		int window_height;				//the window height

		vec4 light_position_field;		//position of the light
		vec4 light_ambient_field;		//ambient light
		vec4 light_diffuse_field;		//diffuse light
		vec4 light_specular_field;		//specular light

		GLuint camera_mv_loc;			//Location of model_view uniform
		GLuint object_mv_loc;			//Objects model_view uniform
		GLuint projection_loc;			//Location of projection uniform

		GLuint ambient_product_loc;		//location of ambient product uniform
		GLuint diffuse_product_loc;		//location of diffuse product uniform
		GLuint specular_product_loc;	//location of specular product uniform
		GLuint light_position_loc;		//location of light position uniform
		GLuint shininess_loc;			//location of shininess uniform

		GLuint program;					//compiled vertex and fragment shaders
		GLuint vao;						//vertex array object
		GLuint buffer;					//buffer object to send data
		GLuint loc;						//Location of vao
		GLuint normal_loc;				//Location of Normals in vao
};

//http://www.neilmendoza.com/glsl-rotation-about-an-arbitrary-axis/
//Not made by me, On blog by Neil Mendoza
mat4 rotationMatrix(vec3 axis, float angle);

#endif
