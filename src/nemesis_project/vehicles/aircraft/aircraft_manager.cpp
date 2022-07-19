#include "aircraft_manager.h"

#include <iostream>

aircraft_manager::aircraft_manager(motion_manger*mm):FC(mm) {
	aircraft_id = 0;
	landing_id = 0;
	updater = mm;
}

aircraft_manager::~aircraft_manager() {

}

void aircraft_manager::update(double time) {
	FC.update(time);

	for (int i = 0; i < drop_ships.size(); i++) {

		//test code to make sure the door animation works

		if (drop_ships[i]->are_doors_open()) {
			drop_ships[i]->close_doors();
		}
		else {
			drop_ships[i]->open_doors();
		}

		//update just the doors
		drop_ships[i]->update_models(time);
		updater->update_item(drop_ships[i]->left_doors);
		updater->update_item(drop_ships[i]->right_doors);
	}
}

int aircraft_manager::spawn_landing_pad(loc<int> location) {
	landing_site* temp = new landing_site(landing_id);
	temp->set_location(location);
	landing_id++;
	landing_areas.push_back(temp);
	return temp->get_ID();
}

int aircraft_manager::spawn_landing_strip(loc<int> location) {
	landing_strip* temp = new landing_strip(landing_id);
	temp->set_location(location);
	landing_id++;
	landing_strips.push_back(temp);
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

int aircraft_manager::spawn_drop_ship(loc<int> location) {
	drop_ship * temp = new drop_ship(aircraft_id);
	temp->set_location(location);
	aircraft_id++;
	drop_ships.push_back(temp);
	return temp->get_ID();
}

int aircraft_manager::spawn_thopter(loc<int> location) {
	thopter* temp = new thopter(aircraft_id);
	temp->set_location(location);
	aircraft_id++;
	thopters.push_back(temp);
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

drop_ship* aircraft_manager::get_drop_ship(int id) {
	drop_ship* output = NULL;

	for (size_t i = 0; i < drop_ships.size(); i++)
	{
		if (drop_ships[i]->get_ID() == id) {
			output = drop_ships[i];
			break;
		}
	}

	return output;
}

thopter* aircraft_manager::get_thopter(int id) {
	thopter* output = NULL;

	for (size_t i = 0; i < thopters.size(); i++)
	{
		if (thopters[i]->get_ID() == id) {
			output = thopters[i];
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

landing_strip* aircraft_manager::get_landing_strip(int id) {
	landing_strip* output = NULL;
	//	std::cout << "looking for pad: " <<id<< std::endl;
	for (size_t i = 0; i < landing_strips.size(); i++)
	{
		//std::cout << "pad: " << landing_areas[i]->get_ID() << std::endl;
		if (landing_strips[i]->get_ID() == id) {
			//	std::cout << "found the pad" << std::endl;
			output = landing_strips[i];
			break;
		}
	}

	return output;
}

void aircraft_manager::send_craft_patrol(int plane, loc<int> location) {
	aircraft* temp = get_aircraft(plane);
	if (temp != NULL) {
		FC.send_craft_patrol(temp, location);
	}
	else {
		std::cout << "can not create patrol, plane NULL" << std::endl;
	}
}

void aircraft_manager::testing_sim(std::vector<rendering::item_info*> working_models) {
	sim_models = working_models;

	if (sim_models.size() > 0) {
		aircraft* temp = new aircraft(aircraft_id);
		temp->obj = sim_models[0];
		aircraft_id++;

		aircraft* temp2 = new aircraft(aircraft_id);
		temp2->obj = sim_models[1];
		aircraft_id++;

		std::cout << "working_models " << working_models.size() << std::endl;
		std::cout << "sim_models " << sim_models.size() << std::endl;
		sim_models.erase(sim_models.begin());
		sim_models.erase(sim_models.begin());
		//route_plan.active_sim(temp, sim_models.size());
		FC.start_sim(temp, temp2, sim_models);
	}
}
