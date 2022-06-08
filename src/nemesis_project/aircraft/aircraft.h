#pragma once

#include "../common_obj/location.h"
#include <rendering/rendering_object_data.hpp>

class aircraft
{
public:
	aircraft(int id);
	~aircraft();

	bool operator==(const int& id);

	void set_location(const loc<int>& loca) { location = loca; }

	int get_ID() { return ID; }
	loc<int> get_location() { return location; }

	item_info* obj;

private:
	int ID;
	loc<int> location;
};
