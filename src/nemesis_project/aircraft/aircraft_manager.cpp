#include "aircraft_manager.h"

#include <iostream>

aircraft_control::aircraft_control(optimized_spawner* objm) {
	OBJM = objm;
	factory = NULL;
	flight_brain = NULL;
}

aircraft_control::~aircraft_control() {

}

void aircraft_control::update() {
	flight_brain->update();

	update_models();
}

void aircraft_control::update_models() {

}


int aircraft_control::spawn_plane(loc spawn_loc, int plane_type) {
	
	plane_data* output = factory->spawn_plane(spawn_loc.x, spawn_loc.y, spawn_loc.z, plane_type);
	
	if (output == NULL) {
		std::cout << "failed to spawn plane" << std::endl;
		return -1;
	}
	
	int model_amount = 1;
	output->amount_models = model_amount;
	output->model_index = new int[model_amount];
	models_in_use.push_back(OBJM->spawn_item(AIRCRAFT_T, spawn_loc.x, spawn_loc.y, spawn_loc.z, 180));
	output->model_index[0] = models_in_use.size() - 1;
	
	
	planes.push_back(output);
	models_in_use.push_back(models_in_use[models_in_use.size() - 1]);
	return models_in_use.size()-1;
}

void aircraft_control::place_landing_site(loc location, bool flight_strip) {
landing_site* land = new landing_site;
	land->location_start = location;
	land->location_end = location;

	land->air_strip = flight_strip;

	land->inuse = false;
	land->plane_traveling_to = false;
	land->plane_need_service = false;

	land->plane = NULL;

	landing_sites.push_back(land);
	landing_sites_open.push_back(land);
}

void aircraft_control::init(int plane_enum) {

	place_landing_site(loc(0, 1, 0), false);
	place_landing_site(loc(10, 1, 10), false);

	factory = new aircraft_factory(plane_enum);	
	flight_brain = new flight_controller();

	spawn_plane(loc(0, 1, 0), 0);

	plane_data* plane = planes[0];

	//OBJM->spawn_item(AIRCRAFT_T, 0, 1, 0, 180);
	OBJM->spawn_item(AIRCRAFT_LANDING_PAD, 0, 1, 0);
	OBJM->spawn_item(AIRCRAFT_LANDING_PAD, 10, 1, 10);

	plane_route* testing = new plane_route;
	
	testing->starting_spot = landing_sites[0];
	testing->ending_spot = landing_sites[1];
	testing->patrol = false;


	bool valid = flight_brain->fly_plane(plane, testing);
	if (valid) {
		std::cout << "the plane is going to take off" << std::endl;
	}
}

std::vector<landing_site*>& aircraft_control::get_landing_sites() {
	return landing_sites;
}

std::vector<landing_site*>& aircraft_control::get_open_landing_sites() {
	return  landing_sites_open;
}

std::vector<landing_site*>& aircraft_control::get_filled_landing_sites() {
	return  landing_sites_closed;
}
