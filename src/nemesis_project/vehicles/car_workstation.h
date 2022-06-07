#pragma once

#include "../common_obj/location.h"
#include <rendering/rendering_object_data.hpp>

class car_workstation
{
public:
	car_workstation(int id);
	~car_workstation();

	item_info* lift;
	item_info* leaver;

	int get_ID() { return ID; }

private:
	int ID;
};
