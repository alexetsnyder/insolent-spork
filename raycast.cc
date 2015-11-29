//******************************************************************* 
//                                                                    
//  Program:     Basic Survival Game                                     
//      
//	File:		 raycast.cc
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

#include "raycast.h"

RayCast::RayCast()
{
	//Nothing
}

void RayCast::cast_ray(int x, int y, float window_width, float window_height,
					   mat4 camera_mv, mat4 projection)
{
	//Normalized Device Coordinates
	float xd = (2.0f * x) / window_width - 1.0f;
	float yd = 1.0f - (2.0f * y) / window_height;

	vec4 ray_clip(xd, yd, -1.0, 1.0);

	//Eye coordinates
	vec4 ray_eye = inverse(projection) * ray_clip;
	ray_eye = vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

	//World coordinates
	ray_field = inverse(camera_mv) * ray_eye;
	ray_field = normalize(ray_field);
}
