//******************************************************************* 
//                                                                    
//  Program:     Basic Survival Game                                     
//      
//	File:		 ground.h
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: A object that creates the ground out of planes      
//                                                                    
//  Date:        Dec 9, 2015
//                                                                    
//*******************************************************************

#ifndef GROUND_OBJECT_CLASS
#define GROUND_OBJECT_CLASS

#include <vector>
#include "plane.h"

class Ground //: public Object
{
	public:
		void init(int width, int length);
		void load();
		void draw(GLuint ambient_loc, GLuint diffuse_loc, GLuint specular_loc,
				  GLuint object_mv_loc, GLuint shininess_loc,
				  vec4 light_ambient, vec4 light_diffuse, vec4 light_specular);

	private:
		std::vector<Plane> planes;		//Need one plane geometry
		std::vector<mat4> transforms;	//The objects transforms 
		int width_field;				//The width
		int length_field;				//The length
};

#endif