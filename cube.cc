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
//  Date:        November 9, 2015
//                                                                    
//*******************************************************************

#include "cube.h"

Cube::Cube()
{
	//
}

void Cube::init()
{
	send_vertices();

}

void Cube::draw_geometry()
{
	for (int i = 0; i < 6; ++i)
	{
		glDrawArrays(GL_TRIANGLE_FAN, place + i * 4, 4);
	}
}

void Cube::send_vertices()
{
	if (!data_sent)
	{
		vec3 points[SIZE];
		vec3 normals[SIZE];
		vec3 start = vec3(-0.5, -0.5, -0.5);

		draw_square(points, 0, start, XY_PLANE);
		fill_normals(points, normals, 0, true);
		draw_square(points, 4, start, XZ_PLANE);
		fill_normals(points, normals, 4, true);
		draw_square(points, 8, start, YZ_PLANE);
		fill_normals(points, normals, 8, true);

		draw_square(points, 12, vec3(start.x, start.y + 1.0, start.z), XZ_PLANE);
		fill_normals(points, normals, 12, false);
		draw_square(points, 16, vec3(start.x, start.y, start.z + 1.0), XY_PLANE);
		fill_normals(points, normals, 16, false);
		draw_square(points, 20, vec3(start.x + 1.0, start.y, start.z), YZ_PLANE);
		fill_normals(points, normals, 20, false);

		glBufferSubData(GL_ARRAY_BUFFER, place * sizeof(vec3), sizeof(points), points);

		data_sent = true;
	}
}

void Cube::rectangle(vec3 points[], int index, vec3 point, plane p)
{
	if (p == XY_PLANE)
	{
		points[index] = point;
		points[++index] = vec3(point.x, point.y + 1.0, point.z);
		points[++index] = vec3(point.x + 1.0, point.y + 1.0, point.z);
		points[++index] = vec3(point.x + 1.0, point.y, point.z);
	}
	else if (p == XZ_PLANE)
	{
		points[index] = point;
		points[++index] = vec3(point.x, point.y, point.z + 1.0);
		points[++index] = vec3(point.x + 1.0, point.y, point.z + 1.0);
		points[++index] = vec3(point.x + 1.0, point.y, point.z);
	}
	else
	{
		points[index] = point;
		points[++index] = vec3(point.x, point.y, point.z + 1.0);
		points[++index] = vec3(point.x, point.y + 1.0, point.z + 1.0);
		points[++index] = vec3(point.x, point.y + 1.0, point.z);
	}
}

void Cube::fill_normals(vec3 points[], vec3 normals[], int index, int inv)
{
	vec3 normal = normalize(cross(points[index+1] - points[index], points[index+2] - points[index+1]));
	if (inv)
	{
		normal.x = (normal.x == 0) ? normal.x : normal.x * -1;
		normal.y = (normal.y == 0) ? normal.y : normal.y * -1;
		normal.z = (normal.z == 0) ? normal.z : normal.z * -1;
	}
	
	for (int i = index; i < index+4; ++i)
	{
		normals[i] = normal;
	}
}

