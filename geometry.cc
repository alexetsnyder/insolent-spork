//******************************************************************* 
//                                                                    
//  Program:     Basic Survival Game                                     
//      
//	File:		 geometry.cc
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: The implementation for the geometry class     
//                                                                    
//  Date:        Dec 9, 2015
//                                                                    
//*******************************************************************

#include "geometry.h"

int Geometry::NUM_POINTS = 0;
int Geometry::NUM_NORMALS = 0;
bool Geometry::SEND_FLAG = false;

void Geometry::set_lighting(vec4 ambient, vec4 diffuse, vec4 specular, float shininess)
{
	ambient_field = ambient;
	diffuse_field = diffuse;
	specular_field = specular;
	shininess_field = shininess;
}