#pragma once

#include "../../../common_obj/location.h"
#include "../air_route.hpp"
#include <rendering/rendering_object_data.hpp>

#include "../../common/fuel.h"

class aircraft: public fuel
{
public:
	aircraft(int id);
	~aircraft();

	int get_ID();

	loc<int> get_location();
	void set_location(loc<int> alocation);

	bool operator==(const int& id);

	double get_move_speed(double distance, double angle_change_req);
	double get_move_speed_static();

	double get_angle_speed(double distance, double angle_change_req);
	double get_angle_speed_static();

	void update_model_loc(const loc<double>& alocation,const rendering::rotation &aangle);
	void update_model_loc_from_saved();

	rendering::item_info* obj;
	route* current_route = NULL;

protected:
	loc<double> current_location;
	rendering::rotation angle;

private:
	int ID;
	loc<int> location;

	double move_speed;
	double angle_speed;
};
