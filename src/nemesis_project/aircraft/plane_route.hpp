#pragma once

#include "../common_obj/location.hpp"
#include "aircraft_data.hpp"

#include <vector>

struct landing_site {
	loc<int> location_start;

	bool air_strip;
	loc<int> location_end;

	bool inuse;
	bool plane_traveling_to;
	bool plane_need_service;

	plane_data* plane;

};

struct plane_route {
	landing_site* starting_spot;
	landing_site* ending_spot;

	std::vector<loc<int> > points;

	bool patrol;

	plane_data* plane = NULL;

};