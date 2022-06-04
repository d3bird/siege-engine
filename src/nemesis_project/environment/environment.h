#pragma once

#include "../core/optimized_spawner.h"
#include "../utility/motion_manager.h"

#include "../world/crane/crane_manager.h"
#include "../world/rail/rail_manager.h"


class environment
{
public:
	environment(optimized_spawner *os, motion_manger* mm);
	~environment();

	void update(double time_change);

	//everything needed for the crane system
	int place_crane(const loc<int>& location, int height, int radius);
	void toggle_crane(int id);
	crane* get_crane(int id);


	//everything needd to run the rail system
	bool place_rail(loc<int>& location, bool x_axis, railRoad::rail_type aType);
	bool can_place_rail(loc<int>& location);
	int place_cart(loc<int>& location);//returns the id of the cart
	int can_place_cart(loc<int>& location);
	void toggle_cart(int id, double velocity);
	void prin_rail_info();

private:

	//engine related objects
	optimized_spawner* spawner;
	motion_manger* updater;

	//managers
	crane_manager crane_mgr;
	railRoad::rail_manager rail_mgr;


};

