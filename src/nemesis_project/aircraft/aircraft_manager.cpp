#include "aircraft_manager.h"

#include <iostream>

aircraft_manager::aircraft_manager(motion_manger*mm) {
	aircraft_id = 0;
	landing_id = 0;
	updater = mm;
}

aircraft_manager::~aircraft_manager() {

}

void aircraft_manager::update(double time) {

}

int aircraft_manager::spawn_landing_pad(loc<int> location) {
	landing_site* temp = new landing_site(landing_id);
	temp->set_location(location);
	landing_id++;
	landing_areas.push_back(temp);
	return temp->get_ID();
}

int aircraft_manager::spawn_plane(int landing_pad) {
	landing_site* site = get_landing_site(landing_pad);

	if (site == NULL) {
		std::cout << "can not spawn plane here, pad is NULL" << std::endl;
		return -1;
	}
	loc<int> location = site->get_location();

	aircraft* temp = new aircraft(aircraft_id);
	temp->set_location(location);
	aircraft_id++;
	aircrafts.push_back(temp);
	return temp->get_ID();
}

void aircraft_manager::send_craft_to_site(int plane, loc<int> location) {

}

void aircraft_manager::send_craft_to_land_site(int plane, int land_pad) {

}

aircraft* aircraft_manager::get_aircraft(int id) {
	aircraft* output = NULL;

	for (size_t i = 0; i < aircrafts.size(); i++)
	{
		if (aircrafts[i]->get_ID() == id) {
			output = aircrafts[i];
			break;
		}
	}

	return output;
}
landing_site* aircraft_manager::get_landing_site(int id) {
	landing_site* output = NULL;
//	std::cout << "looking for pad: " <<id<< std::endl;
	for (size_t i = 0; i < landing_areas.size(); i++)
	{
		//std::cout << "pad: " << landing_areas[i]->get_ID() << std::endl;
		if (landing_areas[i]->get_ID() == id) {
		//	std::cout << "found the pad" << std::endl;
			output = landing_areas[i];
			break;
		}
	}

	return output;
}