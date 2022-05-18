#include "local_map.h"

local_map_data::local_map_data(){

}

local_map_data::~local_map_data(){

}

bool local_map_data::is_inbounds_of_map_local(int x, int y, int z, local_map_data* map) {
	return (map != NULL &&
		x >= 0 && x < map->x_size&&
		y >= 0 && y < map->y_size&&
		z >= 0 && z < map->z_size);
}