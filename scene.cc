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
	previous = vec2(2.0, 2.0);

	current_tree = -1;
	current_rock = -1;

	logs = 0;
	leafs = 0;
	stones = 0;

	window_width = width;
	window_height = height;

	track_field.track_ball_on = false;
	track_field.last_x = 0;
	track_field.last_y = 0;
	track_field.current_x = 0;
	track_field.current_y = 0;

	follow_mouse = true;
	first_person = false;
	place_object = false;
	place_tree = false;
	place_rock = false;


	player.init(1.5, 1.5, 1.5);
	player.move_to(vec3(2.0, 2.0, 0.21));

	ground.init(50, 50);
	/*Tree tree;
	trees.push_back(tree);
	trees[0].init();

	Rock rock;
	rocks.push_back(rock);
	rock[0].init();*/

	camera.set_model_view(Translate(0.0, 0.0, -44.0));
	//std::cout << "model_view = " << camera.get_model_view() << std::endl;
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
	//trees[0].load();
}

void Scene::draw_objects()
{
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

	//Draw all trees
	for (size_t i = 0; i < trees.size(); ++i)
	{
		trees[i].draw(ambient_product_loc, diffuse_product_loc, specular_product_loc,
				  	  object_mv_loc, shininess_loc, 
			  		  light_ambient_field, light_diffuse_field, light_specular_field);
	}

	//Draw all rocks
	for (size_t i = 0; i < rocks.size(); ++i)
	{
		rocks[i].draw(ambient_product_loc, diffuse_product_loc, specular_product_loc,
				  	  object_mv_loc, shininess_loc, 
			  		  light_ambient_field, light_diffuse_field, light_specular_field);
	}
}

void Scene::mouse_motion(int x, int y)
{
	if (follow_mouse && place_object)
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
			if (place_tree)
			{
				trees[current_tree].move_to(vec3(intersect_point.x, intersect_point.y, intersect_point.z));
			}
			else
			{
				rocks[current_rock].move_to(vec3(intersect_point.x, intersect_point.y, intersect_point.z));
			}
		}
		glutPostRedisplay();
	}
	else if (first_person)
	{
		/*float xd = (2.0f * x) / window_width - 1.0f;
		float yd = 1.0f - (2.0f * y) / window_height;*/

		y = window_height - y;

		if (previous.x == 2.0 || previous.y == 2.0)
			previous = vec2(x, y);

		vec2 look = previous - vec2(x, y);

		//camera.at().z -= 0.001*look.y;

		//std::cout << 200*look.x << std::endl;

		camera.at() = RotateZ(look.x) * camera.at();

		previous = vec2(x, y);
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
		if (follow_mouse && place_object)
		{
			place_object = false;
			place_tree = false;
			place_rock = false;
		}
		else if (!first_person && !follow_mouse)
		{
			track_field.track_ball_on = true;
			track_field.last_x = track_field.current_x = x;
			track_field.last_y = track_field.current_y = y;
		}
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
		camera.set_model_view(camera.get_model_view() * rotation(axis, 0.1*angle));
	}
}

void Scene::keyboard(unsigned char key, int x, int y)
{
	vec4 eye, up, at;
	Tree tree;
	Rock rock;

	switch(key)
	{
		case 'e':
			if (first_person)
			{
				std::vector<Tree>::iterator it;
				for (it = trees.begin(); it < trees.end(); ++it)
				{
					vec3 cam_pos(camera.eye().x, camera.eye().y, camera.eye().z);
					if (within_range(cam_pos, it->position(), 3.0))
					{
						//std::cout << "Tree. Tree. Tree...\n";
						trees.erase(it);
						++logs; ++leafs;
						--current_tree;
						//create_crafting_menu();
					}
				}
				std::vector<Rock>::iterator it2;
				for (it2 = rocks.begin(); it2 < rocks.end(); ++it2)
				{
					vec3 cam_pos(camera.eye().x, camera.eye().y, camera.eye().z);
					if (within_range(cam_pos, it2->position(), 3.0))
					{
						rocks.erase(it2);
						stones += rand() % 10;
						--current_rock;
					}
				}
			}
			break;

		case 'c':
			player.set_visible();
			camera.set_model_view(Translate(0.0, 0.0, -44.0));
			follow_mouse = true;
			first_person = false;
			glutPostRedisplay();
			break;
		case 'v':
			create_crafting_menu();
			player.set_invisible();
			first_person = true;
			follow_mouse = false;
			eye = player.position();
			eye.z += 0.5;
			eye.w = 1.0;
			at = vec4(eye.x + 2.0, eye.y, eye.z, 1.0);
			at.z += 0.5;
			up = vec4(0.0, 0.0, 1.0, 0.0);
			camera.set_model_view(eye, at, up);
			glutPostRedisplay();
			break;
		case 'b':
			player.set_visible();
			first_person = false;
			follow_mouse = false;
			camera.set_model_view(Translate(0.0, 0.0, -44.0));
			glutPostRedisplay();
			break;

		case 't':
			if (follow_mouse)
			{
				if (current_tree == -1)
					current_tree = 0;
				else
					++current_tree;
				tree.init();
				trees.push_back(tree);
				place_object = true;
				place_tree = true;
			}
			break;
		case 'r':
			if (follow_mouse)
			{
				if (current_rock == -1)
					current_rock = 0;
				else
					++current_rock;
				rock.init();
				rocks.push_back(rock);
				place_object = true;
				place_rock = true;
			}
			break;

		case 'w': 
			if(first_person)
			{
				camera.move_at(Camera::FORWARD);
			}
			else
			{
				player.move_to_position(vec3(0.0, 1.0, 0.0));
			}
			break;
		case 's': 
			if(first_person)
			{
				camera.move_at(Camera::BACKWARDS);
			}
			else
			{
				player.move_to_position(vec3(0.0, -1.0, 0.0));
			}
			break;
		case 'a': 
			if(first_person)
			{
				camera.move_at(Camera::LEFT);
			}
			else
			{
				player.move_to_position(vec3(-1.0, 0.0, 0.0));
			}
			break;
		case 'd':
			if(first_person)
			{
				camera.move_at(Camera::RIGHT);
			}
			else
			{
				player.move_to_position(vec3(1.0, 0.0, 0.0));
			}
			break;

		case 'z':
			if (follow_mouse)
			{
				camera.set_model_view(camera.get_model_view() * Translate(0.0, 0.0, 1.0));
				//std::cout << "z = " << camera.get_model_view()[2][3] << std::endl;
			}
			break;
		case 'x':
			if (follow_mouse)
			{
				camera.set_model_view(camera.get_model_view() * Translate(0.0, 0.0, -1.0));
				//std::cout << "z = " << camera.get_model_view()[2][3] << std::endl;
			}
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

void Scene::create_crafting_menu()
{
	if (logs > 0)
	{
		std::string s = "Log " + to_string(logs);
		glutAddMenuEntry(s.c_str(), LOGS);
	}
	if (leafs > 0)
	{
		std::string s = "Leafs " + to_string(leafs);
		glutAddMenuEntry(s.c_str(), LEAFS);
	}
	if (stones > 0)
	{
		std::string s = "Stones " + to_string(stones);
		glutAddMenuEntry(s.c_str(), ROCKS);
	}
	if (logs >= 2 && leafs > 0)
	{
		glutAddMenuEntry("Hut", HUT);
	}
}

std::string to_string(int a)
{
	std::stringstream ss;
	ss << a;
	return ss.str();
}
