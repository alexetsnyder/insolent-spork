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
#include "Angel.h"
#include "camera.h"
#include "cube.h"

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
		void motion_func(int x, int y);
		/*void keyboard(unsigned char key, int x, int y);
		void animate(GLint time);*/
		void reshape(int width, int height);

	private:
		Camera camera;					//The camera

		Cube cube;
		mat4 transform;
		float rotX;
		float rotY;

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

#endif
