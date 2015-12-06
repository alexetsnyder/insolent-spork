//******************************************************************* 
//                                                                    
//  Program:     3D Survival Game                                      
//      
//	File:		 collision.cc
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: The implementation of functions that have anything
//				 to do with collision detection.         
//                                                                    
//  Date:       December 9, 2015
//                                                                    
//*******************************************************************

#include "collision.h"

bool within_range(vec3 pos1, vec3 pos2, float tol)
{
	return length(pos1 - pos2) <= tol;
}

