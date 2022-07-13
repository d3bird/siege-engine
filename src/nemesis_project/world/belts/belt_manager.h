#pragma once

#include "../../core/motion_manager.h"
#include "belt.h"

#include <vector>

class belt_manager
{
public:
	belt_manager(motion_manger* mm);
	~belt_manager();

	void update(double deltaTime);

	//first return is the spawned and second is the affected
	std::pair<int, int> spawn_belt(loc<int> location, int out_dir);
	int get_num_connections(int ID);
	rendering::item_info* replace_obj(int ID, rendering::item_info* new_obj);

	//for clean up
	std::vector<rendering::item_info*> get_all_objs();

private:
	motion_manger* updater;

	int ID_num;
	std::vector<belt*> belts_update;
};

