#pragma once

#include "aircraft.h"
#include "air_route.hpp"
#include "../utility/motion_manager.h"

#include <vector>

class flight_controller
{
public:
	flight_controller(motion_manger* mm);
	~flight_controller();

	void update(double time);

	void send_craft_patrol(aircraft* plane, loc<int> location);


private:
	std::vector<aircraft*> planes;
	motion_manger* updater;

	void create_orbit_patrol(aircraft* plane);
	bool orbit_check(const loc<int>& aDest, const loc<int>& aCenter, int radius);


};

