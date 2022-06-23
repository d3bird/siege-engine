#include "world_generation.h"

#include <map>

world_generator::world_generator(optimized_spawner* objm) {
	OBJM = objm;
}
world_generator::~world_generator() {

}


local_map_data* world_generator::create_blank_world_cell(int x_siz, int y_siz, int z_siz, bool spawn_bottom) {
	//std::cout << "create_blank_world_cell " << std::endl;

	int x_size = x_siz;
	int y_size= y_siz;
	int z_size= z_siz;
	
//	std::cout << "x_size: " << x_size << std::endl;
	//std::cout << "y_size: " << y_size << std::endl;
	//std::cout << "z_size: " << z_size << std::endl;

	//std::cout << "create data" << std::endl;

	//init the map
	map_cell*** world_map;
	world_map = new map_cell * *[y_size];

	for (int y = 0; y < y_size; y++) {
		world_map[y] = new   map_cell * [x_size];
		for (int x = 0; x < x_size; x++) {
			world_map[y][x] = new map_cell[z_size];
		}
	}

	for (int y = 0; y < y_size; y++) {
		for (int x = 0; x < x_size; x++) {
			for (int z = 0; z < z_size; z++) {
				world_map[y][x][z].x = x;
				world_map[y][x][z].y = y;
				world_map[y][x][z].z = z;

				world_map[y][x][z].ground = NULL;
				world_map[y][x][z].floor = NULL;
				world_map[y][x][z].zone_on_top = NULL;
				world_map[y][x][z].link_to_platform = NULL;


			}
		}
	}


	if (spawn_bottom) {
		int y = 0;
		for (int x = 0; x < x_size; x++) {
			for (int z = 0; z < z_size; z++) {
				world_map[y][x][z].floor = OBJM->spawn_item(FLOOR_TEMP, x, y, z);
			}
		}
	}

	//std::cout << "creating data obj" << std::endl;

	local_map_data* map_info = new local_map_data;

	map_info->x_size = x_size;
	map_info->y_size = y_size;
	map_info->z_size = z_size;
	map_info->map = world_map;
	
	map_info->generated_blank = true;;

	return map_info;
}

local_map_data*** world_generator::create_full_world_map(world_gen_settings* settings) {
	local_map_data*** output = NULL;

	if (settings == NULL) {
		return output;
	}

	//creating map data array
	output = new local_map_data * *[settings->cells_wide];
	for (int i = 0; i < settings->cells_wide; i++) {
		output[i] = new local_map_data * [settings->cells_long];
	}

	for (int i = 0; i < settings->cells_wide; i++) {
		for (int q = 0; q < settings->cells_long; q++) {
			output[i][q] = NULL;
		}
	}

	//fillin in the map blank data 
	int x_size = settings->x_size;
	int y_size = settings->y_size;
	int z_size = settings->z_size;
	
	for (int i = 0; i < settings->cells_wide; i++) {
		for (int q = 0; q < settings->cells_long; q++) {
			output[i][q] = create_blank_world_cell(x_size, y_size, z_size, true);
		}
	}

	//create the biome map


	//use the biome map to generate the map_cells

	biomes **biome_map;

	biome_map = new biomes * [settings->cells_wide];
	for (int i = 0; i < settings->cells_wide; i++) {
		biome_map[i] = new biomes  [settings->cells_long];
	}

	std::vector<std::pair<biomes, std::pair<int, int> > > cell_biomes;

	for (int i = 0; i < settings->cells_wide; i++) {
		for (int q = 0; q < settings->cells_long; q++) {
			std::pair<int, int> loc = std::make_pair(i, q);
			biomes biome = FOREST;

			if (i % 2 == 0 || q % 2 == 1) {
				biome = PLANE;
			}

			if (i == (int)(settings->cells_wide / 2) && q == (int)(settings->cells_long / 2)){
				biome = AIR_DROP;
			}

			cell_biomes.push_back(std::make_pair(biome, loc));
		}
	}

	for (int i = 0; i < cell_biomes.size(); i++) {
		int x = cell_biomes[i].second.first;
		int z = cell_biomes[i].second.second;
		switch (cell_biomes[i].first)
		{
		case FOREST:
			generate_forest_world(output[x][z]);
			break;
		case VALLEY:
			generate_valley_world(output[x][z]);
			break;
		case HILLS:
			generate_hill_world(output[x][z]);
			break;
		case AIR_DROP:
			generate_air_drop(output[x][z]);
			break;
		case PLANE:
		default:

			break;
		}

	}

	//smooth out the land
	for (int i = 0; i < settings->cells_wide; i++) {
		for (int q = 0; q < settings->cells_long; q++) {
			local_map_data* main = output[i][q];
			local_map_data* left = NULL;
			local_map_data* right = NULL;
			local_map_data* north = NULL;
			local_map_data * south = NULL;


			smooth_cells(main, left, right, north, south);
		}
	}

	return output;
}

