#pragma once

#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <vector>
#include <string>

#include "terrian/mobil_data.h"
#include "terrian/map_cell.h"
#include "terrian/local_map.h"
#include "terrian/world_map.h"
#include "terrian/terrian_analyzer.h"


static void clear_checked(int layer, local_map_data* map) {
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

static bool is_enclosed(int x, int y, int z, local_map_data* map) {

	if (map == NULL) {
		std::cout << "map is null" << std::endl;
		return false;
	}
	if (!map->is_inbounds_of_map_local(x,y,z,map)) {
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
				if (map->is_inbounds_of_map_local(x_n + 1, y_n, z_n, map) && !world_map[y_n][x_n + 1][z_n].checked) {
					cells_to_check.push_back(&world_map[y_n][x_n + 1][z_n]);
					world_map[y_n][x_n + 1][z_n].checked = true;
				}
				if (map->is_inbounds_of_map_local(x_n - 1, y_n, z_n, map) && !world_map[y_n][x_n - 1][z_n].checked) {
					cells_to_check.push_back(&world_map[y_n][x_n - 1][z_n]);
					world_map[y_n][x_n - 1][z_n].checked = true;
				}
				if (map->is_inbounds_of_map_local(x_n, y_n, z_n + 1, map) && !world_map[y_n][x_n][z_n + 1].checked) {
					cells_to_check.push_back(&world_map[y_n][x_n][z_n + 1]);
					world_map[y_n][x_n][z_n + 1].checked = true;
				}
				if (map->is_inbounds_of_map_local(x_n, y_n, z_n - 1, map) && !world_map[y_n][x_n][z_n - 1].checked) {
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
static room* generate_room(int x, int y, int z, local_map_data* map) {

	if (map == NULL) {
		std::cout << "map is null" << std::endl;
		return NULL;
	}
	if (!map->is_inbounds_of_map_local(x, y, z, map)) {
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
				if (map->is_inbounds_of_map_local(x_n + 1, y_n, z_n, map) && !world_map[y_n][x_n + 1][z_n].checked) {
					cells_to_check.push_back(&world_map[y_n][x_n + 1][z_n]);
					world_map[y_n][x_n + 1][z_n].checked = true;
				}
				
				if (map->is_inbounds_of_map_local(x_n - 1, y_n, z_n, map) && !world_map[y_n][x_n - 1][z_n].checked) {
					cells_to_check.push_back(&world_map[y_n][x_n - 1][z_n]);
					world_map[y_n][x_n - 1][z_n].checked = true;
				}
			
				if (map->is_inbounds_of_map_local(x_n, y_n, z_n + 1, map) && !world_map[y_n][x_n][z_n + 1].checked) {
					cells_to_check.push_back(&world_map[y_n][x_n][z_n + 1]);
					world_map[y_n][x_n][z_n + 1].checked = true;
				}
				
				if (map->is_inbounds_of_map_local(x_n, y_n, z_n - 1, map) && !world_map[y_n][x_n][z_n - 1].checked) {
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

static local_map_data* merge_maps(local_map_data* larger, local_map_data* smaller) {

	return NULL;
}


static void delete_map_data(local_map_data* in) {
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
