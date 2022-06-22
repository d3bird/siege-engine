#pragma once

#include "../../common_obj/location.h"
#include <rendering/rendering_object_data.hpp>

#include "missile.h"

class launcher
{
public:
	launcher(int id, loc<int> aLocation);
	~launcher();

	void update_missile_model();

	loc<int> get_location() { return location; }
	int get_ID() { return ID; }

	item_info* model;

	missile* slotted_missile;
private:
	int ID;
	loc<int> location;
};