void world_generator::generate_test_world(local_map_data* input) {

	place_circle(8, 0, 8, 6, true, false, input);
	//place_circle(8, 1, 8, 4, true, true, OBJM);
	//world_map[3][8][8].ground = OBJM->spawn_item(CUBE_TREE_T, 8, 1, 8);
	//world_map[3][8][8].floor = OBJM->spawn_item(FLOOR_TEMP, 8, 1, 8);
	//print_layer(0, 0, input);
	add_in_missing_floors(input);
//	print_layer(1, 0, input);
	//print_layer(2, 0, input);
	smooth_in_ramps(input);
	place_trees_in_area(0, 0, 0, 7, 7, 7, input);
}

void world_generator::generate_valley_world(local_map_data* input) {
	int depth = 3;
	int width = 5;

	bool middle_of_X = true;

	bool create_bridge = true;
	int bridge_width = 2;

	int x_size = input->x_size;
	int y_size = input->y_size;
	int z_size = input->z_size;

	float fill_percent = .4f;
	int fill_height =(int) (fill_percent * y_size);

	map_cell*** world_map = input->map;

	int x_tree_start = 0;
	int y_tree_start = 0;
	int z_tree_start = 0;

	int x_tree_end = 0;
	int y_tree_end = 0;
	int z_tree_end = 0;

	//fill in the ground
	for (int y = 0; y < fill_height; y++) {
		for (int x = 0; x < x_size; x++) {
			for (int z = 0; z < z_size; z++) {
				world_map[y][x][z].ground = OBJM->spawn_item(WALL_TEMP, x, y, z);
			}
		}
	}

	int ladder_x = x_size / 2;
	int ladder_z = z_size / 2;
	ladder_z -= 1;
	//carves away the ground
	if (middle_of_X) {
		int start_width = 2;
		int x_start = x_size / 2;

		int last_y = 0;
		for (int y = 0; y < (fill_percent * y_size); y++) {
			for (int x = x_start - y; x < x_start + start_width; x++) {
				for (int z = 0; z < z_size; z++) {
					OBJM->delete_item_from_buffer(world_map[y][x][z].ground);
					world_map[y][x][z].ground = NULL;

					if (x == ladder_x && z == ladder_z) {
						world_map[y][x][z].ground = OBJM->spawn_item(LADDER_T, x, y, z);
						update_obj_angle(world_map[y][x][z].ground, 270);
						last_y = y;
					}

				}
			}
			start_width++;
		}
		last_y++;
		world_map[last_y][ladder_x][ladder_z].ground = OBJM->spawn_item(LADDER_T, ladder_x, last_y, ladder_z);
		update_obj_angle(world_map[last_y][ladder_x][ladder_z].ground, 270);

		x_tree_start = x_start + start_width;
		x_tree_end = x_size - 1;

		z_tree_start = 0;
		z_tree_end = z_size - 1;

		if (create_bridge) {

			int z_brdge_start = z_size / 2;
			z_brdge_start -= bridge_width;
			int y =(int) (fill_percent * y_size) - 1;
			for (int x = x_start - y; x < x_start + start_width; x++) {
				for (int z = 0; z < z_size; z++) {
					if ((z >= z_brdge_start && z <= z_brdge_start + bridge_width) && y == (fill_percent * y_size) - 1) {
						if (world_map[y][x][z].ground == NULL) {
							world_map[y][x][z].ground = OBJM->spawn_item(WALL_TEMP, x, y, z);
						}

					}
				}
			}
		}
	}
	else {

	}

	add_in_missing_floors(input);
	smooth_in_ramps(input);

	//construct the buildings
	int y =(int) (fill_percent * y_size);
	place_square(0, y, 0, 5, 5, input);
	place_square(0, y + 1, 0, 5, 5, input);
	place_square(0, y + 2, 0, 4, 4, input);
	place_square(0, y + 2, 0, 3, 3, input);
	place_square(0, y + 2, 0, 2, 2, input);

	add_in_missing_floors(input);

	place_furnaces(0, y, 6, 4, 4, input);

	//add trees to the other side of the river
	y_tree_start = y;
	y_tree_end = y_tree_start;

	world_map[y_tree_start][x_tree_start][z_tree_start].ground = OBJM->spawn_item(CUBE_TREE_T, x_tree_start, y_tree_start, z_tree_start);
	world_map[y_tree_end][x_tree_end][z_tree_end].ground = OBJM->spawn_item(CUBE_TREE_T, x_tree_end, y_tree_end, z_tree_end);

	place_trees_in_area(x_tree_start, y_tree_start, z_tree_start, x_tree_end + 1, y_tree_end, z_tree_end + 1, input);


	//remove the end ramps at the bottom of the alley

	int start_width = 2;
	int x_start = x_size / 2;

	y = 0;
	for (int x = x_start - y; x < x_start + start_width; x++) {
		for (int z = 0; z < z_size; z++) {
			if (world_map[y][x][z].ground != NULL) {
				if (world_map[y][x][z].ground->type != LADDER_T) {
					OBJM->delete_item_from_buffer(world_map[y][x][z].ground);
					world_map[y][x][z].ground = NULL;
				}
			}
		}
	}


}

