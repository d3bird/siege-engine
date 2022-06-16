#pragma once

#include "../../../common_obj/location.h"
#include "../air_route.hpp"
#include <rendering/rendering_object_data.hpp>

class drop_ship {
public:
	drop_ship(int id);
	~drop_ship();

	//updates the model location and the doors moving
	void update_models(loc<double> aLocation, double time);
	void update_models(double time);

	void set_location(loc<int> aLocation);
	void set_location(loc<double> aLocation);

	int get_ID() { return ID; }

	void open_doors();
	void close_doors();
	bool are_doors_open();

	double get_move_speed();
	double get_turn_speed();

	void start_landing_procedures();
	void start_take_off_procedures();

	bool operator==(const int id);

	item_info* body;
	item_info* engines;
	item_info* left_doors;
	item_info* right_doors;

	route* current_route;

private:

	void update_models(bool just_doors);

	loc<double> location;
	double turn_speed;
	double move_speed;
	int ID;

	bool doors_opening;
	bool doors_closing;
	bool doors_open;
	bool doors_closed;

	double door_move_speed;
	double door_offset;
	double current_off;

	bool parked;
	bool unloading;

	bool getting_ready_take_off;
	bool getting_ready_park;
	bool ready_to_take_off;
};