#include "environment.h"

environment::environment(optimized_spawner* os, motion_manger* mm):
	crane_mgr(mm), rail_mgr(mm), vehicle_mgr(mm), aircraft_mgr(mm),
	decor_manager(mm) {
	spawner = os;
	updater = mm;
	world_map = NULL;
}

environment::~environment(){

}

void environment::update(double time_change) {
	crane_mgr.update(time_change);
	rail_mgr.update(time_change);
	furnace_mgr.update(time_change);
	vehicle_mgr.update(time_change);
	aircraft_mgr.update(time_change);
	decor_manager.update(time_change);
}

bool environment::place_rail(loc<int>& location, bool x_axis, railRoad::rail_type aType) {
	bool output = can_place_rail(location);

	if (output) {
		item_info* temp = NULL;

		switch (aType)
		{
		case railRoad::CURVE:
			temp = spawner->spawn_item(CURVE_RAIL, location.x, location.y, location.z);

			break;
		case railRoad::STRAIGHT:
			temp = spawner->spawn_item(RAIL, location.x, location.y, location.z);
			break;
		case railRoad::SLANT:
			temp = spawner->spawn_item(SLANT_RAIL, location.x, location.y, location.z);
			break;
		default:
			std::cout << "there is no model for this rail" << std::endl;
			break;
		}

		if (temp == NULL) {
			return false;
		}

		if (!x_axis) {
			temp->angle = 90;
			updater->update_item(temp);
		}

		if (!world_map->attach_obj(location, temp, false, true)) {
			std::cout << "failed to attach rail to world map" << std::endl;
		}

		rail_mgr.add_rail(location, x_axis, aType);
	}
	return output;
}

bool environment::can_place_rail(loc<int>& location) {
	bool output = false;
	return true;
	if (world_map != NULL) {

		output = world_map->can_place_ground_obj(location, true);

	}
	return output;
}


int environment::place_cart(loc<int>& location) {
	int rail_state = can_place_cart(location);
	bool placable;

	switch (rail_state)
	{
	case 1:
	case 2:
		placable = true;
		break;
	case 0:
	default:
		placable = false;
		break;
	}

	int output = -1;
	if (placable) {
		output = rail_mgr.place_cart(location);

		if (output != -1) {

			item_info* temp = spawner->spawn_item(CART, location.x, location.y, location.z);

			//the rail is facing another direction
			if (rail_state == 2) {
				temp->angle = 90;
				updater->update_item(temp);
			}

			//yes I know that this is not the best, but it can be optimised latter
			for (int i = 0; i < rail_mgr.carts.size(); i++) {
				if (rail_mgr.carts[i] == output) {
					rail_mgr.carts[i].cart_obj = temp;
					std::cout << "linked the obj with the cart" << std::endl;
					break;
				}
			}
		}
		else {
			std::cout << "railroad mgr failed to create a cart object" << std::endl;
		}
	}
	else {
		std::cout << "fail to place cart" << std::endl;
	}
	return output;
}

int environment::can_place_cart(loc<int>& location) {
	return rail_mgr.can_place_cart(location);
}

void environment::toggle_cart(int id, double velocity) {
	rail_mgr.set_cart_vel(id, velocity);
	rail_mgr.toggle_cart(id);
}

void environment::prin_rail_info() {
	rail_mgr.print_info();
}

int environment::place_crane(const loc<int>& location, int height, int radius) {
	int output = -1;
	item_info* temp = 0;

	std::cout << "creating crane" << std::endl;

	std::cout << height << " , " << radius << std::endl;

	crane* new_crane = crane_mgr.create_crane(location, height, radius);
	if (new_crane == NULL) {
		std::cout << "failed creating crane" << std::endl;
		return output;
	}

	//make the central pillar
	for (int i = 0; i < height; i++) {
		temp = spawner->spawn_item(CRANE_B, location.x, location.y + i, location.z);
		if (temp != NULL) {
			new_crane->base.push_back(temp);
			world_map->attach_obj(loc<int>(location.x, location.y + i, location.z), temp, false, true);
		}
	}

	//make the arm
	for (int i = location.x - 1; i < radius + location.x - 1; i++) {
		temp = spawner->spawn_item(CUBE_T, i, location.y + height - 2, location.z);
		if (temp != NULL) {
			new_crane->arm.push_back(temp);
		}
	}

	//make the attachment
	temp = spawner->spawn_item(CUBE_T, 0, location.y + height - 2, location.z);
	if (temp != NULL) {
		new_crane->attachment = (temp);
	}

	new_crane->set_running(true);
	new_crane->set_aproaching_dest(true);
	new_crane->print_info();

	std::cout << "done creating crane" << std::endl;

	return output;
}


void environment::toggle_crane(int id) {
	crane_mgr.toggle_crane(id);
}


crane* environment::get_crane(int id) {
	return crane_mgr.get_crane(id);
}


int environment::create_furnace(const std::vector<loc<int> >& spots) {
	return furnace_mgr.create_furnace(spots);
}

