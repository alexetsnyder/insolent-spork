//******************************************************************* 
//                                                                    
//  Program:     Basic Survival Game                                     
//      
//	File:		 cube.h
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: Implements the Scene class             
//                                                                    
//  Date:        November 9, 2015
//                                                                    
//*******************************************************************

#ifndef CUBE_GEOMETRY_CLASS
#define CUBE_GEOMETRY_CLASS

#include "Angel.h"

class cube //: public Geometry
{
	public:
		Cube();

		void init();

		void draw_geometry();

	private:
		void send_vertices();
		void rectangle(vec3 points[], int index, vec3 point, plane p);
		void fill_normals(vec3 points[], vec3 normals[], int index, int inv);
};

#endif