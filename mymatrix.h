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

//Convert mat4s to array then use function that I found on 
//the internet to find the inverse.
void convert_mat4_to_array(const mat4& matrix, double m[16]);
void convert_array_to_mat4(const double m[16], mat4& matrix);
bool gluInvertMatrix(const double m[16], double invOut[16]);

#endif