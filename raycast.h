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

#ifndef RAY_CAST_FUNCTIONS
#define RAY_CAST_FUNCTIONS

#include "Angel.h"
#include "mymatrix.h"

//Casts a ray from the camera into the world depending on 
//where the mouse clicks on the screen
vec4 cast_ray(int x, int y, float window_width, float window_height,
			  mat4 camera_mv, mat4 projection);

//Determines whether a ray intersects with a plane and 
//if it does puts the point of intersection in intersect_point
bool ray_intersect_plane(vec4& P0, vec4& N, vec4& I0, vec4& I, vec4 intersect_point);

#endif
