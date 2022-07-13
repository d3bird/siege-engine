#pragma once

#include <unordered_map>
#include <vector>

#include "../../common_obj/location.h"
#include "../../core/motion_manager.h"

#include "crane.h"

class crane_manager {
	public:
	crane_manager(motion_manger* mm);
	~crane_manager();

	crane* create_crane(loc<int>location, int height, int radus);

	void update(double detlaTime);
	void toggle_crane(int id);

	crane* get_crane(int id);


	std::vector<loc<int> >  get_converate(int id, int y = 1);

	private:

		void create_rand_dest(crane* input);

		motion_manger* updater;

	//	std::unordered_map<loc<int>, crane> cranes;
		std::vector<crane*> cranes;
		int ID_max;
};