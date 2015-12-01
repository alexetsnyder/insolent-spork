//******************************************************************* 
//                                                                    
//  Program:     Basic Survival Game                                     
//      
//	File:		 plane.h
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: A object that creates plane vertex information      
//                                                                    
//  Date:        Dec 9, 2015
//                                                                    
//*******************************************************************

#ifndef PLANE_GEOMETRY_CLASS
#define PLANE_GEOMETRY_CLASS

#include "Angel.h"
#include "geometry.h"

struct plane_data
{
	int index;			//Index to fill points and normals
	vec4 points[4];		//The vertex info sent to GPU
	vec3 normals[4];	//The normal info sent to GPU
};

class Plane : public Geometry
{
	public:
		static const int SIZE;			//Number of vertices
		static const vec4 VERTICES[];	//Verticies for a unit plane
		static int BUFFER_PLOC;			//Place of vertices in buffer
		static int BUFFER_NLOC;			//NUM_POINTS*sizeof(vecc4) + this for location of normals
		static bool INIT_DATA;			//Data initiated once
		static bool POINTS_SENT;		//Points sent once
		static plane_data DATA;			//Plane data in cpu

		Plane();

		void init();		//Create Verticies and deal with locations
		void load();		//Send verticies to gpu
		void draw();		//Draw the object.

		vec3 get_normal(){return DATA.normals[0];}

	private:
		void create_vertices();
		void rectangle(int i, int j, int k, int l);
};

#endif
