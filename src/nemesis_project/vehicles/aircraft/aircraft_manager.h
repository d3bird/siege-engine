#pragma once


#include "landing_spots/auto_pad.h"
#include "landing_spots/landing_site.h"
#include "landing_spots/landing_strip.h"

#include "flight_controller.h"
#include "route_planner.h"

#include <vector>
#include "../../common_obj/location.h"
#include "../../utility/motion_manager.h"


/*aircraft_manager
* This manager is the high level entry point to control the air vehicles
* it manages the aircraft enties and sends them to the flight controler to move through waypoints
* it also keeps track of the landing sites so it can tell the route planner to navigate between theses sites
*/

class aircraft_manager
{
public:
	aircraft_manager(motion_manger* mm);
	~aircraft_manager();

	void update(double time);

	//test the flight movement
	void testing_sim(std::vector<item_info*> working_models);

	int spawn_landing_pad(loc<int> location);
	int spawn_landing_strip(loc<int> location);
	int spawn_plane(int landing_pad);

	int spawn_drop_ship(loc<int> location);

	void send_craft_to_site(int plane, loc<int> location);
	void send_craft_to_land_site(int plane, int land_pad);

	//will send the plane to a obit around a point
	void send_craft_patrol(int plane, loc<int> location);

	//getters
	aircraft* get_aircraft(int id);
	drop_ship* get_drop_ship(int id);

	landing_site* get_landing_site(int id);
	landing_strip* get_landing_strip(int id);

private:

	motion_manger* updater;

	flight_controller FC;
	route_planner route_plan;

	std::vector<aircraft*> aircrafts;
	std::vector<drop_ship*> drop_ships;

	std::vector<landing_site*> landing_areas;
	std::vector<landing_strip*> landing_strips;
	
	std::vector<item_info*> sim_models;
	bool running_sim;

	int aircraft_id;
	int landing_id;
};
