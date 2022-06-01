#pragma once

#include <unordered_map>
#include <vector>

#include "../../common_obj/location.h"
#include "../../utility/motion_manager.h"

#include "crane.h"

class crane_manager {
	public:
	crane_manager(motion_manger* mm);
	~crane_manager();

	crane* create_crane(loc<int>location, int height, int radus);

	void update(double detlaTime);
	void toggle_crane(int id);

	private:
		motion_manger* updater;

	//	std::unordered_map<loc<int>, crane> cranes;
		std::vector<crane*> cranes;
		int ID_max;
};