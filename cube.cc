//******************************************************************* 
//                                                                    
//  Program:     Basic Survival Game                                     
//      
//	File:		 cube.cc
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: Implements the cube class            
//                                                                    
//  Date:        Dec 9, 2015
//                                                                    
//*******************************************************************

#include "cube.h"

const int Cube::SIZE = 24;
bool Cube::INIT_DATA = false;
bool Cube::POINTS_SENT = false;
int Cube::BUFFER_PLOC = 0;
int Cube::BUFFER_NLOC = 0;
cube_data Cube::DATA;
const vec4 Cube::VERTICES[8] = {
			vec4(-0.5, -0.5,  0.5, 1.0),
			vec4(-0.5,  0.5,  0.5, 1.0),
			vec4( 0.5,  0.5,  0.5, 1.0),
			vec4( 0.5, -0.5,  0.5, 1.0),
			vec4(-0.5, -0.5, -0.5, 1.0),
			vec4(-0.5,  0.5, -0.5, 1.0),
			vec4( 0.5,  0.5, -0.5, 1.0),
			vec4( 0.5, -0.5, -0.5, 1.0)
		};


Cube::Cube()
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

void Cube::init()
{
	if (!POINTS_SENT && SEND_FLAG)
	{
		glBufferSubData(GL_ARRAY_BUFFER, BUFFER_PLOC * sizeof(vec4),
		 				sizeof(DATA.points), DATA.points);
		glBufferSubData(GL_ARRAY_BUFFER, NUM_POINTS*sizeof(vec4) + BUFFER_NLOC*sizeof(vec3), 
						sizeof(DATA.normals), DATA.normals);

		POINTS_SENT = true;
		SEND_FLAG = false;
	}
}

void Cube::draw()
{
	for (int i = 0; i < 6; ++i)
	{
		glDrawArrays(GL_TRIANGLE_FAN, BUFFER_PLOC + i * 4, 4);
	}
}

void Cube::create_vertices()
{
	rectangle(1, 0, 3, 2);
	rectangle(2, 3, 7, 6);
	rectangle(3, 0, 4, 7);
	rectangle(6, 5, 1, 2);
	rectangle(4, 5, 6, 7);
	rectangle(5, 4, 0, 1);

	for (int i = 0; i < 8; ++i)
	{
		std::cout << "normal " << i << " = " << DATA.normals[i*4] << std::endl;
	}

	//glBufferSubData(GL_ARRAY_BUFFER, BUFFER_LOC * sizeof(vec3), sizeof(points), points);
}

void Cube::rectangle(int i, int j, int k, int l)
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
