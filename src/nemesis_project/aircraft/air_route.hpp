#pragma once

#include "../common_obj/location.h"
#include <vector>

struct route {

	std::vector<loc<double> > waypoints;
	std::vector<loc<double> > starting_waypoints;

	bool repeat = true;
	bool done = false;
	bool found_angle = false;
	bool has_point_moved = false;

	loc<double> start_loc;
	loc<int> orbit_loc;
	int index = 0;

	void increment_index() {
		index++;
		if (index >= waypoints.size()) {
			index = 0;
			if (!repeat) {
				done = true;
			}
		}
	}

	loc<double> get_current_waypoint() {
		return waypoints[index];
	}

};