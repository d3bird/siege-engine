#pragma once 

#include "light_data.hpp"

class light_factory
{
public:
	light_factory(int scene_light_max);
	~light_factory();

	lighting_scene* create_light_scene(int max_lights);
	void delete_lighting_scene(lighting_scene* input);

	bool create_light(glm::vec3 pos, glm::vec3 col, lighting_scene* scene);
	void delete_light(def_light* light, lighting_scene* scene);

private:
	int light_max;

};

