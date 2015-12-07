//******************************************************************* 
//                                                                    
//  Program:     Basic Survival Game                                     
//      
//	File:		 rock.h
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: A object that creates a rock in the scene
//                                                                    
//  Date:        Dec 9, 2015
//                                                                    
//*******************************************************************

#ifndef ROCK_OBJECT_CLASS
#define ROCK_OBJECT_CLASS

#include "Angel.h"
#include "cube.h"

class Rock //: public Object
{
	public:
		void init();
		void load();
		void draw(GLuint ambient_loc, GLuint diffuse_loc, GLuint specular_loc,
				  GLuint object_mv_loc, GLuint shininess_loc,
				  vec4 light_ambient, vec4 light_diffuse, vec4 light_specular);
		void move_to(vec3 position);
		void move_to_position(vec3 movement);

		//Getter and Setters
		vec3 position() {return position_field;}

	private:
		Cube rock_field;			//The rock as a cube
		mat4 transform_field;		//Scale and move rock
		vec3 position_field;		//The rock position in the world
};

#endif