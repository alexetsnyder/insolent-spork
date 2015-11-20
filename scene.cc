//******************************************************************* 
//                                                                    
//  Program:     Survival Game                                       
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
//  Date:        December 9, 2015
//                                                                    
//*******************************************************************

#include "scene.h"

Scene::Scene(int width, int height)
{
	rotX = 0.0;
	rotY = 0.0;

	transform = Translate(0.0, 0.0, 0.0);

	vec4 ambient(0.3, 0.3, 0.3, 1.0);
	vec4 specular(1.0, 0.0, 0.0, 1.0);
	vec4 diffuse(0.4, 0.0, 0.0, 1.0);
	float shininess = 100.0;
	cube.set_lighting(ambient, diffuse, specular, shininess);

	vec4 eye(0.0, 0.0, 8.0, 1.0);
	vec4 at(0.0, 0.0, 0.0, 1.0);
	vec4 up(0.0, 1.0, 0.0, 0.0);
	camera.set_model_view(eye, at, up);

	camera.set_projection(45.0, width/(float)height, 0.1, 10.0);

	//Lighting properties
	light_position_field = vec4(0.0, 10.0, 0.0, 0.0);
	light_diffuse_field = vec4(1.0, 1.0, 1.0, 1.0);
	light_specular_field = vec4(1.0, 1.0, 1.0, 1.0);
	light_ambient_field = vec4(0.4, 0.4, 0.4, 1.0);
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

	camera_mv_loc = glGetUniformLocation(program, "camera_mv");

	object_mv_loc = glGetUniformLocation(program, "object_mv");

	projection_loc = glGetUniformLocation(program, "projection");

	ambient_product_loc = glGetUniformLocation(program, "AmbientProduct");

	diffuse_product_loc = glGetUniformLocation(program, "DiffuseProduct");

	specular_product_loc = glGetUniformLocation(program, "SpecularProduct");

	light_position_loc = glGetUniformLocation(program, "LightPosition");

	shininess_loc = glGetUniformLocation(program, "Shininess");
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
	vec4 ambient_product, diffuse_product, specular_product;

	//Camera and light positiong
	glUniformMatrix4fv(camera_mv_loc, 1, GL_TRUE, camera.get_model_view());
	glUniformMatrix4fv(projection_loc, 1, GL_TRUE, camera.get_projection());
	glUniform4fv(light_position_loc, 1, light_position_field);

	//Lighting for cube
	ambient_product = light_ambient_field * cube.ambient();
	diffuse_product = light_diffuse_field *  cube.diffuse();
	specular_product = light_specular_field * cube.specular();

	glUniform4fv(ambient_product_loc, 1, ambient_product);
	glUniform4fv(diffuse_product_loc, 1, diffuse_product);
	glUniform4fv(specular_product_loc, 1, specular_product);
	glUniformMatrix4fv(object_mv_loc, 1, GL_TRUE, transform);
	glUniform1f(shininess_loc, cube.shininess());	
	cube.draw();
}

void Scene::motion_func(int x, int y)
{
	static vec2 previous;
	static bool first = true;

	if (first)
	{
		previous = vec2((float)x, (float)y);
		first = false;
	}

	vec2 angle = previous - vec2(x, y);

	rotX += angle.x;
	rotY += angle.y;

	transform = RotateY(rotX) * 
				RotateX(rotY);

	glutPostRedisplay();

	previous = vec2(x, y);
}

/*void Scene::keyboard(unsigned char key, int x, int y)
{
	//
}*/

void Scene::reshape(int width, int height)
{
	//adjust viewport and clear
	glViewport(0, 0, width, height);

	//set class variables
	/*window_width = width;
	window_height = height;*/

	//Send to vertex shader
	//glUniform2f(window_size_loc, width, height);

	camera.aspect() = width / (float)height;
	glUniformMatrix4fv(projection_loc, 1, GL_TRUE, camera.get_projection());

	//Redisplay 
	glutPostRedisplay();
}
