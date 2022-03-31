#pragma once

#include "../../../core/optimized_spawner.h"
#include "../../../utility/random_gen.hpp"

#include <time.h>

#include "../../terrian_data.hpp"


#include "generation_objs.hpp"

//this class creates local_map_data and modifys local_map_data to create differnt worlds
class world_generator{
public:
	world_generator(optimized_spawner* objm);
	~world_generator();

	local_map_data*** create_full_world_map(world_gen_settings* settings);

	local_map_data* create_blank_world_cell(int x_size, int y_size, int z_size, bool spawn_bottom = true);

	//generic generation functions for a single cell
	void generate_test_world(local_map_data* input);
	
	void generate_valley_world(local_map_data* input);
	void generate_hill_world(local_map_data* input);
	void generate_forest_world(local_map_data* input);

	void generate_room_test(local_map_data* input);

	void generate_air_drop(local_map_data* input);

	//generation functions for the scrolling world

	void generate_plane_scroll(local_map_data* input, bool spawn_items = false);
	void generate_hill_scroll(local_map_data* input, bool spawn_items = false);

private:

	optimized_spawner* OBJM;

	//single map cell functions
	void place_circle(int x0, int layer, int y0, int radius, bool fill,bool add_floor, local_map_data* input);
	void place_square(int x, int y, int z, int x_width, int z_width, local_map_data* input);

	void generate_hill(int x, int y, int z, int radius, int height, local_map_data* input);
	void place_trees_in_area(int start_x, int start_y, int start_z, 
		int end_x, int end_y, int end_z, local_map_data* input);
	void smooth_in_ramps(local_map_data* input);
	void add_in_missing_floors(local_map_data* input);

	void place_furnaces(int x, int y, int z, int x_width, int z_width, local_map_data* input);

	//multi cell map functions
	void smooth_cells(local_map_data* main, local_map_data* left, local_map_data* right, local_map_data* north, local_map_data* south);

	void update_obj_angle(item_info* obj, float angle = 0);

	//debugging functions

	void print_layer(int layer, int print_type, local_map_data* input);
};

