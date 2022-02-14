#pragma once

#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <vector>
#include <string>

#include "zones/zone.h"
#include "zones/farm_zone.h"

struct room;

struct additional_proporities {
	std::vector< item_info*> additional_items;
};

struct map_cell {
	int x;
	int y;
	int z;

	item_info* ground = NULL;//this is the main object in the square (could be a wall, table etc..)
	item_info* floor = NULL;

	bool gen_without_items = false;
	int ground_type = CUBE_T;
	int floor_type = CUBE_T;


	additional_proporities* props = NULL;

	zone* zone_on_top = NULL;

	map_cell* link_to_platform = NULL;

	bool inclosed = false;
	bool checked = false;
	bool failed_to_find_room = false;

	room* part_of_room = NULL;

	bool passibe() {
		if (ground != NULL) {
			switch (ground->type)
			{
			case LADDER_T:
				return true;
				break;
			default:
				return false;
				break;
			}
		}
		else {
			return floor != NULL;
		}
	}

};

struct room {
	std::string room_name;
	std::vector< map_cell*> cells_in_room;
};

struct wheel {
	int turn_speed = 1;
	bool pos_directio = true;

	int wheight_limit = 0;
	item_info* obj = NULL;
	item_info* wheel_block_link = NULL;
};

struct wheels {
	std::vector<wheel*> wheels;
	std::vector<item_info*> wheel_blocks;
};

struct map_data {
	int x_size;
	int y_size;
	int z_size;
	map_cell*** map= NULL;// the local map

	bool generated_blank = false;

	bool mobil = false;
	wheels* Wheels = NULL;

	int ground_level = 0;

	bool merged_to_larger_map = false;
	int x_off_set = 0;
	int y_off_set = 0;
	int z_off_set = 0;

	std::vector< room*> rooms_on_map;
};

static bool is_inbounds_of_map(int x, int y, int z, map_data* map) {
	return (map != NULL &&
		x >= 0 && x < map->x_size &&
		y >= 0 && y < map->y_size &&
		z >= 0 && z < map->z_size);
}

static void clear_checked(int layer, map_data* map) {
	int y = layer;

	if (map == NULL) {
		return;
	}

	int x_size = map->x_size;
	int z_size = map->z_size;
	for (int x = 0; x < x_size; x++) {
		for (int z = 0; z < z_size; z++) {
			map->map[y][x][z].checked = false;
		}
	}

}

static int max_room_size = 500;

static bool is_enclosed(int x, int y, int z, map_data* map) {

	if (map == NULL) {
		std::cout << "map is null" << std::endl;
		return false;
	}
	if (!is_inbounds_of_map(x,y,z,map)) {
		std::cout << "not in bounds" << std::endl;
		return false;
	}
	bool output = false;
	int cells_found = 0;

	map_cell*** world_map = map->map;

	std::vector< map_cell*> cells_in_room;
	std::vector< map_cell*> cells_to_check;
	std::vector< map_cell*> cells_checked;
	map_cell* test = &world_map[y][x][z];

	if (test->ground == NULL) {
		cells_to_check.push_back(test);
		test->checked = true;
	}
	else {
		std::cout << "can not be in a room since the starting point is on a wall" << std::endl;
		return false;
	}

	while (cells_found < max_room_size) {
		if (cells_to_check.empty()) {
			output = true;
			break;
		}
		test = cells_to_check[0];
		cells_checked.push_back(test);
		cells_to_check.erase(cells_to_check.begin());

		if (test != NULL) {

			if (test->ground == NULL) {
				cells_in_room.push_back(test);
				cells_found++;
				test->checked = true;
				int x_n = test->x;
				int y_n = test->y;
				int z_n = test->z;
				if (is_inbounds_of_map(x_n + 1, y_n, z_n, map) && !world_map[y_n][x_n + 1][z_n].checked) {
					cells_to_check.push_back(&world_map[y_n][x_n + 1][z_n]);
					world_map[y_n][x_n + 1][z_n].checked = true;
				}
				if (is_inbounds_of_map(x_n - 1, y_n, z_n, map) && !world_map[y_n][x_n - 1][z_n].checked) {
					cells_to_check.push_back(&world_map[y_n][x_n - 1][z_n]);
					world_map[y_n][x_n - 1][z_n].checked = true;
				}
				if (is_inbounds_of_map(x_n, y_n, z_n + 1, map) && !world_map[y_n][x_n][z_n + 1].checked) {
					cells_to_check.push_back(&world_map[y_n][x_n][z_n + 1]);
					world_map[y_n][x_n][z_n + 1].checked = true;
				}
				if (is_inbounds_of_map(x_n, y_n, z_n - 1, map) && !world_map[y_n][x_n][z_n - 1].checked) {
					cells_to_check.push_back(&world_map[y_n][x_n][z_n - 1]);
					world_map[y_n][x_n][z_n - 1].checked = true;
				}
			}
		}
	}

	if (output) {
		std::cout << "found " << cells_in_room.size() << " in room" << std::endl;
	}
	/*	for (int i = 0; i < cells_in_room.size(); i++) {
			int x = cells_in_room[i]->x;
			int y = cells_in_room[i]->y;
			int z = cells_in_room[i]->z;

			std::cout << x << "," << y << "," << z << " is in the room" << std::endl;
		}*/

	clear_checked(y, map);

	return output;
}

