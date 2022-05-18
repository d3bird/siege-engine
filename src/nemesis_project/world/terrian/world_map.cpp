#include "world_map.h"

#include <iostream>
#include <cmath>

map_data::map_data(){

}

map_data::~map_data(){

}

/*
* This function returns the which chunk, then the local cords for that chunck
* returns -1 if the funct fails
*/
 std::pair < loc<int>, loc<int> > map_data::get_map_local_cords(loc<int>& cords, map_data* map) {
	std::pair < loc<int>, loc<int> > output;

	//std::cout << "finding loc at these cords" << std::endl;
	//std::cout << cords.x << "," << cords.y << "," << cords.z << std::endl;

	if (map->world_map != NULL) {
		int chunk_x_size = map->world_map[0][0][0].x_size;
		int chunk_y_size = map->world_map[0][0][0].y_size;
		int chunk_z_size = map->world_map[0][0][0].z_size;

		int world_x_size = chunk_x_size * map->x_size;
		int world_y_size = chunk_y_size * map->y_size;
		int world_z_size = chunk_z_size * map->z_size;

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