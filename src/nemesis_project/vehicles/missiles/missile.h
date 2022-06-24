#pragma once

#include "../../common_obj/location.h"
#include <rendering/rendering_object_data.hpp>

#include "../common/fuel.h"

class missile : public fuel
{
public:
	missile(int id, loc<int> aLocation);
	~missile();

	enum flight_state { TAKE_OFF, ANGLE_TOWARD, HOMING, FULL_SPEED };

	void fire(const loc<double>& atarget);
	bool is_fired();

	void explode();

	double get_velocity();
	double get_angle_changle();

	void set_fly_state(flight_state new_state);

	void set_grid_location(const loc<int>& alocation);
	void update_model_location(const loc<double>& alocation, double angle = 0);

	void update_model_info();

	loc<int> get_start_location() { return location; }
	loc<double> get_location() { return actual_location; }
	int get_ID() { return ID; }

	item_info* model;

private:
	int ID;
	loc<int> location;
	loc<double> actual_location;

	loc<double> target;
	bool target_set;
	bool fired;

	flight_state state;

	double acceleration;
	double velocity;
	double max_velocity;

	double angle_change;
	double horizontal_angle;


};
