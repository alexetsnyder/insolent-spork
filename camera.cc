//******************************************************************* 
//                                                                    
//  Program:     3D Survival Game                                      
//      
//	File:		 camera.h
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: The camera class      
//                                                                    
//  Date:        December 9, 2015
//                                                                    
//*******************************************************************

#include "camera.h"

Camera::Camera()
{
	//
}

void Camera::set_model_view(vec4 eye, vec4 at, vec4 up)
{
	eye_field = eye;
	at_field = at;
	up_field = up;
}

mat4 Camera::get_model_view()
{
	return LookAt(eye_field, at_field, up_field);
}

void Camera::set_projection(float fovy, float aspect, float zNear, float zFar)
{
	fovy_field = fovy;
	aspect_field = aspect;
	zNear_field = zNear;
	zFar_field = zFar;
}

mat4 Camera::get_projection()
{
	return Perspective(fovy_field, aspect_field, zNear_field, zFar_field);
}
