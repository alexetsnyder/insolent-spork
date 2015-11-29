//******************************************************************* 
//                                                                    
//  Program:     Basic Survival Game                                     
//      
//	File:		 ground.cc
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: The implementation of the ground object    
//                                                                    
//  Date:        Dec 9, 2015
//                                                                    
//*******************************************************************

#include "ground.h"

void Ground::init(int width, int length)
{
	vec4 ambient, specular, diffuse;
	float shininess;

	width_field = width;
	length_field = length;

	ambient = vec4(0.4, 0.4, 0.4, 1.0);
	specular = vec4(0.0, 4.0, 0.0, 1.0);
	diffuse= vec4(0.0, 1.0, 0.0, 1.0);
	shininess = 50.0;

	for (int i = 0; i < width*length; ++i)
	{
		Plane new_plane;
		planes.push_back(new_plane);
		planes[i].set_lighting(ambient, diffuse, specular, shininess);
	}
	planes[0].init();

	//Bottom half
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < length; ++j)
		{
			transforms.push_back(Translate(i - width/2.0, j - length/2.0, 0.0));
		}
	}
/*
	//Top half
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < 2*length; ++j)
		{
			transforms.push_back(Translate(width - i, length - j, 0.0));
		}
	}*/
}

void Ground::load()
{
	planes[0].SEND_FLAG = true;
	planes[0].load();
}

void Ground::draw(GLuint ambient_loc, GLuint diffuse_loc, GLuint specular_loc,
		  		  GLuint object_mv_loc, GLuint shininess_loc,
		  		  vec4 light_ambient, vec4 light_diffuse, vec4 light_specular)
{
	vec4 ambient_product, diffuse_product, specular_product;

	for (size_t i = 0; i < planes.size(); ++i)
	{
		ambient_product = light_ambient * planes[i].ambient();
		diffuse_product = light_diffuse *  planes[i].diffuse();
		specular_product = light_specular * planes[i].specular();

		glUniform4fv(ambient_loc, 1, ambient_product);
		glUniform4fv(diffuse_loc, 1, diffuse_product);
		glUniform4fv(specular_loc, 1, specular_product);
		glUniformMatrix4fv(object_mv_loc, 1, GL_TRUE, transforms[i]);
		glUniform1f(shininess_loc, planes[i].shininess());	
		planes[i].draw();
	}
}
