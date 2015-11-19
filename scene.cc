//******************************************************************* 
//                                                                    
//  Program:     3D Roller Coaster                                       
//      
//	File:		 scene.cc
//                                                               
//  Author:      Alex Snyder
//  Email:       as828110@ohio.edu
//                                                                    
//  Class: CS4250: Interactive Graphics with Dr. Chelberg
//                                                                    
//  Description: Implements the Scene class             
//                                                                    
//  Date:        November 9, 2015
//                                                                    
//*******************************************************************

#include "scene.h"

Scene::Scene()
{
	rotX = 0.0;
	rotY = 0.0;
	rotZ = 0.0;

	//Lighting properties
	/*light_position_field = vec4(0.0, 6.0, 6.0, 0.0);
	light_diffuse_field = vec4(1.0, 1.0, 1.0, 1.0);
	light_specular_field = vec4(1.0, 1.0, 1.0, 1.0);
	light_ambient_field = vec4(0.4, 0.4, 0.4, 1.0);*/
}

void Scene::init(std::string vshader, std::string fshader, std::string position)
{
	//Create vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Create buffer object
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	//Load shaders to program
	program = InitShader(vshader.c_str(), fshader.c_str());
	glUseProgram(program);

	//Get location of vao 
	loc = glGetAttribLocation(program, position.c_str());
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	normal_loc = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(normal_loc);
	glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, 0, 
						  BUFFER_OFFSET(Geometry::NUM_POINTS*sizeof(vec4)));

	//camera_mv_loc = glGetUniformLocation(program, "camera_mv");

	object_mv_loc = glGetUniformLocation(program, "object_mv");

	/*projection_loc = glGetUniformLocation(program, "projection");

	ambient_product_loc = glGetUniformLocation(program, "AmbientProduct");

	diffuse_product_loc = glGetUniformLocation(program, "DiffuseProduct");

	specular_product_loc = glGetUniformLocation(program, "SpecularProduct");

	light_position_loc = glGetUniformLocation(program, "LightPosition");

	shininess_loc = glGetUniformLocation(program, "Shininess");*/
}

void Scene::load_objects()
{

	glBufferData(GL_ARRAY_BUFFER, Geometry::NUM_POINTS*sizeof(vec4) + 
				 Geometry::NUM_NORMALS*sizeof(vec3), NULL, GL_STATIC_DRAW);

	cube.SEND_FLAG = true;
	cube.init();
}

void Scene::draw_objects()
{
	//vec4 ambient_product, diffuse_product, specular_product;
	glUniformMatrix4fv(object_mv_loc, 1, GL_TRUE, transform);
	cube.draw();
}

void Scene::motion_func(int x, int y)
{
	static vec2 previous;
	static bool first = true;

	y = 800 - y;

	if (first)
	{
		previous = vec2((float)x, (float)y);
		first = false;
	}

	//std::cout << "previous = " << previous << std::endl;

	vec2 angle = previous - vec2(x, y);

	//std::cout << "angle = " << angle << std::endl;

	rotX += 2.0 * cos(angle.x) * sin(angle.y);
	rotY += 2.0 * sin(angle.x) * sin(angle.y);
	rotZ += 2.0 * sin(angle.y);

	std::cout << rotX << " , " << rotY << " , " << rotZ << std::endl;

	transform = RotateZ(rotZ) * 
				RotateY(rotY) * 
				RotateX(rotX);

	glutPostRedisplay();

	previous = vec2(x, y);
}

/*void Scene::keyboard(unsigned char key, int x, int y)
{
	//
}*/

/*void Scene::reshape(int width, int height)
{
	//adjust viewport and clear
	glViewport(0, 0, width, height);

	//set class variables
	window_width = width;
	window_height = height;

	//Send to vertex shader
	//glUniform2f(window_size_loc, width, height);

	camera.aspect() = width / (float)height;
	glUniformMatrix4fv(projection_loc, 1, GL_TRUE, camera.get_projection());

	//Redisplay 
	glutPostRedisplay();
}*/
