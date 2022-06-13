#pragma once

#include "../common_obj/location.h"
#include <rendering/rendering_object_data.hpp>
#include "air_route.hpp"

class aircraft
{
public:
	aircraft(int id);
	~aircraft();

	int get_ID() { return ID; }

	loc<int> get_location() { return location; }
	void set_location(loc<int> alocation);

	bool operator==(const int& id);

	double get_move_speed(double distance, double angle_change_req);
	double get_move_speed_static() { return move_speed; }

	double get_angle_speed(double distance, double angle_change_req);
	double get_angle_speed_static() { return angle_speed; }

	void update_model_loc(const loc<double>& alocation, double aangle);
	void update_model_loc_from_saved();

	item_info* obj;
	route* current_route = NULL;

protected:
	loc<double> current_location;
	double angle;


private:
	int ID;
	loc<int> location;

	double move_speed;
	double angle_speed;
};
