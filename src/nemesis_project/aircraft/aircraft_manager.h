#pragma once

#include "aircraft_factory.h"
#include "flight_controller.h"

#include "plane_route.hpp"

#include "../core/optimized_spawner.h"

class aircraft_manager
{
public:
	aircraft_manager(optimized_spawner * objm);
	~aircraft_manager();

	void update();

	int spawn_plane(loc_i<int> spawn_loc, int plane_type);

	void place_landing_site(loc_i<int> location, bool flight_strip);

	std::vector<landing_site*>& get_landing_sites();
	std::vector<landing_site*>& get_open_landing_sites();
	std::vector<landing_site*>& get_filled_landing_sites();
	
	void init(int plane_enum);

	void start_animation_sim( const loc_i<int> &start_loc);

private:

	void update_models();

	optimized_spawner* OBJM;
	aircraft_factory* factory;
	flight_controller* flight_brain;

	std::vector< landing_site*> landing_sites;
	std::vector< landing_site*> landing_sites_open;
	std::vector< landing_site*> landing_sites_closed;

	std::vector<item_info*> models_in_use;

	std::vector<plane_data*> planes;
};

