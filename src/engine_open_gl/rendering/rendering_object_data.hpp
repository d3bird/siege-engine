#pragma once

#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <vector>
#include <string>

//opengl information
#include "model.h"
#include "shader.h"
#include "rotation.h"

struct item_info
{
	bool custom_rot_angle = false;
	glm::vec3 rot;
	glm::vec3 loc;//on the screen

	rotation angles;

	glm::mat4* mat;

	//old information
	unsigned int debug_id;
	unsigned int item_id;
	unsigned int buffer_loc;
	unsigned int amount;
	float x_m, y_m, z_m;// the location in the engine
	float x_scale = 1;
	float y_scale = 1;
	float z_scale = 1;

	int rendering_group = -1;

	float x_rot = 0;
	float y_rot = 1;
	float z_rot = 0;

	float angle = 0;

	std::string* item_name;
	int type;

};

struct item
{
	//rendering information
	int spawn_id;
	std::string loc;
	std::string * item_name;
	std::vector< item_info*> item_data;
	bool generated_correctly = false;

	//open gl information
	Model* model;
	unsigned int buffer;
	unsigned int buffer_size;
	unsigned int amount;
	glm::mat4* modelMatrices;
	Shader* custom_shader;
	int type;
	bool updatemats = true;
	bool draw = true;

};

static void clean_object_data(item_info* obj_data) {
	if (obj_data == NULL) {
		return;
	}
	if (obj_data->mat != NULL) {
		delete obj_data->mat;
	}

	//if (obj_data->proporties != NULL) {
	//	clean_object_proporites(obj_data->proporties);
	//}

	delete obj_data;
}

static void clean_item(item* it) {
	if (it == NULL) {
		return;
	}
	for (int i = 0; i < it->item_data.size(); i++) {
		clean_object_data(it->item_data[i]);
	}
	it->item_data.clear();
	delete it;
}
