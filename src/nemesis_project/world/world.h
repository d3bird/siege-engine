#pragma once

#include "../core/optimized_spawner.h"
#include "terrian_data.hpp"

class world {
public:
	world();

	~world();

	void init(int x_size, int y_size, int z_size, optimized_spawner* OBJM);

	map_data* world_map;

private:

	bool inited = false;

	int x_size;
	int z_size;
	int y_size;

	void update_obj_angle(item_info* obj, optimized_spawner* OBJM, float angle);
};

