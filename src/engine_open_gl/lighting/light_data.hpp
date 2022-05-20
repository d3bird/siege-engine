#pragma once

#include <vector>
#include <glm/glm.hpp>

struct def_light
{
	bool on = true;
	glm::vec3* light_col;
	glm::vec3* light_loc;

	int current_index = -1;

	def_light(glm::vec3* c_loc, glm::vec3* p_loc) {
		light_col = c_loc;
		light_loc = p_loc;
	}
};

struct lighting_scene
{

	size_t index = -1;

	int max_lights= 10;
	int current_lights = 0;

	std::vector < glm::vec3*> light_pos;
	std::vector < glm::vec3*> light_col;

	std::vector< def_light*> active_lights;
	std::vector< def_light*> non_active_lights;
};