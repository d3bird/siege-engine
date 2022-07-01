#include "environment.h"

environment::environment(optimized_spawner* os, motion_manger* mm):
	crane_mgr(mm), rail_mgr(mm), vehicle_mgr(mm), aircraft_mgr(mm),
	decor_manager(mm), missile_mgr(mm), mis_sim(NULL), door_mgr(mm) {
	spawner = os;
	updater = mm;
	world_map = NULL;
}

environment::~environment(){

	if (mis_sim != NULL) {
		delete mis_sim;
	}
}

void environment::update(double time_change) {
	crane_mgr.update(time_change);
	rail_mgr.update(time_change);
	furnace_mgr.update(time_change);
	vehicle_mgr.update(time_change);
	aircraft_mgr.update(time_change);
	decor_manager.update(time_change);

	if (mis_sim != NULL) {

	}

	door_mgr.update(time_change);
}

bool environment::spawn_ground_item(item_type type, const loc<int>& location) {
	item_info* temp = spawner->spawn_item(type, location.x, location.y, location.z);
	bool ouptut = world_map->attach_obj(location, temp,false,true);
	//if it failed to attach the item then delete the object
	if (!ouptut) {
		std::cout << "fail to spawn_ground_item" << std::endl;
		spawner->delete_item_from_buffer(temp);
	}

	return ouptut;
}

bool environment::spawn_floor_item(item_type type, const loc<int>& location) {
	item_info* temp = spawner->spawn_item(type, location.x, location.y, location.z);
	bool ouptut = world_map->attach_obj(location, temp, true, false);
	//if it failed to attach the item then delete the object
	if (!ouptut) {
		std::cout << "fail to spawn_ground_item" << std::endl;
		spawner->delete_item_from_buffer(temp);
	}

	return ouptut;
}

void environment::replace_ground_item(item_type type, const loc<int>& location) {
	item_info* temp = spawner->spawn_item(type, location.x, location.y, location.z);
	item_info* old = world_map->replace_obj(location, temp, false, true);
	//if it failed to attach the item then delete the object
	if (old != NULL) {
		std::cout << "removing replaced object" << std::endl;
		spawner->delete_item_from_buffer(old);
	}
}

void environment::replace_floor_item(item_type type, const loc<int>& location) {
	item_info* temp = spawner->spawn_item(type, location.x, location.y, location.z);
	item_info* old = world_map->replace_obj(location, temp, true, false);
	//if it failed to attach the item then delete the object
	if (old != NULL) {
		std::cout << "removing replaced object" << std::endl;
		spawner->delete_item_from_buffer(old);
	}
}

