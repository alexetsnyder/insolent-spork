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

#ifndef CAMERA_CONTROL_CLASS
#define CAMERA_CONTROL_CLASS

#include "Angel.h"

class Camera
{
	public:
		Camera();			//Constructer

		void set_model_view(vec4 eye, vec4 at, vec4 up);
		mat4 get_model_view();

		void set_projection(float fovy, float aspect, float zNear, float zFar);
		mat4 get_projection();

		//Getter and Setters
		vec4& eye() {return eye_field;}
		vec4& at() {return at_field;}
		vec4& up() {return up_field;}
		float& fovy() {return fovy_field;}
		float& aspect() {return aspect_field;}
		float& zNear() {return zNear_field;}
		float& zFar() {return zFar_field;}

	private:
		vec4 eye_field;			//Where the view is
		vec4 at_field;			//Where viewer is looking at
		vec4 up_field;			//The up vector			

		float fovy_field;		//Field of View
		float aspect_field;		//Aspect ration
		float zNear_field;		//Near z 
		float zFar_field;		//Far z
};

#endif