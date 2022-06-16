#include "world_map.h"

#include <iostream>
#include <cmath>

map_data::map_data(){
	x_size = -1;
	y_size = -1;
	z_size = -1;
	world_map = NULL;
}

map_data::~map_data(){

}

bool map_data::has_been_inited() {
	return (x_size != -1 &&
		y_size != -1 &&
		z_size != -1 &&
world_map != NULL);

}


/*
* This function returns the which chunk, then the local cords for that chunck
* returns -1 if the funct fails
*/
std::pair < loc<int>, loc<int> > map_data::get_map_local_cords(const loc<int>& cords) {
	std::pair < loc<int>, loc<int> > output;

	//std::cout << "finding loc at these cords" << std::endl;
	//std::cout << cords.x << "," << cords.y << "," << cords.z << std::endl;

	if (world_map != NULL) {
		int chunk_x_size = world_map[0][0][0].x_size;
		int chunk_y_size = world_map[0][0][0].y_size;
		int chunk_z_size = world_map[0][0][0].z_size;

		int world_x_size = chunk_x_size * x_size;
		int world_y_size = chunk_y_size * y_size;
		int world_z_size = chunk_z_size * z_size;

		if (world_x_size <= 0 || world_y_size <= 0 || world_z_size <= 0 ||
			cords.x >= world_x_size || cords.y >= world_y_size || cords.z >= world_z_size) {
			std::cout << cords.x << "," << cords.y << "," << cords.z << std::endl;
			std::cout << "failed" << std::endl;
			return output;
		}
		else {
			//	std::cout << "finding local cords on world" << std::endl;

			//	std::cout << "chunk_x_size: " << chunk_x_size << std::endl;
			//	std::cout << "chunk_y_size: " << chunk_y_size << std::endl;
			//	std::cout << "chunk_z_size: " << chunk_z_size << std::endl;
			//	std::cout << std::endl;
			//	std::cout << "world_x_size: " << world_x_size << std::endl;
			//	std::cout << "world_y_size: " << world_y_size << std::endl;
			//	std::cout << "world_z_size: " << world_z_size << std::endl;

			output.first.x = (int)std::floor(cords.x / chunk_x_size);
			output.first.y = (int)std::floor(cords.y / chunk_y_size);
			output.first.z = (int)std::floor(cords.z / chunk_z_size);

			output.second.x = cords.x - (output.first.x * chunk_x_size);
			output.second.y = cords.y - (output.first.y * chunk_y_size);
			output.second.z = cords.z - (output.first.z * chunk_z_size);

			//	std::cout << "x chunk: " << output.first.x << std::endl;
			/*	std::cout << "y chunk: " << output.first.y << std::endl;
				std::cout << "z chunk: " << output.first.z << std::endl;
				std::cout << std::endl;
				std::cout << "x local: " << output.second.x << std::endl;
				std::cout << "y local: " << output.second.y << std::endl;
				std::cout << "z local: " << output.second.z << std::endl;*/
		}

	}

	return output;
}

bool map_data::can_place_ground_obj(const loc<int>& cords, bool requires_floor) {
	std::pair < loc<int>, loc<int> > temp = get_map_local_cords(cords);
	return can_place_ground_obj(temp.first, temp.second, requires_floor);
}

bool map_data::can_place_ground_obj(const loc<int>& chunk_cords, const loc<int>& local_cords, bool requires_floor) {

	if (world_map == NULL) {
		std::cout << " the world map was null" << std::endl;
		return false;
	}

	bool output = is_valid_locaL_cords(chunk_cords, local_cords);

	if (requires_floor) {
		output = output&& !is_cords_floor_NULL(chunk_cords, local_cords);
	}

	return output;
}

bool map_data::attach_obj(const loc<int>& cords, item_info* obj, bool floor, bool ground) {
	bool output = false;

	if (floor || ground) {

		std::pair < loc<int>, loc<int> > temp = get_map_local_cords(cords);
		output = is_valid_locaL_cords(temp.first, temp.second);
		if (output) {
			if (ground) {
				if (is_cords_ground_NULL(temp.first, temp.second)) {
					set_ground_obj(temp.first, temp.second, obj);
				}
			}
			if (floor) {
				if (is_cords_floor_NULL(temp.first, temp.second)) {
					set_floor_obj(temp.first, temp.second, obj);
				}
			}
		}
		else {
			std::cout << "not valid cords" << std::endl;
		}
	}

	return output;
}

item_info* map_data::replace_obj(const loc<int>& cords, item_info* obj, bool floor, bool ground){
	item_info* output = NULL;



	return output;
}

bool map_data::is_valid_chunck(const loc<int>& cords) {
	return ((cords.x >= 0 && cords.x < x_size) &&
		(cords.y >= 0 && cords.y < y_size) &&
		(cords.z >= 0 && cords.z < z_size));
}

bool map_data::is_valid_locaL_cords(const loc<int>& chunk_cords, const loc<int>& local_cords) {
	bool output = is_valid_chunck(chunk_cords);

	if (output) {
		output = world_map[chunk_cords.y][chunk_cords.x][chunk_cords.z].is_inbounds_of_map_local
		(local_cords.x, local_cords.y, local_cords.z);
	}

	return output;
}

bool map_data::is_cords_ground_NULL(const loc<int>& chunk_cords, const loc<int>& local_cords) {
	bool output = false;

	if(world_map[chunk_cords.y][chunk_cords.x][chunk_cords.z].
		map[local_cords.y][local_cords.x][local_cords.z].ground == NULL){
		output = true;
	}

	 return output;
 }

bool map_data::is_cords_floor_NULL(const loc<int>& chunk_cords, const loc<int>& local_cords) {
	bool output = false;

	if (world_map[chunk_cords.y][chunk_cords.x][chunk_cords.z].
		map[local_cords.y][local_cords.x][local_cords.z].floor == NULL) {
		output = true;
	}

	return output;
}

inline void map_data::set_floor_obj(const loc<int>& chunk_cords, const loc<int>& local_cords, item_info* obj) {
	world_map[chunk_cords.y][chunk_cords.x][chunk_cords.z].
		map[local_cords.y][local_cords.x][local_cords.z].floor = obj;
}

inline void map_data::set_ground_obj(const loc<int>& chunk_cords, const loc<int>& local_cords, item_info* obj) {
	world_map[chunk_cords.y][chunk_cords.x][chunk_cords.z].
		map[local_cords.y][local_cords.x][local_cords.z].floor = obj;
}