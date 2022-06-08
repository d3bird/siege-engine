#pragma once

#include "aircraft.h"
#include "landing_site.h"
#include "flight_controller.h"

#include <vector>
#include "../common_obj/location.h"
#include "../utility/motion_manager.h"

class aircraft_manager
{
public:
	aircraft_manager(motion_manger* mm);
	~aircraft_manager();

	void update(double time);

	int spawn_landing_pad(loc<int> location);
	int spawn_plane(int landing_pad);

	void send_craft_to_site(int plane, loc<int> location);
	void send_craft_to_land_site(int plane, int land_pad);

	//will send the plane to a obit around a point
	void send_craft_patrol(int plane, loc<int> location);

	//getters
	aircraft* get_aircraft(int id);
	landing_site* get_landing_site(int id);

private:

	motion_manger* updater;

	flight_controller FC;

	std::vector<aircraft*> aircrafts;
	std::vector<landing_site*> landing_areas;

	int aircraft_id;
	int landing_id;
};
