//******************************************************************* 
//                                                                    
//  Program:     Basic Survival Game                                     
//      
//	File:		 player.cc
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: The implementation of the player object
//                                                                    
//  Date:        Dec 9, 2015
//                                                                    
//*******************************************************************

#include "player.h"

void Player::init(float width, float height, float length)
{
	cube.init();
	transform_field = Translate(0.0, 0.0, 0.0) * Scale(width, height, length);
	position_field = vec3(0.0, 0.0, 0.0);
	width_field = width;
	height_field = height;
	length_field = length;

	vec4 ambient = vec4(0.4, 0.4, 0.4, 1.0);
	vec4 specular = vec4(0.0, 0.0, 1.0, 1.0);
	vec4 diffuse= vec4(0.0, 0.0, 0.4, 1.0);
	float shininess = 200.0;
	cube.set_lighting(ambient, diffuse, specular, shininess);
}

void Player::load()
{
	cube.SEND_FLAG = true;
	cube.load();
}

void Player::draw(GLuint ambient_loc, GLuint diffuse_loc, GLuint specular_loc,
		  GLuint object_mv_loc, GLuint shininess_loc,
		  vec4 light_ambient, vec4 light_diffuse, vec4 light_specular)
{
	vec4 ambient_product = light_ambient * cube.ambient();
	vec4 diffuse_product = light_diffuse *  cube.diffuse();
	vec4 specular_product = light_specular * cube.specular();

	glUniform4fv(ambient_loc, 1, ambient_product);
	glUniform4fv(diffuse_loc, 1, diffuse_product);
	glUniform4fv(specular_loc, 1, specular_product);
	glUniformMatrix4fv(object_mv_loc, 1, GL_TRUE, transform_field);
	glUniform1f(shininess_loc, cube.shininess());	
	cube.draw();
}

void Player::move_to(vec3 position)
{
	vec3 movement = position - position_field;

	//std::cout << "movement = " << movement << std::endl;
	//std::cout << "player.position = " << position_field << std::endl;

	move_to_position(movement);
}

void Player::move_to_position(vec3 movement)
{	
	position_field.x += movement.x;
	position_field.y += movement.y;
	position_field.z += movement.z;

	//std::cout << "before = " << transform_field << std::endl;

	transform_field[0][3] += movement.x;
	transform_field[1][3] += movement.y;
	transform_field[2][3] += movement.z;

	//std::cout << "after = " << transform_field << std::endl;
}