//******************************************************************* 
//                                                                    
//  Program:     Basic Survival Game                                     
//      
//	File:		 geometry.h
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: An object for which all geometry classes will
//				 inherit.      
//                                                                    
//  Date:        Dec 9, 2015
//                                                                    
//*******************************************************************

#ifndef GEOMETRY_API_CLASS
#define GEOMETRY_API_CLASS

#include "Angel.h"

class Geometry
{
	public:
		static int NUM_POINTS;
		static int NUM_NORMALS;
		static bool SEND_FLAG;

		//Setters and Getters
		void set_lighting(vec4 ambient, vec4 diffuse, vec4 specular, float shininess);
		vec4& ambient() {return ambient_field;}
		vec4& diffuse() {return diffuse_field;}
		vec4& specular() {return specular_field;}
		float& shininess() {return shininess_field;}

	private:
		vec4 ambient_field;			//ambient light effect on object
		vec4 diffuse_field;			//diffuse property of material
		vec4 specular_field;		//specular property of material
		float shininess_field;		//Shininess property of material
};

#endif
