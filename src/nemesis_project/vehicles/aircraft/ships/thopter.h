#pragma once

#include "../../../common_obj/location.h"
#include "../air_route.hpp"
#include <rendering/rendering_object_data.hpp>

#include "../../common/fuel.h"

class thopter: public fuel
{
public:
	thopter(int id);
	~thopter();

	void update(double time);

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

	void start_landing_animation();
	void start_take_off_animation();

	void start_flying();

	bool is_landing();
	bool is_taking_off();
	bool is_flying();

	rendering::item_info* base;
	rendering::item_info* fl_wing;
	rendering::item_info* fr_wing;
	rendering::item_info* bl_wing;
	rendering::item_info* br_wing;

	route* current_route = NULL;

protected:

	loc<double> current_location;
	rendering::rotation angle;

	bool landing;
	bool taking_off;
	bool flying = true;;

	rendering::rotation fl_wing_angle;
	bool fl_pos_dir;
	float fly_diff = 40;
	rendering::rotation fr_wing_angle;
	bool fr_pos_dir = 220;
	rendering::rotation bl_wing_angle;
	bool bl_pos_dir = 40;
	rendering::rotation br_wing_angle;
	bool br_pos_dir = 220;

	void calc_wing_possition(double time);

	void set_wing_location();

private:
	int ID;
	loc<int> location;

	double move_speed;
	double angle_speed;
	double wing_speed;
};
