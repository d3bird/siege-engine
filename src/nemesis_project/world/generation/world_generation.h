#pragma once


#include "../world.h"
#include "../terrian_data.hpp"
#include "../../core/optimized_spawner.h"

struct world_gen_settings {
	int x_cell_size;
	int y_cell_size;
	int z_cell_size;

	int x_cell_amount;
	int y_cell_amount;
	int z_cell_amount;

	bool flat_land;
	int ground_level;

};

class world_generation {
public:
	world_generation(optimized_spawner* spawn);
	~world_generation();

	world* create_world(world_gen_settings* input, bool force = false);

	//premade settings

	world_gen_settings* flat_land_settings();

private:
	optimized_spawner* spawner;

	bool is_settings_valid(world_gen_settings* test);

	local_map_data* world_generation::create_blank_cell(int x_siz, int y_siz, int z_siz);
	void create_blank_cell(map_data* world, world_gen_settings* settings, int x_index, int y_index, int z_index);

	void print_settings(world_gen_settings* settings);
};