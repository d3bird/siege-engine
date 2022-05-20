#pragma once

#include <rendering/rendering_object_data.hpp>
#include "../../common_obj/location.h"

#include <vector>

class crane
{
public:
	crane(int heigh, int radiu);
	~crane();

	int get_height() { return height; }
	int get_radius() { return radius; }

	bool is_running() { return running; }
	bool is_aproaching_dest() { return aproaching_dest; }

	void set_running(bool run) { running = run; }

	void set_dest(loc<int> aDest) { dest = aDest; }


	struct crane_sect {
		item_info* obj;
		loc<double> end_loc;
		bool moving;
		float end_angle;
	};

	std::vector<item_info*> base;
	std::vector<crane_sect> arm;

private:

	int height;
	int radius;
	bool running;
	bool aproaching_dest;
	loc<int>dest;
};