void world_generator::generate_hill_world(local_map_data* input) {


	int x_size = input->x_size;
	int y_size = input->y_size;
	int z_size = input->z_size;

	int x = x_size / 2;
	int z = z_size / 2;

	int height = 4;
	
	if (height >= y_size) {
		height = y_size - 1;
	}

	generate_hill(x, 0, z, 8, height, input);
	add_in_missing_floors(input);
	//print_layer(1, 0, input);
	smooth_in_ramps(input);
	place_trees_in_area(0, 0, 0, x_size, y_size , z_size, input);

}

void world_generator::generate_forest_world(local_map_data* input) {
	if (input == NULL) {
		return;
	}

	int x_size = input->x_size;
	int y_size = input->x_size;
	int z_size = input->x_size;

	int ground_level = 2;
	input->ground_level = ground_level;
	map_cell*** grid = input->map;

	for (int y = 0; y < y_size; y++) {
		for (int x = 0; x < x_size; x++) {
			for (int z = 0; z < z_size; z++) {

				if (y <= ground_level) {
					if (grid[y][x][z].ground == NULL) {
						grid[y][x][z].ground = OBJM->spawn_item(WALL_TEMP, x, y, z);
					}
					if (grid[y][x][z].floor == NULL) {
						grid[y][x][z].floor = OBJM->spawn_item(FLOOR_TEMP, x, y, z);
					}
				}
				else {
					if (y == ground_level +1) {
						if (grid[y][x][z].floor == NULL) {
							grid[y][x][z].floor = OBJM->spawn_item(FLOOR_TEMP, x, y, z);
						}
					}
				}

			}
		}
	}
}

void world_generator::generate_room_test(local_map_data* input) {
	place_square(0, 0, 0, 5, 5, input);
	place_square(7, 0, 7, 4, 4, input);

}

void world_generator::generate_hill(int x, int y, int z, int radius, int height, local_map_data* input) {

	for (int i = 0; i < height; i++) {
		place_circle(x, y + i, z, radius - i, true, true, input);
	}

}

void world_generator::place_square(int x, int y, int z, int x_width, int z_width, local_map_data* input) {

	map_cell*** world_map = input->map;
	for (int x1 = x; x1 < x + x_width; x1++) {
		for (int z1 = z; z1 < z + z_width; z1++) {
			if (x1 == x || x1 == x + x_width - 1) {
				if (world_map[y][x1][z1].ground == NULL) {
					world_map[y][x1][z1].ground = OBJM->spawn_item(WALL_TEMP, x1, y, z1);
				}
			}
			else if (z1 == z || z1 == z + z_width - 1) {
				if (world_map[y][x1][z1].ground == NULL) {
					world_map[y][x1][z1].ground = OBJM->spawn_item(WALL_TEMP, x1, y, z1);
				}
			}
		}
	}
}

