#include "world_generation.h"

#include <iostream>

world_generation::world_generation(optimized_spawner* spawn) {
	spawner = spawn;
}


world_generation::~world_generation() {

}

world* world_generation::create_world(world_gen_settings* input, bool force) {
	world* output = NULL;
	if (is_settings_valid(input) || force) {
		//create the base object
		output = new world;
		output->init(spawner);

		print_settings(input);

		//create the base map

		map_data* world_map = new map_data;
		world_map->x_size = input->x_cell_amount;
		world_map->y_size = input->y_cell_amount;
		world_map->z_size = input->z_cell_amount;

		world_map->world_map = new local_map_data * *[world_map->y_size];
		for (int y = 0; y < world_map->y_size; y++) {
			world_map->world_map[y] = new local_map_data * [world_map->x_size];
			for (int x = 0; x < world_map->x_size; x++) {
				world_map->world_map[y][x] = new local_map_data[world_map->z_size];
			}
		}

		for (int y = 0; y < world_map->y_size; y++) {
			for (int x = 0; x < world_map->x_size; x++) {
				for (int z = 0; z < world_map->z_size; z++) {
					create_blank_cell(world_map, input, x, y, z);
				}
			}
		}

		if (input->flat_land) {
			int y_m = 0;// input->ground_level;

			int x_siz = input->x_cell_size;
			int y_siz = input->y_cell_size;
			int z_siz = input->z_cell_size;

			for (int x_m = 0; x_m < world_map->x_size; x_m++) {
				for (int z_m = 0; z_m < world_map->z_size; z_m++) {

					map_cell*** local_map = world_map->world_map[y_m][x_m][z_m].map;

					int x_off = world_map->world_map[y_m][x_m][z_m].x_off_set;
					int y_off = world_map->world_map[y_m][x_m][z_m].y_off_set;
					int z_off = world_map->world_map[y_m][x_m][z_m].z_off_set;

					std::cout << "x_off: " << x_off << std::endl;
					std::cout << "y_off: " << y_off << std::endl;
					std::cout << "z_off: " << z_off << std::endl;

					int y = 0;// input->ground_level;
					for (int x = 0; x < x_siz; x++) {
						for (int z = 0; z < z_siz; z++) {
							local_map[y][x][z].ground = spawner->spawn_item(STONE_WALL,
								x + x_off, y + y_off, z + z_off);
							local_map[y + 1][x][z].ground = spawner->spawn_item(GRASS_FLOOR,
								x + x_off, y + 1 + y_off, z + z_off);
						}
					}


				}
			}


		}

		output->world_map = world_map;
	}
	return output;
}

void world_generation::print_settings(world_gen_settings* settings) {
	std::cout << "world gen settings:" << std::endl;

	if (settings == NULL) {
		std::cout << "world gen settings was NULL" << std::endl;
		std::cout  << std::endl;
	}

	int total = settings->x_cell_size * settings->y_cell_size * settings->z_cell_size;
	std::cout << " x_cell_size: " << settings->x_cell_size << std::endl;
	std::cout << " y_cell_size: " << settings->y_cell_size << std::endl;
	std::cout << " z_cell_size: " << settings->z_cell_size << std::endl;
	std::cout << "total: " << total << std::endl;

	int cell_total = settings->x_cell_amount * settings->y_cell_amount * settings->z_cell_amount;
	std::cout << " x_cell_amount: " << settings->x_cell_amount << std::endl;
	std::cout << " y_cell_amount: " << settings->y_cell_amount << std::endl;
	std::cout << " z_cell_amount: " << settings->z_cell_amount << std::endl;
	std::cout << "total total: " << total* cell_total << std::endl;

	std::cout << " flat_land: " << settings->flat_land << std::endl;
	std::cout << " ground_level: " << settings->ground_level << std::endl;

	std::cout << std::endl;
}


world_gen_settings*  world_generation::flat_land_settings() {
	world_gen_settings* output = new world_gen_settings;

	//should be cubes in size for the best affect
	output->x_cell_size = 5;
	output->y_cell_size = 5;
	output->z_cell_size = 5;

	output->x_cell_amount = 10;
	output->y_cell_amount = 3;
	output->z_cell_amount = 10;

	output->flat_land = true;
	output->ground_level = 0;

	return output;
}


bool world_generation::is_settings_valid(world_gen_settings* test) {
	bool output = false;

	if (test != NULL) {


		 
		output = true;
	}

	return output;
}

void world_generation::create_blank_cell(map_data* world, world_gen_settings* settings, int x_index, int y_index, int z_index) {

	if (world == NULL) {
		return;
	}

	int x_siz = settings->x_cell_size;
	int y_siz = settings->y_cell_size;
	int z_siz = settings->z_cell_size;

	if (world->world_map == NULL) {
		return;
	}

	//needs to be the size of the cell and 
	//where the cell is on the map
	int x_offset = ((x_index)*x_siz);
	int y_offset = (y_index * y_siz);
	int z_offset = (z_index * z_siz);
	
	world->world_map[y_index][x_index][z_index].x_off_set = x_offset;
	world->world_map[y_index][x_index][z_index].y_off_set = y_offset;
	world->world_map[y_index][x_index][z_index].z_off_set = z_offset;

	world->world_map[y_index][x_index][z_index].x_size = x_siz;
	world->world_map[y_index][x_index][z_index].y_size = y_siz;
	world->world_map[y_index][x_index][z_index].z_size = z_siz;

	//create the map
	map_cell*** map = new map_cell * *[y_siz];
	for (int y = 0; y < y_siz; y++) {
		map[y] = new map_cell * [x_siz];
		for (int x = 0; x < x_siz; x++) {
			map[y][x] = new map_cell[z_siz];
		}
	}

	//create the indexing values
	for (int y = 0; y < y_siz; y++) {
		for (int x = 0; x < x_siz; x++) {
			for (int z = 0; z < z_siz; z++) {
				map[y][x][z].x = x;
				map[y][x][z].y = y;
				map[y][x][z].z = z;
			}
		}
	}

	//setting it to the map map
	world->world_map[y_index][x_index][z_index].map = map;
}


local_map_data* world_generation::create_blank_cell(int x_siz, int y_siz, int z_siz){

	local_map_data*	world_map = new local_map_data();

	world_map->x_size = x_siz;
	world_map->y_size = y_siz;
	world_map->z_size = z_siz;

	//create the map
	world_map->map = new map_cell * *[y_siz];
	for (int y = 0; y < y_siz; y++) {
		world_map->map[y] = new map_cell * [x_siz];
		for (int x = 0; x < x_siz; x++) {
			world_map->map[y][x] = new map_cell[z_siz];
		}
	}

	//create the indexing values
	for (int y = 0; y < y_siz; y++) {
		for (int x = 0; x < x_siz; x++) {
			for (int z = 0; z < z_siz; z++) {
				world_map->map[y][x][z].x = x;
				world_map->map[y][x][z].y = y;
				world_map->map[y][x][z].z = z;
			}
		}
	}

	return world_map;
}