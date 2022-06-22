#pragma once

#include "../../common_obj/location.h"
#include <rendering/rendering_object_data.hpp>

class missile
{
public:
	missile(int id, loc<int> aLocation);
	~missile();

	loc<int> get_location() { return location; }
	int get_ID() { return ID; }

	item_info* model;

private:
	int ID;
	loc<int> location;

};
