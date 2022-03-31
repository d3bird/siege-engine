#pragma once

#include "../../object_data.hpp"
#include "../../../utility/logger.h"
#include <time.h>

#include "../../terrian_data.hpp"
#include "../../../core/optimized_spawner.h"


#include "../../../utility/random_gen.hpp"

#include "generation_objs.hpp"
#include "world_generation.h"
#include "city_generation.h"

#include "../../world.h"
#include "../../mobil_platform.h"


//this class creates local_map_data and modifys local_map_data to create differnt worlds
class generation_pipeline{
public:
	generation_pipeline(optimized_spawner* objm);
	~generation_pipeline();


	void set_to_def_settings();
	void set_gen_settings(gen_setttings* input);
	void set_city_gen_settings(city_gen_settings* input);
	void set_world_gen_settings(world_gen_settings* input);

	//generating the terrians
	mobil_platform* create_mobil_city();
	world* create_world();

	world* create_world_single_cell();

private:
	//helper functions
	void offset_world_map(local_map_data*** input);//moves the objects to their respective spots
	void offset_world_map(local_map_data* input);//moves the objects to their respective spots

	void create_motion_systems(local_map_data*** input);// creates the motion systems for the maps
	void create_motion_systems(local_map_data* input);

	void create_thermal_systems(local_map_data*** input);// creates the thernak systems for the maps
	void create_thermal_systems(local_map_data* input);

	bool check(local_map_data*** input);// checks the generated maps for errors
	bool check(local_map_data* input);

	//creates the que and returns the index point for that que
	int create_optimised_rendering_que(local_map_data* input, bool set_primary = false);

	void update_obj_angle(item_info* obj, float angle);

	//settings and required engine componates
	optimized_spawner* OBJM;
	gen_setttings* def_settings;
	gen_setttings* given_settings;
	bool using_def;

	//generators and analyzers
	world_generator* world_gen;
	city_generator* city_gen;

};

