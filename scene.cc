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
	window_width = width;
	window_height = height;

	track_field.track_ball_on = false;
	track_field.last_x = 0;
	track_field.last_y = 0;
	track_field.current_x = 0;
	track_field.current_y = 0;
	track_field.angle = 0.0;

	follow_mouse = true;
	first_person = false;

	player.init(1.5, 1.5, 1.5);
	player.move_to(vec3(0.0, 0.0, 0.21));

	ground.init(50, 50);

	/*vec4 eye(0.0, 0.0, 8.0, 1.0);
	vec4 at(0.0, 0.0, 0.0, 1.0);
	vec4 up(0.0, 1.0, 0.0, 0.0);
	camera.set_model_view(eye, at, up);*/

	camera.set_model_view(Translate(0.0, 0.0, -15.0));
	std::cout << "model_view = " << camera.get_model_view() << std::endl;
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

	player.load();

	ground.load();
}

void Scene::draw_objects()
{
	vec4 ambient_product, diffuse_product, specular_product;

	//Camera and light positiong
	glUniformMatrix4fv(camera_mv_loc, 1, GL_TRUE, camera.get_model_view());
	glUniformMatrix4fv(projection_loc, 1, GL_TRUE, camera.get_projection());
	glUniform4fv(light_position_loc, 1, light_position_field);

	//Draw the player in the scene
	player.draw(ambient_product_loc, diffuse_product_loc, specular_product_loc,
				object_mv_loc, shininess_loc, 
				light_ambient_field, light_diffuse_field, light_specular_field);

	//Draw the ground in the scene
	ground.draw(ambient_product_loc, diffuse_product_loc, specular_product_loc,
				object_mv_loc, shininess_loc, 
				light_ambient_field, light_diffuse_field, light_specular_field);
}

void Scene::mouse_motion(int x, int y)
{

	if (follow_mouse)
	{
		vec4 ray = cast_ray(x, y, window_width, window_height, 
						  	camera.get_model_view(), camera.get_projection());

		//std::cout << "ray = " << ray << std::endl;

		vec4 intersect_point;
		vec4 ground_normal = ground.get_normal();
		ground_normal.w = 0.0;
		vec4 plane_p0(0.0, 0.0, 0.0, 1.0);
		vec4 camera_pos = camera.position();
		if (ray_intersect_plane(plane_p0, ground_normal, 
							    camera_pos, ray, intersect_point))
		{
			player.move_to(vec3(intersect_point.x, intersect_point.y, intersect_point.z));
		}
		glutPostRedisplay();
	}
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
		follow_mouse = false;

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
		track_field.last_y != track_field.current_y &&
		track_field.track_ball_on)
	{
		vec3 p1 = get_trackball_vector(track_field.last_x, track_field.last_y);
		vec3 p2 = get_trackball_vector(track_field.current_x, track_field.current_y);
		float angle = -acos(std::min(1.0f, (float)dot(p1, p2)));
		vec3 axis = cross(p1, p2);
		//std::cout << Translate(0.0, 0.0, 15.0) * camera.get_model_view() << std::endl;
		//camera.set_model_view(Translate(0.0, 0.0, 15.0) * camera.get_model_view());
		camera.set_model_view(camera.get_model_view() * rotation(axis, 0.1*angle));
		//camera.set_model_view(Translate(0.0, 0.0, -15.0) * camera.get_model_view());
		//std::cout << "Idle function is running...\n";
	}

}

void Scene::keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'c':
			camera.set_model_view(Translate(0.0, 0.0, -15.0));
			follow_mouse = true;
			glutPostRedisplay();
			break;
		case 'v':
			first_person = true;
			break;

		case 'w': 
			player.move_to_position(vec3(0.0, 1.0, 0.0));
			break;
		case 's': 
			player.move_to_position(vec3(0.0, -1.0, 0.0));
			break;
		case 'a': 
			player.move_to_position(vec3(-1.0, 0.0, 0.0));
			break;
		case 'd':
			player.move_to_position(vec3(1.0, 0.0, 0.0));
			break;

		case 033:
			exit(EXIT_SUCCESS);
			break;
	}	
}

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
