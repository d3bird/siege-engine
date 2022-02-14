#pragma once

#include "object_data.hpp"
#include "../utility/logger.h"
#include <time.h>

#include "../core/optimized_spawner.h"
#include "terrian_data.hpp"

#include "generation/world_generation.h"


class world{
public:
	world(map_data* map);
	world(map_data*** map);

	~world();

	bool generated_correctly() { return inited; }
	void set_time(timing* t) { time = t; }


	void update();

	void spawn_object(int x, int y, int z, int object, float angle = 0);
	void place_heat_source(int x, int y, int z);

	void find_pathing(int x_s, int y_s, int z_s, int x_e, int y_e, int z_e);

	map_data* get_map_info() { return map_info; }

private:
	
	void init(int x_size, int y_size, int z_size, optimized_spawner* OBJM);
	timing* time = NULL;
	bool inited = false;
	world_generator* world_gen;

	int x_size;
	int z_size;
	int y_size;

	void update_obj_angle(item_info* obj, optimized_spawner* OBJM, float angle);


	std::vector<zone*> map_zones;

	//for a single cell world
	map_cell*** world_map = NULL;
	map_data* map_info = NULL;

	//large world map
	map_data*** large_map;

	//misc functions
	bool is_valid_loc(int x, int y, int z);

};

