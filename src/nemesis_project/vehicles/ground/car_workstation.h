#pragma once

#include "../../common_obj/location.h"
#include <rendering/rendering_object_data.hpp>

#include "vehicle.h"

class car_workstation
{
public:
	car_workstation(int id);
	~car_workstation();

	void update(double time);

	rendering::item_info* lift;
	rendering::item_info* leaver;

	grnd_vehicle* mounted_vehicle;

	int get_ID() { return ID; }

	loc<double> location;

private:
	int ID;
	
	bool direction;
	double speed;

	//these vars determin the possition that the lift must move
	bool need_to_set_pos;
	double start_pos;
	double end_pos;
	double orginal;
};
