//******************************************************************* 
//                                                                    
//  Program:     Basic Survival Game                                     
//      
//	File:		 tree.h
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: A object that creates a tree geometry on 
//				 the screen.
//                                                                    
//  Date:        Dec 9, 2015
//                                                                    
//*******************************************************************

#ifndef TREE_OBJECT_CLASS
#define TREE_OBJECT_CLASS

#include "Angel.h"
#include "cube.h"

class Tree //: public Object
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
		Cube leafs;						//The top of the tree
		mat4 leafs_transform_field;		//Scale and move tree
		Cube trunk;						//The bottom of the tree
		mat4 trunk_transform_field;		//Scale and move tree
		vec3 position_field;			//The tree position in the world
};

#endif