void world_generator::place_circle(int x0, int layer, int y0, int radius, bool fill, bool add_floor, local_map_data* input) {
	std::cout << "placing hill" << std::endl;

	int x = radius;
	int y = 0;
	int err = 0;

	int wall_created = 0;
	map_cell*** world_map = input->map;
	while (x >= y)
	{
		world_map[layer][x0 + x][y0 + y].ground = OBJM->spawn_item(WALL_TEMP, x0 + x, layer, y0 + y);
		world_map[layer][x0 + y][y0 + x].ground = OBJM->spawn_item(WALL_TEMP, x0 + y, layer, y0 + x);
		world_map[layer][x0 - y][y0 + x].ground = OBJM->spawn_item(WALL_TEMP, x0 - y, layer, y0 + x);
		world_map[layer][x0 - x][y0 + y].ground = OBJM->spawn_item(WALL_TEMP, x0 - x, layer, y0 + y);
		world_map[layer][x0 - x][y0 - y].ground = OBJM->spawn_item(WALL_TEMP, x0 - x, layer, y0 - y);
		world_map[layer][x0 - y][y0 - x].ground = OBJM->spawn_item(WALL_TEMP, x0 - y, layer, y0 - x);
		world_map[layer][x0 + y][y0 - x].ground = OBJM->spawn_item(WALL_TEMP, x0 + y, layer, y0 - x);
		world_map[layer][x0 + x][y0 - y].ground = OBJM->spawn_item(WALL_TEMP, x0 + x, layer, y0 - y);
		wall_created += 8;
		

		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}

		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}

	std::cout << "the circle created " << wall_created << " walls" << std::endl;

	if (fill) {
		if (is_enclosed(x0, layer, y0, input)) {
			std::cout << "circle is enclosed" << std::endl;
			room* temp = generate_room(x0, layer, y0, input);
			if (temp != NULL) {
				for (int i = 0; i < temp->cells_in_room.size(); i++) {
					int x2 = temp->cells_in_room[i]->x;
					int y2 = temp->cells_in_room[i]->y;
					int z2 = temp->cells_in_room[i]->z;
					world_map[y2][x2][z2].ground = OBJM->spawn_item(WALL_TEMP, x2, y2, z2);
				}
				delete temp;
			}
		}
		else {
			std::cout << "circle is not enclosed" << std::endl;

		}

	}

	std::cout << "done placing hill" << std::endl;
}


void world_generator::generate_plane_scroll(local_map_data* input, bool spawn_items) {
	if (input == NULL) {
		std::cout << "input was null" << std::endl;
		return;
	}

	int x_size = input->x_size;
	int y_size = input->y_size;
	int z_size = input->z_size;
	
//	for (int y = 0; y < y_size; y++) {
	int y = 0;
		for (int x = 0; x < x_size; x++) {
			for (int z = 0; z < z_size; z++) {
				//std::cout << "making spot: " << x << " , " << z << std::endl;
				if (input->is_inbounds_of_map_local(x, y, z)) {
					input->map[y][x][z].gen_without_items = true;
					input->map[y][x][z].floor_type = FLOOR_TEMP;
					input->map[y][x][z].ground_type = WALL_TEMP;
				}
				//else {
				//	std::cout << "point was out of bounds" << std::endl;
				//}
			}
		}
	//}

		//add_in_missing_floors(input);

}

void world_generator::generate_hill_scroll(local_map_data* input, bool spawn_items) {

}

