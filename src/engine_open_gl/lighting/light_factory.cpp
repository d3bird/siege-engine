#include "light_factory.h"

#include <iostream>

light_factory::light_factory(int scene_light_max) {

	light_max = scene_light_max;

	if (light_max <= 0) {
		light_max = 100;
		std::cout << "light cap set >= 0, setting it to "<< light_max << std::endl;
	}

}

light_factory::~light_factory()
{
}


lighting_scene* light_factory::create_light_scene(int max_lights) {
	lighting_scene* output = NULL;

	if (light_max <= 0) {
		std::cout << "there are no lights in this light scene" << std::endl;
	}
	else {
		if (max_lights > light_max) {
			std::cout << "this scene has more lights than is allowed, capping it to max" << std::endl;
			max_lights = light_max;
		}

		output = new lighting_scene;
		output->max_lights = max_lights;

	}


	return output;
}

void light_factory::delete_lighting_scene(lighting_scene* input) {

	if (input != NULL) {

		for (int i = 0; i < input->active_lights.size(); i++) {
			delete_light(input->active_lights[i], input);
		}
		for (int i = 0; i < input->non_active_lights.size(); i++) {
			delete_light(input->non_active_lights[i], input);
		}

		input->active_lights.clear();
		input->non_active_lights.clear();

		for (int i = 0; i < input->light_pos.size(); i++) {
			if (input->light_pos[i] != NULL) {
				delete input->light_pos[i];
			}
			if (input->light_col[i] != NULL) {
				delete input->light_col[i];
			}
		}
		input->light_pos.clear();
		input->light_col.clear();

		delete input;
	}
}


bool light_factory::create_light(glm::vec3 pos, glm::vec3 col, lighting_scene* scene) {

	if (scene != NULL) {

		if (scene->current_lights < scene->max_lights) {

			glm::vec3* l_pos = new glm::vec3(pos);
			glm::vec3* l_cor = new glm::vec3(col);

			def_light* light = new def_light(l_pos, l_cor);

			scene->light_pos.push_back(l_pos);
			scene->light_col.push_back(l_cor);

			int current_loc = -1;

			if (light->on) {
				current_loc = scene->active_lights.size();
				scene->active_lights.push_back(light);
			}
			else {
				current_loc = scene->non_active_lights.size();
				scene->non_active_lights.push_back(light);
			}

			light->current_index = current_loc;

			scene->current_lights += 1;
			return true;
		}
		else {
			std::cout << "light scene is full" << std::endl;
			std::cout << "scene->current_lights: " << scene->current_lights << std::endl;
			std::cout << "scene->max_lights: "<< scene->max_lights << std::endl;
		}
	}
	return false;
}

void light_factory::delete_light(def_light* light, lighting_scene* scene) {

	if (scene != NULL && light != NULL) {



	}
	else if (light != NULL) {
		delete light->light_col;
		delete light->light_loc;
		delete light;
		light = NULL;
	}

}