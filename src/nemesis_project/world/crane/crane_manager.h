#pragma once

#include <unordered_map>
#include <vector>

#include "../../common_obj/location.h"

#include "crane.h"

class crane_manager {
	public:
	crane_manager();
	~crane_manager();

	crane* create_crane(int height, int radus);

	void update(double detlaTime);
	void toggle_crane(int id);

	private:
	//	std::unordered_map<loc<int>, crane> cranes;
		std::vector<crane*> cranes;
		int ID_max;
};