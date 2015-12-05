//******************************************************************* 
//                                                                    
//  Program:     Basic Survival Game                                     
//      
//  File:        mymatrix.h
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: A collection of matrix functions for this project     
//                                                                    
//  Date:        Dec 9, 2015
//                                                                    
//*******************************************************************

#ifndef MYMATRIX_COLLECTION
#define MYMATRIX_COLLECTION

#include "Angel.h"

//Looks like the mat4 functions in angel, that way
//I can take the inverse like I do things like Scale 
//and so on.
mat4 inverse(mat4 matrix);

//Given an axis of rotation and a angle return the 
//rotation matrix to rotate around the axis by the 
//angle
mat4 rotation(vec3 axis, float angle);

//http://www.neilmendoza.com/glsl-rotation-about-an-arbitrary-axis/
//Not made by me, On blog by Neil Mendoza
mat4 rotationMatrix(vec3 axis, float angle);

//Convert mat4s to array then use function that I found on 
//the internet to find the inverse.
void convert_mat4_to_array(const mat4& matrix, double m[16]);
void convert_array_to_mat4(const double m[16], mat4& matrix);

//http://www.gamedev.net/topic/648190-algorithm-for-4x4-matrix-inverse/
//glu inverse matrix function found online
bool gluInvertMatrix(const double m[16], double invOut[16]);

#endif
