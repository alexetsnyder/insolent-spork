//******************************************************************* 
//                                                                    
//  Program:     Basic Survival Game                                     
//      
//	File:		 cube.h
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: A object that creates cube vertex info.       
//                                                                    
//  Date:        Dec 9, 2015
//                                                                    
//*******************************************************************

#ifndef CUBE_GEOMETRY_CLASS
#define CUBE_GEOMETRY_CLASS

#include "Angel.h"
#include "geometry.h"

struct cube_data
{
	int index;				//Index to fill points and normals
	vec4 points[24];		//The vertex info sent to GPU
	vec3 normals[24];		//The normal info sent to GPU
};

class Cube : public Geometry
{
	public:
		static const int SIZE;			//Number of vertices
		static const vec4 VERTICES[];   //Vertices of unit cube
		static int BUFFER_PLOC;			//Place of vertices in buffer
		static int BUFFER_NLOC;			//NUM_POINTS*sizeof(vecc4) + this for location of normals
		static bool INIT_DATA;			//Data initiated once
		static bool POINTS_SENT;		//Points sent once
		static cube_data DATA;			//Cube data in cpu

		Cube();

		void init();		//Set send flag and only call once when all objects are created

		void draw();		//Draw the object.

	private:
		void create_vertices();
		void rectangle(int i, int j, int k, int l);
};

#endif