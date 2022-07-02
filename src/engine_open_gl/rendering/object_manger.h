#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstdlib>
#include <ctime>

#include "model.h"
#include "shader.h"
#include "time.h"

#include "rendering_object_data.hpp"

#include "../misc/external_files.hpp"

/*
* This class handlse all the rendering for each of the differnt objects
* each object has one draw call that will draw every instance of that object
* an object can be spawned at a loaction(x y z) or a given transform
* the created object will return a pointer to a object so if anything needs to be changed from the defualts it can be changed or add to a update list
*/

//the data needed to render the objects in the engine

//update the matrix of a specfic item
struct update_pak {
	unsigned int item_id;
	unsigned int buffer_loc;
	float x,y,z;
	float x_scale;
	float y_scale;
	float z_scale;
	float rox_x = 0;
	float rox_y = 1;
	float rox_z = 0;
	rotation angle;
};

//transfer object to tell the map where all the maps are located
struct item_loc {
	int x, y, z;
	item_info* object;
	item_loc(item_info* o, int x1, int y1, int z1) {
		object = o;
		x = x1;
		y = y1;
		z = z1;
	}
};

class object_manger{
public:

	object_manger();
	~object_manger();

	void draw();

	int add_model(std::string name, std::string loc, unsigned int buffer_size, int type, bool draw = true, Shader* custom_shader = NULL);

	void init();

	void update_item_matrix(update_pak* data, glm::mat4 given_mat = glm::mat4(-1.0f));

	item_info* spawn_item(int type, int x, int y, int z, glm::mat4* given_mat = NULL);
	item_info* spawn_item(int type,int x, int y, int z, float angle);

	//getters and setters
	void set_projection(glm::mat4 i) { projection = i; update_projection = true; if (common != NULL) { common->setMat4("projection", i); } }
	void set_cam(glm::mat4 i) { view = i; update_cam = true; }
	void set_standered_shader(Shader* i) { common = i; }

	bool need_cam_updates() { return using_custom_shaders; }

	void delete_item_from_buffer(item_info* it);

	std::vector< item*>* get_all_item_info() { return &items; }

	void clear_all_object();
	void clear_all_models();
	//new generation based optimization
	std::vector< item*>* create_blank_item_list();

private:


	bool increase_buffer_size(int item_index);

	//common vars
	bool update_projection;
	bool update_cam;

	bool using_custom_shaders;

	unsigned int object_id;
	glm::mat4 view;
	glm::mat4 projection;
	Shader* common;

	const int max_buffer_size = 1000000;

	std::vector< item*> items;//every item
	std::vector< bool> draw_item;//wheither to draw item

	//optimised rendering
	void clear_optimised_items();

	std::vector< item*> optimised_items;//items based on where the player is

};

