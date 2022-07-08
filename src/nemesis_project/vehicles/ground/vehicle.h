#pragma once

#include "../../common_obj/location.h"
#include <rendering/rendering_object_data.hpp>

#include "../common/fuel.h"

class grnd_vehicle : public fuel
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
	rendering::item_info* body;

	//wheels
	rendering::item_info* BLW;
	rendering::item_info* BRW;
	rendering::item_info* FLW;
	rendering::item_info* FRW;

	//misc
	rendering::item_info* headlights;

private:
	loc<double> obj_cords;

};
