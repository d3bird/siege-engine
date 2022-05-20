#pragma once

#include <rendering/rendering_object_data.hpp>
#include "../../common_obj/location.h"

#include <vector>

class crane
{
public:
	crane();
	crane(int heigh, int radiu, int id);
	~crane();


	int get_ID() { return ID; }

	int get_height() { return height; }
	int get_radius() { return radius; }

	bool is_running() { return running; }
	bool is_aproaching_dest() { return aproaching_dest; }

	void set_running(bool run) { running = run; }

	void set_dest(const loc<int>& aDest);
	loc<int> get_destination() { return dest; }

	void update(double detlaTime);

	void print_info();

	struct crane_sect {
		item_info* obj = NULL;
		loc<double> end_loc;
		loc<double> current_loc;
		bool moving = false;
		float end_angle = 0;
	};

	std::vector<item_info*> base;
	std::vector<crane_sect> arm;

private:

	int ID;
	int height;
	int radius;
	bool running;
	bool aproaching_dest;
	loc<int>dest;
};