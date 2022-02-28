#pragma once

#include "manager/belt_manager.h"
#include "manager/door_manager.h"

#include "../core/optimized_spawner.h"
#include "terrian_data.hpp"

class world {
public:
	world();

	~world();

	void place_belt(int x, int y, int z, int dir);

	void init(int x_size, int y_size, int z_size, optimized_spawner* OBJM);

	map_data* world_map;

private:

	bool inited = false;

	int x_size;
	int z_size;
	int y_size;

	belt_manager* belts;
	door_data::door_manager* doors;
	optimized_spawner* OBJM;

	void update_obj_angle(item_info* obj, optimized_spawner* OBJM, float angle);

	//this is for testing purposes 
	void gen_test_world(optimized_spawner* OBJM);

	void gen_flight_world();

};

