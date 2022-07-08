#pragma once

#include "../../../common_obj/location.h"
#include <rendering/rendering_object_data.hpp>

class landing_strip
{
public:
	landing_strip(int id);
	~landing_strip();

	void set_location(const loc<int>& loca) { location = loca; }

	bool operator==(const int& id);
	int get_ID() { return ID; }

	loc<int> get_location() { return location; }

	rendering::item_info* obj;

private:
	int ID;
	loc<int> location;

};