//fills in the cliffs with ramps
void world_generator::smooth_in_ramps(local_map_data* input) {
	std::cout << "adding in ramps" << std::endl;

	std::vector<item_info*> cornors;
	map_cell*** world_map = input->map;
	for (int y = 0; y < input->y_size; y++) {
		for (int x = 0; x < input->x_size; x++) {
			for (int z = 0; z < input->z_size; z++) {
				if (input->is_inbounds_of_map_local(x, y, z)) {
					if (world_map[y][x][z].ground != NULL) {
						if (world_map[y][x][z].ground->type == WALL_TEMP) {
							if (input->is_inbounds_of_map_local(x - 1, y, z)) {
								if (world_map[y][x - 1][z].ground == NULL && world_map[y][x - 1][z].floor != NULL) {
									world_map[y][x - 1][z].ground = OBJM->spawn_item(RAMP_T, x - 1, y, z);
								}
							}
							if (input->is_inbounds_of_map_local(x + 1, y, z)) {
								if (world_map[y][x + 1][z].ground == NULL && world_map[y][x + 1][z].floor != NULL) {
									world_map[y][x + 1][z].ground = OBJM->spawn_item(RAMP_T, x + 1, y, z);
									update_obj_angle(world_map[y][x + 1][z].ground, 180);
								}
							}
							if (input->is_inbounds_of_map_local(x, y, z - 1)) {
								if (world_map[y][x][z - 1].ground == NULL && world_map[y][x][z - 1].floor != NULL) {
									world_map[y][x][z - 1].ground = OBJM->spawn_item(RAMP_T, x, y, z - 1);
									update_obj_angle(world_map[y][x][z - 1].ground, 270);
								}
							}
							if (input->is_inbounds_of_map_local(x, y, z + 1)) {
								if (world_map[y][x][z + 1].ground == NULL && world_map[y][x][z + 1].floor != NULL) {
									world_map[y][x][z + 1].ground = OBJM->spawn_item(RAMP_T, x, y, z + 1);
									update_obj_angle(world_map[y][x][z + 1].ground, 90);
								}
							}
							if (input->is_inbounds_of_map_local(x - 1, y, z - 1)) {
								if (world_map[y][x - 1][z - 1].ground == NULL && world_map[y][x - 1][z - 1].floor != NULL) {
									cornors.push_back(world_map[y][x - 1][z - 1].ground);
								}
							}
							if (input->is_inbounds_of_map_local(x - 1, y, z + 1)) {
								if (world_map[y][x - 1][z + 1].ground == NULL && world_map[y][x - 1][z + 1].floor != NULL) {
									cornors.push_back(world_map[y][x - 1][z + 1].ground);
								}
							}
							if (input->is_inbounds_of_map_local(x + 1, y, z - 1)) {
								if (world_map[y][x + 1][z - 1].ground == NULL && world_map[y][x + 1][z - 1].floor != NULL) {
									cornors.push_back(world_map[y][x + 1][z - 1].ground);
								}
							}
							if (input->is_inbounds_of_map_local(x + 1, y, z + 1)) {
								if (world_map[y][x + 1][z + 1].ground == NULL && world_map[y][x + 1][z + 1].floor != NULL) {
									cornors.push_back(world_map[y][x + 1][z + 1].ground);
								}
							}
						}
					}
				}
			}
		}
	}

	//the cornors spawing parms
/*
	world_map[y][x - 1][z - 1].ground = OBJM->spawn_item(CORNOR_RAMP_DOWN_T, x - 1, y, z - 1);
	update_obj_angle(world_map[y][x - 1][z - 1].ground, OBJM, 270);
	world_map[y][x - 1][z + 1].ground = OBJM->spawn_item(CORNOR_RAMP_DOWN_T, x - 1, y, z + 1);
	world_map[y][x + 1][z - 1].ground = OBJM->spawn_item(CORNOR_RAMP_DOWN_T, x + 1, y, z - 1);
	update_obj_angle(world_map[y][x + 1][z - 1].ground, OBJM, 180);
	world_map[y][x + 1][z + 1].ground = OBJM->spawn_item(CORNOR_RAMP_DOWN_T, x + 1, y, z + 1);
	update_obj_angle(world_map[y][x + 1][z + 1].ground, OBJM, 90);
	*/

	//place in the cornors
	for (int i = 0; i < cornors.size(); i++) {

	}
	std::cout << cornors.size() << " cornors" << std::endl;
	std::cout << "done adding in ramps" << std::endl;
}

