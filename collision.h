//******************************************************************* 
//                                                                    
//  Program:     3D Survival Game                                      
//      
//	File:		 collision.h
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: The definition of functions that have anything
//				 to do with collision detection.         
//                                                                    
//  Date:       December 9, 2015
//                                                                    
//*******************************************************************

#ifndef COLLISION_DETECTION_DEFINITIONS
#define COLLISION_DETECTION_DEFINITIONS

#include "Angel.h"

bool within_range(vec3 pos1, vec3 pos2, float tol);

#endif