#pragma once

#include "../common_obj/location.h"
#include <rendering/rendering_object_data.hpp>
#include "air_route.hpp"

class aircraft
{
public:
	aircraft(int id);
	~aircraft();

	bool operator==(const int& id);

	int get_ID() { return ID; }
	loc<int> get_location() { return location; }
	void set_location(loc<int> alocation);

	item_info* obj;
	route* current_route;

private:
	int ID;
	loc<int> location;
};