void world_generator::add_in_missing_floors(local_map_data* input) {
	int missing = 0;
	map_cell*** world_map = input->map;
	for (int y = 0; y < input->y_size; y++) {
		for (int x = 0; x < input->x_size; x++) {
			for (int z = 0; z < input->z_size; z++) {

				if (world_map[y][x][z].floor == NULL) {
					if (y == 0 ) {
						world_map[y][x][z].floor = OBJM->spawn_item(FLOOR_TEMP, x, y, z);
					}
					else if (world_map[y - 1][x][z].ground != NULL) {
						if (world_map[y - 1][x][z].ground->type == WALL_TEMP) {
							world_map[y][x][z].floor = OBJM->spawn_item(FLOOR_TEMP, x, y, z);
						}
					}
					
				}
			}
		}
	}
	std::cout << "found " << missing << " missing floors" << std::endl;
}

void world_generator::place_trees_in_area(int start_x, int start_y, int start_z,
	int end_x, int end_y, int end_z, local_map_data* input) {

	std::cout << "covering area with trees" << std::endl;
	int x_width;
	int y_width;
	int z_width;

	int x_start;
	int y_start;
	int z_start;

	//generating box cords
	if (end_x > start_x) {
		x_width = end_x - start_x;
		x_start = start_x;
	}
	else {
		x_width = start_x - end_x;
		x_start = end_x;
	}

	if (end_y > start_y) {
		y_width = end_y - start_y;
		y_start = start_y;
	}
	else {
		y_width = start_y - end_y;
		y_start = end_y;
	}

	if (end_z > start_z) {
		z_width = end_z - start_z;
		z_start = start_z;
	}
	else {
		z_width = start_z - end_z;
		z_start = end_z;
	}

	//checking to makesure it dose not go out of the box
	if (x_start + x_width >= input->x_size) {
		int diff = x_start + x_width  - input->x_size;
		x_width -= diff-1;
	}

	if (y_start + y_width  >= input->y_size) {
		int diff = y_start + y_width  - input->y_size;
		y_width -= diff-1;
	}

	if (z_start + z_width >= input->z_size) {
		int diff = z_start + z_width - input->z_size;
		z_width -= diff-1;
	}

	std::cout << "x_width:" << x_width << std::endl;
	std::cout << "y_width:" << y_width << std::endl;
	std::cout << "z_width:" << z_width << std::endl;

	std::cout << "x_start:" << x_start << std::endl;
	std::cout << "y_start:" << y_start << std::endl;
	std::cout << "z_start:" << z_start << std::endl;

	//get_numbers_between_bounds

	if (x_width == 0) {
		x_width += 1;
	}

	if (y_width == 0) {
		y_width += 1;
	}

	if (z_width == 0) {
		z_width += 1;
	}

	int spawned = 0;
	int should_spawn = x_width * z_width;
	float density = .3f;
	should_spawn =(int) (density * should_spawn);

	map_cell*** world_map = input->map;
	bool random_fill = true;

	if (random_fill) {
		int need_more =0;
		std::vector<double> y_spot = number_gen::get_numbers_between_bounds(should_spawn, y_start, y_start + y_width);
		std::vector<double> x_spot = number_gen::get_numbers_between_bounds(should_spawn, x_start, x_start + x_width);
		std::vector<double> z_spot = number_gen::get_numbers_between_bounds(should_spawn, z_start, z_start + z_width);

		for (int i = 0; i < should_spawn; i++) {
			if (i >= x_spot.size()) {
				std::cout << i <<"(i) was bigger than x_spot" << std::endl;
				return;
			}
			if (i >= y_spot.size()) {
				std::cout << i << "(i) was bigger than y_spot" << std::endl;
				return;
			}
			if (i >= z_spot.size()) {
				std::cout << i << "(i) was bigger than z_spot" << std::endl;
				return;
			}
			int x = (int) x_spot[i];
			int y = (int) y_spot[i];
			int z = (int) z_spot[i];
			if (input->is_inbounds_of_map_local(x, y, z)) {
				if (world_map[y][x][z].floor != NULL && world_map[y][x][z].ground == NULL) {
					world_map[y][x][z].ground = OBJM->spawn_item(CUBE_TREE_T, x, y, z);
					spawned++;
				}
			}
			else {
				std::cout << "out of bounds" << std::endl;
			}
		}
	}else{
		for (int y = y_start; y < y_start + y_width; y++) {
			for (int x = x_start; x < x_start + x_width; x++) {
				for (int z = z_start; z < z_start + z_width; z++) {
					if (input->is_inbounds_of_map_local(x, y, z)) {
						if (world_map[y][x][z].floor != NULL && world_map[y][x][z].ground == NULL) {
							world_map[y][x][z].ground = OBJM->spawn_item(CUBE_TREE_T, x, y, z);
							spawned++;
						}
						/*else {
							if (world_map[y][x][z].floor != NULL) {
								std::cout << "floor was null" << std::endl;
							}
							if (world_map[y][x][z].ground == NULL) {
								std::cout << "ground was not null" << std::endl;

							}
						}*/
					}
					else {
						std::cout << "out of bounds" << std::endl;
					}
				}
			}
		}
	}
	std::cout << "spawned: "<< spawned<<" | should spawn: "<< should_spawn << std::endl;
	std::cout << "done covering area with trees" << std::endl;

}

