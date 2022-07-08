#pragma once

#include <rendering/rendering_object_data.hpp>
#include "../../common_obj/location.h"

#include <vector>

class crane
{
public:
	crane();
	crane(int heigh, int radiu, loc<int>location, int id);
	~crane();

	int get_ID() { return ID; }

	int get_height() { return height; }
	int get_radius() { return radius; }

	loc<int> get_location() { return base_loc; }

	bool is_running() { return running; }
	bool is_aproaching_dest() { return aproaching_dest; }

	void set_running(bool run) { running = run; }
	void set_aproaching_dest(bool dest) { aproaching_dest = dest; }

	bool can_reach_dest(const loc<int>& aDest);
	bool set_dest(const loc<int>& aDest);
	loc<int> get_destination() { return dest; }

	void update(double detlaTime);

	void print_info();

	std::vector<rendering::item_info*> base;
	std::vector<rendering::item_info*> arm;

	rendering::item_info* attachment;

private:

	int ID;
	int height;
	int radius;

	bool running;
	bool aproaching_dest;

	loc<int>base_loc;
	loc<int>arm_loc;
	loc<int>attachment_loc;

	double attachment_rad_pos;
	float current_angle;
	float rot_speed;

	double attachment_move_speed;

	//destination information
	loc<int>dest;
	float destination_angle;
	double attachment_rad_pos_dest;

	//updating states
	bool update_arm;
	bool update_attach;
};