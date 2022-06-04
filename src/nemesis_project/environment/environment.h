#pragma once

#include "../core/optimized_spawner.h"
#include "../utility/motion_manager.h"

#include "../world/crane/crane_manager.h"



class environment
{
public:
	environment(optimized_spawner *os, motion_manger* mm);
	~environment();

	void update(double time_change);

	int place_crane(const loc<int>& location, int height, int radius);
	void toggle_crane(int id);
	crane* get_crane(int id);

private:

	crane_manager crane_mgr;

	optimized_spawner* spawner;
	motion_manger* updater;

};

