//******************************************************************* 
//                                                                    
//  Program:     Basic Survival Game                                     
//      
//	File:		 rock.cc
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: The implementationof the rock object
//                                                                    
//  Date:        Dec 9, 2015
//                                                                    
//*******************************************************************

#include "rock.h"

void Rock::init()
{
	vec4 ambient, specular, diffuse;
	float shininess;

	position_field = vec3(0.0, 0.0, 0.0);

	//Initialize Rock leafs
	rock_field.init();
	transform_field = Translate(0.0, 0.0, 0) * Scale(2.0, 2.0, 2.0);
	ambient = vec4(0.4, 0.4, 0.4, 1.0);
	specular = vec4(0.1, 0.1, 0.1, 1.0);
	diffuse = vec4(0.1, 0.1, 0.1, 1.0);
	shininess = 50.0;
	rock_field.set_lighting(ambient, diffuse, specular, shininess);
}

void Rock::load()
{
	//Both cubes so only need to call load once
	rock_field.SEND_FLAG = true;
	rock_field.load();
}

void Rock::draw(GLuint ambient_loc, GLuint diffuse_loc, GLuint specular_loc,
		  		GLuint object_mv_loc, GLuint shininess_loc,
		 		vec4 light_ambient, vec4 light_diffuse, vec4 light_specular)
{
	vec4 ambient_product, diffuse_product, specular_product;

	//Draw Rock Leafs
	ambient_product = light_ambient * rock_field.ambient();
	diffuse_product = light_diffuse *  rock_field.diffuse();
	specular_product = light_specular * rock_field.specular();

	glUniform4fv(ambient_loc, 1, ambient_product);
	glUniform4fv(diffuse_loc, 1, diffuse_product);
	glUniform4fv(specular_loc, 1, specular_product);
	glUniformMatrix4fv(object_mv_loc, 1, GL_TRUE, transform_field);
	glUniform1f(shininess_loc, rock_field.shininess());	
	rock_field.draw();
}

void Rock::move_to(vec3 position)
{
	vec3 movement = position - position_field;

	move_to_position(movement);
}

void Rock::move_to_position(vec3 movement)
{	
	position_field.x += movement.x;
	position_field.y += movement.y;
	position_field.z += movement.z;

	transform_field[0][3] += movement.x;
	transform_field[1][3] += movement.y;
	transform_field[2][3] += movement.z;
}