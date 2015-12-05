//******************************************************************* 
//                                                                    
//  Program:     Basic Survival Game                                     
//      
//	File:		 tree.cc
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: The implementationof the tree object
//                                                                    
//  Date:        Dec 9, 2015
//                                                                    
//*******************************************************************

#include "tree.h"

void Tree::init()
{
	vec4 ambient, specular, diffuse;
	float shininess;

	position_field = vec3(0.0, 0.0, 0.0);

	//Initialize tree leafs
	leafs.init();
	leafs_transform_field = Translate(0.0, 0.0, 2.6) * Scale(3.0, 3.0, 1.0);
	ambient = vec4(0.4, 0.4, 0.4, 1.0);
	specular = vec4(0.0, 2.0, 0.0, 1.0);
	diffuse = vec4(0.0, 0.9, 0.1, 1.0);
	shininess = 25.0;
	leafs.set_lighting(ambient, diffuse, specular, shininess);

	//Initialize tree trunk
	trunk_transform_field = Translate(0.0, 0.0, 1.1) * Scale(1.0, 1.0, 3.0);
	ambient = vec4(0.4, 0.4, 0.4, 1.0);
	specular = vec4(0.1, 0.01, 0.001, 1.0);
	diffuse = vec4(0.54, 0.27, 0.07, 1.0);
	shininess = 10.0;
	trunk.set_lighting(ambient, diffuse, specular, shininess);
}

void Tree::load()
{
	//Both cubes so only need to call load once
	leafs.SEND_FLAG = true;
	leafs.load();
}

void Tree::draw(GLuint ambient_loc, GLuint diffuse_loc, GLuint specular_loc,
		  		GLuint object_mv_loc, GLuint shininess_loc,
		 		vec4 light_ambient, vec4 light_diffuse, vec4 light_specular)
{
	vec4 ambient_product, diffuse_product, specular_product;

	//Draw Tree Leafs
	ambient_product = light_ambient * leafs.ambient();
	diffuse_product = light_diffuse *  leafs.diffuse();
	specular_product = light_specular * leafs.specular();

	glUniform4fv(ambient_loc, 1, ambient_product);
	glUniform4fv(diffuse_loc, 1, diffuse_product);
	glUniform4fv(specular_loc, 1, specular_product);
	glUniformMatrix4fv(object_mv_loc, 1, GL_TRUE, leafs_transform_field);
	glUniform1f(shininess_loc, leafs.shininess());	
	leafs.draw();

	//Draw Tree trunk
	ambient_product = light_ambient * trunk.ambient();
	diffuse_product = light_diffuse *  trunk.diffuse();
	specular_product = light_specular * trunk.specular();

	glUniform4fv(ambient_loc, 1, ambient_product);
	glUniform4fv(diffuse_loc, 1, diffuse_product);
	glUniform4fv(specular_loc, 1, specular_product);
	glUniformMatrix4fv(object_mv_loc, 1, GL_TRUE, trunk_transform_field);
	glUniform1f(shininess_loc, trunk.shininess());	
	trunk.draw();
}

void Tree::move_to(vec3 position)
{
	vec3 movement = position - position_field;

	//std::cout << "movement = " << movement << std::endl;
	//std::cout << "Tree.position = " << position_field << std::endl;

	move_to_position(movement);
}

void Tree::move_to_position(vec3 movement)
{	
	position_field.x += movement.x;
	position_field.y += movement.y;
	position_field.z += movement.z;

	//std::cout << "before = " << transform_field << std::endl;

	leafs_transform_field[0][3] += movement.x;
	leafs_transform_field[1][3] += movement.y;
	leafs_transform_field[2][3] += movement.z;

	trunk_transform_field[0][3] += movement.x;
	trunk_transform_field[1][3] += movement.y;
	trunk_transform_field[2][3] += movement.z;

	//std::cout << "after = " << transform_field << std::endl;
}