//******************************************************************* 
//                                                                    
//  Program:     Basic Survival Game                                     
//      
//	File:		 raycast.h
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: An object that creates a ray from the mouse
//				 mouse coordinates into the screen.   
//                                                                    
//  Date:        Dec 9, 2015
//                                                                    
//*******************************************************************

#ifndef RAY_CAST_CLASS
#define RAY_CAST_CLASS

#include "Angel.h"
#include "mymatrix.h"

class RayCast
{
	public:
		RayCast();

		//Casts a ray from the camera into the world depending on 
		//where the mouse clicks on the screen
		void cast_ray(int x, int y, float window_width, float window_height,
					  mat4 camera_mv, mat4 projection);

		//Getter returns the ray
		vec4 ray() {return ray_field;}

	private:
		vec4 ray_field;				//Holds the ray
		mat4 camera_mv_field;		//Camera model view matrix
		mat4 projection_field;		//The projection matrix
};

#endif