void world_generator::update_obj_angle(item_info* obj, float angle) {

	update_pak update_pac;

	update_pac.x = obj->x_m;
	update_pac.y = obj->y_m;
	update_pac.z = obj->z_m;

	update_pac.x_scale = 1;
	update_pac.y_scale = 1;
	update_pac.z_scale = 1;

	update_pac.angle.set_y_angle(angle);

	update_pac.buffer_loc = obj->buffer_loc;
	update_pac.item_id = obj->item_id;

	OBJM->update_item_matrix(&update_pac);

}

void world_generator::place_furnaces(int x, int y, int z, int x_width, int z_width, local_map_data* input) {

	if (input->is_inbounds_of_map_local(x, y, z)) {
		if (input->map[y][x][z].floor != NULL) {
			OBJM->delete_item_from_buffer(input->map[y][x][z].floor);
		}
		input->map[y][x][z].ground = OBJM->spawn_item(FURNACE_T, x, y, z);
		input->map[y][x][z].floor = input->map[y][x][z].ground;
		input->map[y][x][z].props = new additional_proporities;
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(FURNACE_GEAR_T, x, y, z));
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BEAM_T, x, y, z));
	}

	if (input->is_inbounds_of_map_local(x, y, z + 1)) {
		input->map[y][x][z + 1].ground = OBJM->spawn_item(BEAM_T, x, y, z + 1);
	}

	if (input->is_inbounds_of_map_local(x, y, z + 2)) {
		input->map[y][x][z + 2].ground = OBJM->spawn_item(BEAM_T, x, y, z + 2);
	}
	
	x += 4;

	if (input->is_inbounds_of_map_local(x, y, z)) {
		input->map[y][x][z].ground = OBJM->spawn_item(FURNACE_T, x, y, z);
		if (input->map[y][x][z].floor != NULL) {
			OBJM->delete_item_from_buffer(input->map[y][x][z].floor);
		}
		input->map[y][x][z].floor = input->map[y][x][z].ground;
		input->map[y][x][z].props = new additional_proporities;
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(FURNACE_GEAR_T, x, y, z));
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BEAM_T, x, y, z));
	}

	if (input->is_inbounds_of_map_local(x, y, z + 1)) {
		input->map[y][x][z + 1].ground = OBJM->spawn_item(BEAM_T, x, y, z + 1);
	}

	if (input->is_inbounds_of_map_local(x, y, z + 2)) {
		input->map[y][x][z + 2].ground = OBJM->spawn_item(BEAM_T, x, y, z + 2);
	}

	z += 3;

	if (input->is_inbounds_of_map_local(x, y, z)) {
		//input->map[y][x][z].ground = OBJM->spawn_item(GEAR_BOX_FRAME, x, y, z);

		if (input->map[y][x][z].floor != NULL) {
			OBJM->delete_item_from_buffer(input->map[y][x][z].floor);
		}
		input->map[y][x][z].floor = input->map[y][x][z].ground;

		input->map[y][x][z].props = new additional_proporities;
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BOX_G_UP, x, y, z));
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BOX_G_DOWN, x, y, z));
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BOX_G_L, x, y, z));
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BOX_G_R, x, y, z));
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BOX_G_N, x, y, z));
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BOX_G_S, x, y, z));

		//input->map[y][x][z].ground = OBJM->spawn_item(TEST_T, x + 2, y, z + 2);
		input->map[y][x][z].ground = OBJM->spawn_item(TEST_T, x, y, z);
	}

	x -= 2;
	if (input->is_inbounds_of_map_local(x, y, z)) {
		//input->map[y][x][z].ground = OBJM->spawn_item(GEAR_BOX_FRAME, x, y, z);

		if (input->map[y][x][z].floor != NULL) {
			OBJM->delete_item_from_buffer(input->map[y][x][z].floor);
		}
		input->map[y][x][z].floor = input->map[y][x][z].ground;

		input->map[y][x][z].props = new additional_proporities;
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BOX_G_UP, x, y, z));
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BOX_G_DOWN, x, y, z));
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BOX_G_L, x, y, z));
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BOX_G_R, x, y, z));
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BOX_G_N, x, y, z));
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BOX_G_S, x, y, z));

		//input->map[y][x][z].ground = OBJM->spawn_item(TEST_T, x + 2, y, z + 2);
		input->map[y][x][z].ground = OBJM->spawn_item(TEST_T, x, y, z);
	}

	x -= 2;
	if (input->is_inbounds_of_map_local(x, y, z)) {
		//input->map[y][x][z].ground = OBJM->spawn_item(GEAR_BOX_FRAME, x, y, z);

		if (input->map[y][x][z].floor != NULL) {
			OBJM->delete_item_from_buffer(input->map[y][x][z].floor);
		}
		input->map[y][x][z].floor = input->map[y][x][z].ground;

		input->map[y][x][z].props = new additional_proporities;
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BOX_G_UP, x, y, z));
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BOX_G_DOWN, x, y, z));
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BOX_G_L, x, y, z));
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BOX_G_R, x, y, z));
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BOX_G_N, x, y, z));
		input->map[y][x][z].props->additional_items.push_back(
			OBJM->spawn_item(GEAR_BOX_G_S, x, y, z));

		//input->map[y][x][z].ground = OBJM->spawn_item(TEST_T, x + 2, y, z + 2);
		input->map[y][x][z].ground = OBJM->spawn_item(TEST_T, x, y, z);

		std::cout << x << "," << y << "," << z << std::endl;
	}

}

