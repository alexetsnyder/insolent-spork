//******************************************************************* 
//                                                                    
//  Program:     Basic Survival Game                                     
//      
//	File:		 player.h
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: A object that creates a player object  
//                                                                    
//  Date:        Dec 9, 2015
//                                                                    
//*******************************************************************

#ifndef PLAYER_OBJECT_CLASS
#define PLAYER_OBJECT_CLASS

#include "Angel.h"
#include "cube.h"

class Player //: public Object
{
	public:
		void init(float width, float height, float length);
		void load();
		void draw(GLuint ambient_loc, GLuint diffuse_loc, GLuint specular_loc,
				  GLuint object_mv_loc, GLuint shininess_loc,
				  vec4 light_ambient, vec4 light_diffuse, vec4 light_specular);
		void move_to(vec3 position);
		void move_to_position(vec3 movement);

	private:
		Cube cube;						//The object that represents the player
		mat4 transform_field;			//Scale and move player
		vec3 position_field;			//The players position in the world
		float width_field;				//The width of the cube
		float height_field;				//The height of the cube
		float length_field;				//The length of the cube
};

#endif