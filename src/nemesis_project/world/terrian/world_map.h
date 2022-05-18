#pragma once 

#include "local_map.h"

class map_data
{
public:
	map_data();
	~map_data();

	int x_size;
	int y_size;
	int z_size;

	local_map_data*** world_map = NULL;

	std::pair < loc<int>, loc<int> > get_map_local_cords(loc<int>& cords, map_data* map);

private:

};

