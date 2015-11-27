//******************************************************************* 
//                                                                    
//  Program:     Basic Survival Game                                     
//      
//	File:		 plane.cc
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: Implements the plane class           
//                                                                    
//  Date:        Dec 9, 2015
//                                                                    
//*******************************************************************

#include "plane.h"

const int Plane::SIZE = 4;
bool Plane::INIT_DATA = false;
bool Plane::POINTS_SENT = false;
int Plane::BUFFER_PLOC = 0;
int Plane::BUFFER_NLOC = 0;
plane_data Plane::DATA;
const vec4 Plane::VERTICES[4] = {
			vec4(-0.5, -0.5, -0.5, 1.0),
			vec4(-0.5,  0.5, -0.5, 1.0),
			vec4( 0.5,  0.5, -0.5, 1.0),
			vec4( 0.5, -0.5, -0.5, 1.0)
		};


Plane::Plane()
{
	//Nothing
}

void Plane::init()
{
	if (!INIT_DATA)
	{
		DATA.index = 0;
		create_vertices();

		BUFFER_NLOC = NUM_NORMALS;
		NUM_NORMALS += SIZE;
		BUFFER_PLOC = NUM_POINTS;
		NUM_POINTS += SIZE;

		INIT_DATA = true;
	}
}

void Plane::load()
{
	if (!POINTS_SENT && SEND_FLAG)
	{
		std::cout << "PLOC = " << BUFFER_PLOC << " NLOC = " << BUFFER_NLOC << std::endl;
		
		glBufferSubData(GL_ARRAY_BUFFER, BUFFER_PLOC * sizeof(vec4),
		 				sizeof(DATA.points), DATA.points);
		glBufferSubData(GL_ARRAY_BUFFER, NUM_POINTS*sizeof(vec4) + BUFFER_NLOC*sizeof(vec3), 
						sizeof(DATA.normals), DATA.normals);
		POINTS_SENT = true;
		SEND_FLAG = false;
	}
}

void Plane::draw()
{
	glDrawArrays(GL_TRIANGLE_FAN, BUFFER_PLOC, SIZE);
}

void Plane::create_vertices()
{
	rectangle(1, 0, 3, 2);
}

void Plane::rectangle(int i, int j, int k, int l)
{
	vec4 u = VERTICES[j] - VERTICES[i];
	vec4 v = VERTICES[k] - VERTICES[j];
	vec3 normal = normalize(cross(u, v));

	DATA.normals[DATA.index] = normal; DATA.points[DATA.index] = VERTICES[i];
	DATA.normals[++DATA.index] = normal; DATA.points[DATA.index] =  VERTICES[j];
	DATA.normals[++DATA.index] = normal; DATA.points[DATA.index] =  VERTICES[k];
	DATA.normals[++DATA.index] = normal; DATA.points[DATA.index] =  VERTICES[l];
	++DATA.index;
}
