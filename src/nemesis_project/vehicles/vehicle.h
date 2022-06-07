#pragma once

#include "../common_obj/location.h"
#include <rendering/rendering_object_data.hpp>

class grnd_vehicle
{
public:
	grnd_vehicle(const loc<double>& location);
	grnd_vehicle(const loc<int>& location);
	~grnd_vehicle();

	//updates the object cords
	void update(const loc<double>& new_location, bool mult = true);

	void set_current_loc() { update(obj_cords); }

	loc<double> get_obj_cords() { return  obj_cords; }

	//body
	item_info* body;

	//wheels
	item_info* BLW;
	item_info* BRW;
	item_info* FLW;
	item_info* FRW;

	//misc
	item_info* headlights;

private:
	loc<double> obj_cords;

};
