#pragma once 

#include "room.hpp"
#include "mobil_data.h"
#include "map_cell.h"

class local_map_data
{
public:
	local_map_data();
	~local_map_data();

	bool is_inbounds_of_map_local(int x, int y, int z, local_map_data* map);

	int x_size;
	int y_size;
	int z_size;
	map_cell*** map = NULL;// the local map

	bool generated_blank = false;

	bool mobil = false;
	wheels* Wheels = NULL;

	int ground_level = 0;

	bool merged_to_larger_map = false;
	int x_off_set = 0;
	int y_off_set = 0;
	int z_off_set = 0;

	std::vector< room*> rooms_on_map;

private:

};

