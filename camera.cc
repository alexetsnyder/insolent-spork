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
	eye_field = vec4(0.0, 0.0, 0.0, 1.0);
	at_field = vec4(0.0, 0.0, 0.0, 1.0);
	up_field = vec4(0.0, 0.0, 0.0, 0.0);

	fovy_field = 45.0;
	aspect_field = 0.0;
	zNear_field = 0.5;
	zFar_field = 10.0;

	speed = 0.08;

	look_at = false;
}

void Camera::set_model_view(vec4 eye, vec4 at, vec4 up)
{
	look_at = true;

	eye_field = eye;
	at_field = at;
	up_field = up;

	set_look_at();
}

void Camera::set_model_view(mat4 model_view)
{
	look_at = false;
	model_view_field = model_view;
}
		
void Camera::set_look_at()
{
	model_view_field = LookAt(eye_field, at_field, up_field);
}

mat4 Camera::get_model_view()
{
	if (look_at)
		set_look_at();

	return model_view_field;
}

vec4 Camera::position()
{
	return vec4(model_view_field[0][3], model_view_field[1][3], model_view_field[2][3], 1.0);
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

void Camera::move_at(moves move)
{
	vec4 movement = at_field - eye_field;

	if (move == FORWARD)
	{
		move_towards(speed*vec3(movement.x, movement.y, movement.z));
	}
	else if (move == BACKWARDS)
	{
		move_towards(speed*vec3(-movement.x, -movement.y, movement.z));
	}
	else if (move == LEFT)
	{
		vec4 perp = cross(up_field, movement);

		move_towards(speed*vec3(perp.x, perp.y, perp.z));
	}
	else 
	{
		vec4 perp = cross(movement, up_field);

		move_towards(speed*vec3(perp.x, perp.y, perp.z));
	}
}

void Camera::move_towards(vec3 movement)
{
	eye_field.x += movement.x;
	at_field.x += movement.x;
	eye_field.y += movement.y;
	at_field.y += movement.y;
}