//generates a 2d room
static room* generate_room(int x, int y, int z, map_data* map) {

	if (map == NULL) {
		std::cout << "map is null" << std::endl;
		return NULL;
	}
	if (!is_inbounds_of_map(x, y, z, map)) {
		std::cout << "not in bounds" << std::endl;
		return NULL;
	}
	bool output;

	int cells_found = 0;

	map_cell*** world_map = map->map;

	std::vector< map_cell*> cells_in_room;
	std::vector< map_cell*> cells_to_check;
	std::vector< map_cell*> cells_checked;
	map_cell* test = &world_map[y][x][z];

	if (test->ground == NULL) {
		cells_to_check.push_back(test);
		test->checked = true;
	}
	else {
		//std::cout << "can not be in a room since the starting point is on a wall" << std::endl;
		return false;
	}

	while (cells_found < max_room_size) {
		if (cells_to_check.empty()) {
			output = true;
			break;
		}
		test = cells_to_check[0];
		cells_checked.push_back(test);
		cells_to_check.erase(cells_to_check.begin());

		if (test != NULL) {

			if (test->ground == NULL) {
				cells_in_room.push_back(test);
				cells_found++;
				test->checked = true;
				int x_n = test->x;
				int y_n = test->y;
				int z_n = test->z;
				if (is_inbounds_of_map(x_n + 1, y_n, z_n, map) && !world_map[y_n][x_n + 1][z_n].checked) {
					cells_to_check.push_back(&world_map[y_n][x_n + 1][z_n]);
					world_map[y_n][x_n + 1][z_n].checked = true;
				}
				
				if (is_inbounds_of_map(x_n - 1, y_n, z_n, map) && !world_map[y_n][x_n - 1][z_n].checked) {
					cells_to_check.push_back(&world_map[y_n][x_n - 1][z_n]);
					world_map[y_n][x_n - 1][z_n].checked = true;
				}
			
				if (is_inbounds_of_map(x_n, y_n, z_n + 1, map) && !world_map[y_n][x_n][z_n + 1].checked) {
					cells_to_check.push_back(&world_map[y_n][x_n][z_n + 1]);
					world_map[y_n][x_n][z_n + 1].checked = true;
				}
				
				if (is_inbounds_of_map(x_n, y_n, z_n - 1, map) && !world_map[y_n][x_n][z_n - 1].checked) {
					cells_to_check.push_back(&world_map[y_n][x_n][z_n - 1]);
					world_map[y_n][x_n][z_n - 1].checked = true;
				}
				
			}
		}
	}
	room* output_room = NULL;
	
	if (output) {
		output_room = new room;;
		std::cout << "found " << cells_in_room.size() << " in room" << std::endl;
		output_room->room_name = "room_name";
		output_room->cells_in_room = cells_in_room;
		//mark cells as part of room
		for (int i = 0; i < cells_in_room.size(); i++) {
			cells_in_room[i]->part_of_room = output_room;
		}
	}
	clear_checked(y, map);
	return output_room;
}

static map_data* merge_maps(map_data* larger, map_data* smaller) {

	return NULL;
}


static void delete_map_data(map_data* in) {
	if (in == NULL) {
		return;
	}

	//checks to makesure that the map was compleatly deleted
	if (in->map != NULL) {
		int count = 0;
		for (int y = 0; y < in->y_size; y++) {
			for (int x = 0; x < in->x_size; x++) {
				for (int z = 0; z < in->z_size; z++) {
					if (in->map[y][x][z].ground != NULL) {
						count++;
					}
					if (in->map[y][x][z].floor != NULL) {
						count++;
					}
				}
			}
		}
		if (count != 0) {
			std::cout << "WARRNING: " << count << " objs where not delete ahead of time" << std::endl;
		}
	}

	//delete the wheels
	if (in->Wheels != NULL) {
		
	}

	//delete the rooms
	if (in->rooms_on_map.size() >0) {

	}

}