void environment::add_mass_to_furnace(int id, double mass) {
	furnace_mgr.add_mass_to_furnace(id, mass);
}

int environment::place_truck(loc<int>& spawn) {
	int output = vehicle_mgr.create_truck(spawn);
	vehicle_mgr.all_vehicles[0]->body = spawner->spawn_item(TRUCK3, spawn.x, spawn.y, spawn.z);
	vehicle_mgr.all_vehicles[0]->headlights = spawner->spawn_item(HEADLIGHTS, spawn.x, spawn.y, spawn.z);
	vehicle_mgr.all_vehicles[0]->FLW = spawner->spawn_item(FLW, spawn.x, spawn.y, spawn.z);
	vehicle_mgr.all_vehicles[0]->FRW = spawner->spawn_item(FRW, spawn.x, spawn.y, spawn.z);
	vehicle_mgr.all_vehicles[0]->BLW = spawner->spawn_item(BLW, spawn.x, spawn.y, spawn.z);
	vehicle_mgr.all_vehicles[0]->BRW = spawner->spawn_item(BRW, spawn.x, spawn.y, spawn.z);

	return output;
}

bool environment::set_truck_dest(int id, loc<int>& spawn) {
	return vehicle_mgr.drive_truck(id, spawn);
}

int environment::place_car_worksation(loc<int>& spawn) {
	int output = -1;
	output = vehicle_mgr.create_truck_workstation(spawn);
	car_workstation* temp = vehicle_mgr.get_station(output);
	if (temp != NULL) {
		temp->lift = spawner->spawn_item(CAR_WORKSHOP_LIFT, spawn.x, spawn.y, spawn.z);
		temp->leaver = spawner->spawn_item(CAR_WORKSHOP_LEAVER, spawn.x, spawn.y, spawn.z);
	}
	else {
		std::cout << "failed to spawn the car workstation" << std::endl;
	}

	return output;
}

void environment::spawn_car_on_station(int id) {
	vehicle_mgr.spawn_car_on_station(id);
}


int environment::spawn_landing_pad(loc<int> location) {
	int output = aircraft_mgr.spawn_landing_pad(location);
	landing_site* temp = aircraft_mgr.get_landing_site(output);
	if (temp != NULL) {
		loc<int> location = temp->get_location();
		std::cout << "pad loc" << location.x << " " << location.y << " " << location.z << std::endl;
		temp->obj = spawner->spawn_item(AIRCRAFT_LANDING_PAD, location.x, location.y, location.z);
	}
	else {
		std::cout << "failed to spawn landing site" << std::endl;
	}
	return output;
}

int environment::spawn_plane(int landing_pad) {
	int output= aircraft_mgr.spawn_plane(landing_pad);

	aircraft* temp = aircraft_mgr.get_aircraft(output);
	if (temp != NULL) {
		loc<int> location = temp->get_location();
		std::cout <<"craft loc"<< location.x << " " << location.y << " " << location.z << std::endl;
		temp->obj = spawner->spawn_item(AIRCRAFT_T, location.x, location.y, location.z);
	}
	else {
		std::cout << "failed to spawn plane" << std::endl;
	}
	return output;
}

void environment::send_craft_to_site(int plane, loc<int> location) {
	 aircraft_mgr.send_craft_to_site(plane ,location);
}

void environment::send_craft_to_land_site(int plane, int land_pad) {
	 aircraft_mgr.send_craft_to_land_site(plane,land_pad);
}

void environment::send_craft_patrol(int plane, loc<int> location) {
	std::cout << "creating an orbiting patrol" << std::endl;
	aircraft_mgr.send_craft_patrol(plane, location);
}

void environment::draw_plane_route(int id) {
	aircraft* temp= aircraft_mgr.get_aircraft(id);
	if (temp != NULL && temp->current_route != NULL) {
		for (int i = 0; i < temp->current_route->waypoints.size(); i++) {
			spawner->spawn_item(CUBE_T,
				temp->current_route->waypoints[i].x/2,
				temp->current_route->waypoints[i].y/2,
				temp->current_route->waypoints[i].z/2);
		}
	}
}

void environment::run_air_sim() {
	std::vector<item_info*> working_models;

	working_models.push_back(spawner->spawn_item(AIRCRAFT_T, -1, -1, -1));
	working_models.push_back(spawner->spawn_item(CUBE_T, -1, -1, -1));
	working_models.push_back(spawner->spawn_item(CUBE_T, -1, -1, -1));
	working_models.push_back(spawner->spawn_item(CUBE_T, -1, -1, -1));
	working_models.push_back(spawner->spawn_item(CUBE_T, -1, -1, -1));

	aircraft_mgr.testing_sim(working_models);
}


void environment::place_fanx3x3(const loc<int>& location){

	item_info* frame = spawner->spawn_item(FAN_FRAME, location.x, location.y, location.z);
	item_info* fan = spawner->spawn_item(FAN, location.x, location.y, location.z);
	decor_manager.place_fanx3x3(location, frame, fan);
}
