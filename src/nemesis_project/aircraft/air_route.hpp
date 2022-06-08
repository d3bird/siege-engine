#pragma once

#include "../common_obj/location.h"
#include <vector>

struct route {

	std::vector<loc<double> > waypoints;
	std::vector<loc<double> > starting_waypoints;
	bool repeat;
	loc<double> start_loc;
	loc<int> orbit_loc;
	int index = 0;
};