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
	vec4 ambient, specular, diffuse;
	float shininess;

	window_width = width;
	window_height = height;

	track_field.track_ball_on = false;
	track_field.last_x = 0;
	track_field.last_y = 0;
	track_field.current_x = 0;
	track_field.current_y = 0;
	track_field.angle = 0.0;

	ambient = vec4(0.4, 0.4, 0.4, 1.0);
	specular = vec4(1.0, 0.0, 0.0, 1.0);
	diffuse= vec4(0.4, 0.0, 0.0, 1.0);
	shininess = 100.0;
	cube.set_lighting(ambient, diffuse, specular, shininess);
	cube.init();
	cube_transform = Translate(0.0, 0.0, 0.0);

	ambient = vec4(0.4, 0.4, 0.4, 1.0);
	specular = vec4(1.0, 0.0, 0.0, 1.0);
	diffuse= vec4(0.4, 0.0, 0.0, 1.0);
	shininess = 100.0;
	plane.set_lighting(ambient, diffuse, specular, shininess);
	plane.init();
	plane_transform = Translate(0.0, -0.5, 0.0);

	/*vec4 eye(0.0, 0.0, 8.0, 1.0);
	vec4 at(0.0, 0.0, 0.0, 1.0);
	vec4 up(0.0, 1.0, 0.0, 0.0);
	camera.set_model_view(eye, at, up);*/

	camera.set_model_view(Translate(0.0, 0.0, -8.0));
	camera.set_projection(45.0, width/(float)height, 0.1, 100.0);

	//Lighting properties
	light_position_field = vec4(0.0, 10.0, 10.0, 0.0);
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
	cube.load();

	plane.SEND_FLAG = true;
	plane.load();
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
	glUniformMatrix4fv(object_mv_loc, 1, GL_TRUE, cube_transform);
	glUniform1f(shininess_loc, cube.shininess());	
	cube.draw();

	//Lighting for the plane
	ambient_product = light_ambient_field * plane.ambient();
	diffuse_product = light_diffuse_field *  plane.diffuse();
	specular_product = light_specular_field * plane.specular();

	glUniform4fv(ambient_product_loc, 1, ambient_product);
	glUniform4fv(diffuse_product_loc, 1, diffuse_product);
	glUniform4fv(specular_product_loc, 1, specular_product);
	glUniformMatrix4fv(object_mv_loc, 1, GL_TRUE, plane_transform);
	glUniform1f(shininess_loc, plane.shininess());	
	plane.draw();
}

//https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Arcball
//http://web.cse.ohio-state.edu/~hwshen/781/Site/Slides_files/trackball.pdf
void Scene::motion_func(int x, int y)
{
	if(track_field.track_ball_on)
	{
		track_field.current_x = x;
		track_field.current_y = y;
	}
}

void Scene::mouse_click(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		track_field.track_ball_on = true;
		track_field.last_x = track_field.current_x = x;
		track_field.last_y = track_field.current_y = y;
	}
	else
	{
		track_field.track_ball_on = false;
	}
}

vec3 Scene::get_trackball_vector(int x, int y)
{
	//Convert to [-1, 1] coordinates
	vec3 P = vec3(1.0*x/window_width*2.0 - 1.0, 
				  1.0*y/window_height*2.0 - 1.0,
				  0);
	P.y = -P.y;		//Invert y since screen y is inverted

	float op_squared = P.x * P.x + P.y * P.y;
	if (op_squared <= 1.0)
	{
		P.z = sqrt(1.0 - op_squared);
	}
	else
	{
		P = normalize(P);
	}
	return P;
}

void Scene::idle_move_trackball()
{
	if (track_field.last_x != track_field.current_x &&
		track_field.last_y != track_field.current_y)
	{
		vec3 p1 = get_trackball_vector(track_field.last_x, track_field.last_y);
		vec3 p2 = get_trackball_vector(track_field.current_x, track_field.current_y);
		float angle = -acos(std::min(1.0f, (float)dot(p1, p2)));
		vec3 axis = cross(p1, p2);
		track_field.angle += angle;
		camera.set_model_view(Translate(0.0, 0.0, -8.0) * rotationMatrix(axis,track_field.angle));
		//std::cout << "Idle function is running...\n";
	}
}

//http://www.neilmendoza.com/glsl-rotation-about-an-arbitrary-axis/
//Not made by me, On blog by Neil Mendoza
mat4 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    
    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}
//End of copied code

/*void Scene::keyboard(unsigned char key, int x, int y)
{
	//
}*/

void Scene::reshape(int width, int height)
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
}