void environment::delete_grnd_obj(const loc<int>& location) {
	item_info* temp = world_map->delete_obj(location, false, true);
	if (temp != NULL) {
		spawner->delete_item_from_buffer(temp);
	}
}
void environment::delete_floor_obj(const loc<int>& location) {
	item_info* temp = world_map->delete_obj(location, true, false);
	if (temp != NULL) {
		spawner->delete_item_from_buffer(temp);
	}
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
			temp->angles.set_y_angle(90);
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
				temp->angles.set_y_angle(90);
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

void environment::print_furnace_info(int id) {

}

int environment::spawn_bulk_head_door(loc<int> start, loc<int> end, bool y_axis, bool dir1) {
	door_mgr.spawn_bulk_head_door(start, end, y_axis, dir1, spawner);

	int x_diff = abs(start.x - end.x);
	int z_diff = abs(start.z - end.z);
	std::cout << "x_diff " << x_diff << std::endl;
	std::cout << "z_diff " << z_diff << std::endl;
	if (x_diff > 0) {
		for (int i = start.x; i < end.x + 1; i++) {
			replace_floor_item(BULK_D_F_FLAT, loc<int>(i, start.y, start.z));
		}
	}
	else if (z_diff > 0) {
		for (int i = start.z; i < end.z + 1; i++) {
			replace_floor_item(BULK_D_F_FLAT, loc<int>(start.x, start.y, i));
		}
	}

	return -1;
}

int environment::get_door_at_loc(loc<int> location) {

	return -1;
}

void environment::open_door(int ID) {
	door_mgr.open_door(ID);
}

void environment::close_door(int ID) {
	door_mgr.close_door(ID);
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

int environment::spawn_landing_strip(loc<int> location) {
	int output = aircraft_mgr.spawn_landing_strip(location);
	landing_strip* temp = aircraft_mgr.get_landing_strip(output);
	if (temp != NULL) {
		loc<int> location = temp->get_location();
		std::cout << "strip loc" << location.x << " " << location.y << " " << location.z << std::endl;
		temp->obj = spawner->spawn_item(LANDING_STRIP, location.x, location.y, location.z);
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

int environment::spawn_drop_ship(loc<int> location) {
	int ship = aircraft_mgr.spawn_drop_ship(location);
	drop_ship* shipper = aircraft_mgr.get_drop_ship(ship);

	if (ship != NULL) {
		//DROP_SHIP_BODY, DROP_SHIP_ENGINE, DROP_SHIP_DOOR_R, DROP_SHIP_DOOR_L,
		shipper->body= spawner->spawn_item(DROP_SHIP_BODY, location.x, location.y, location.z);
		shipper->engines = spawner->spawn_item(DROP_SHIP_ENGINE, location.x, location.y, location.z);
		shipper->right_doors = spawner->spawn_item(DROP_SHIP_DOOR_R, location.x, location.y, location.z);
		shipper->left_doors = spawner->spawn_item(DROP_SHIP_DOOR_L, location.x, location.y, location.z);
	}
	else {
		std::cout << "failed to retrive dropship to asign models" << std::endl;
	}

	return ship;
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
	working_models.push_back(spawner->spawn_item(AIRCRAFT_T, -1, -1, -1));
	working_models.push_back(spawner->spawn_item(CUBE_T, -1, -1, -1));
	working_models.push_back(spawner->spawn_item(CUBE_T, -1, -1, -1));
	working_models.push_back(spawner->spawn_item(CUBE_T, -1, -1, -1));
	working_models.push_back(spawner->spawn_item(CUBE_T, -1, -1, -1));

	aircraft_mgr.testing_sim(working_models);
}

int environment::spawn_missile(const loc<int>& spawn) {
	item_info* mis = spawner->spawn_item(MISSILE3X1, spawn.x, spawn.y, spawn.z);
	return missile_mgr.spawn_missile(spawn, mis);
}

int environment::spawn_missile_lancher(const loc<int>& spawn) {
	item_info* lan = spawner->spawn_item(M_LAUNCHER, spawn.x, spawn.y, spawn.z);
	return missile_mgr.spawn_launcher(spawn, lan);
}

int environment::spawn_missile_w_lancher(const loc<int>& spawn) {
	item_info* mis = spawner->spawn_item(MISSILE3X1, spawn.x, spawn.y+ 5, spawn.z);
	item_info* lan = spawner->spawn_item(M_LAUNCHER, spawn.x, spawn.y, spawn.z);

	int lan_id = missile_mgr.spawn_launcher(spawn, lan);
	int mis_lan = missile_mgr.spawn_missile(spawn, mis);

	missile_mgr.move_missile_to_launcher(mis_lan, lan_id);

	return lan_id;
}

bool environment::fire_launcher(int launcher_id, const loc<int>& target) {
	return missile_mgr.fire_launcher(launcher_id, target);
}

void environment::start_missile_sim() {

	mis_sim = new missile_sim(&missile_mgr, spawner);
	mis_sim->start_sim();
}

void environment::place_fanx3x3(const loc<int>& location){

	item_info* frame = spawner->spawn_item(FAN_FRAME, location.x, location.y, location.z);
	item_info* fan = spawner->spawn_item(FAN, location.x, location.y, location.z);
	decor_manager.place_fanx3x3(location, frame, fan);
}
