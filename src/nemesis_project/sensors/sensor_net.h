#pragma once

#include <vector>

#include "sensors/sensor_data.hpp"
#include "tracks/track_manager.h"


class sensor_net
{
public:
	sensor_net();
	~sensor_net();

	void place_radar(int x, int y, int z);
	void place_radio_tower(int x, int y, int z);
	void place_cable(int x, int y, int z);

	bool in_range_of_radar(int x, int y, int z);

	std::vector< radar*> radars;
	std::vector< radio*> radios;

private:


	sensor_base* create_sensor_base();
};