//debug functions

void world_generator::print_layer(int layer, int print_type, local_map_data* input) {
	int y = layer;

	std::cout << "printing ";
	switch (print_type)
	{
	case 0:
		std::cout << "floors ";
		break;
	case 1:
		std::cout << "ground ";
		break;
	default:
		std::cout << "not a print type" << std::endl;
		return;
		return;
		break;
	}

	std::cout << "for layer " << layer << std::endl;;
	for (int x = 0; x < input->x_size; x++) {
		for (int z = 0; z < input->z_size; z++) {
			switch (print_type)
			{
			case 0:
				if (input->map[y][x][z].floor != NULL) {
					std::cout << "F ";
				}
				else {
					std::cout << "_ ";
				}
				break;
			case 1:
				if (input->map[y][x][z].ground != NULL) {
					std::cout << "G ";
				}
				else {
					std::cout << "_ ";
				}
				break;
			default:
				std::cout << "not a print type" << std::endl;
				return;
				break;
			}
			
		}
		std::cout << std::endl;
	}
}

void world_generator::generate_air_drop(local_map_data* input) {
	if (input == NULL) {
		return;
	}

	int ground_level = 0;
	input->ground_level = ground_level;
	for (int y = 0; y < input-> y_size; y++) {
		for (int x = 0; x < input->x_size; x++) {
			for (int z = 0; z < input->z_size; z++) {

				if (y == ground_level) {
					if (input->map[y][x][z].ground == NULL) {
						input->map[y][x][z].ground = OBJM->spawn_item(WALL_TEMP, x, y, z);

					}
					if (input->map[y][x][z].floor == NULL) {
						input->map[y][x][z].floor = OBJM->spawn_item(FLOOR_TEMP, x, y, z);
					}
				}
				else if (y == ground_level+1) {
					if (input->map[y][x][z].floor == NULL) {
						input->map[y][x][z].floor = OBJM->spawn_item(FLOOR_TEMP, x, y, z);
					}

				}
			}
		}
	}
}

//this function will take the main local_map_data and create ramps to match the height of the sournding
//cells if they have a higher ground level
void world_generator::smooth_cells(local_map_data* main, local_map_data* left, local_map_data* right,
	local_map_data* north, local_map_data* south) {

	if (main == NULL) {
		return;
	}



}