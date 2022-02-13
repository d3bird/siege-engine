#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../rendering/shader.h"

#include "light_factory.h"
#include "light_animation_mgr.h"

class light_mgr
{
public:
	light_mgr(int max_lights_in_scene);
	~light_mgr();

	void update();

	int create_light_scene(int max_lights, bool set_as_current = false);
	void delete_light_scene(int index);

	void set_current_scene(int index);
	void clear_current_scene();

	//adds to curent scene if none specified
	void add_def_light(glm::vec3 col, glm::vec3 pos, int scene = -1);

	void print_info();
	void print_info(def_light* in);
	void print_info(lighting_scene* in);

	void init();

	void set_trigger_update(bool i) { need_update = i; }

	//getters
	lighting_scene* get_current_scene() { return current_scene; }
	bool need_to_update() { return need_update; }
	int get_scene_amount() { return l_scenes.size(); }

private:

	bool need_update;

	light_factory* factory;

	//scence information
	int max_lights_scence;
	int current_index;
	lighting_scene* current_scene;
	std::vector< lighting_scene*> l_scenes;

	inline bool is_scene_index_valid(int in);

	//lighting vars

	bool draw_lights_debug;
	bool update_lights;

	std::vector<glm::vec3> lightPositions;
	std::vector<glm::vec3> lightColors;

	const unsigned int NR_LIGHTS = 32;

	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;
	 
};

