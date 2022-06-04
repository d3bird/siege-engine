#include "scene.h"

#include "world/generation/world_generation.h"
#include "world/generation/city_generation.h"

scene::scene(): rail_mgr(NULL), vehicle_mgr(NULL) {
	API = NULL;
	engine = NULL;
	spawner = NULL;
	testing_w = NULL;
	env = NULL;
}

scene::~scene(){

}

void scene::update(double deltaTime) {

	if (running_tests) {

		return;
	}

	//worlds->update(deltaTime);
	//crane_mgr.update(deltaTime);
	env->update(deltaTime);
	rail_mgr.update(deltaTime);

	/*if (temp_cart != NULL) {
		double distance = deltaTime * speed;
		if (dir) {
			temp_cart->x_m += distance;
			if (temp_cart->x_m >= end) {
				dir = false;
				temp_cart->x_m = end;
			}
		}
		else {
			temp_cart->x_m -= distance;
			if (temp_cart->x_m <= start) {
				dir = true;
				temp_cart->x_m = start;
			}
		}
		updater->update_item(temp_cart);
	}*/
}


void scene::display_guis() {
//	worlds->draw_gui();
}

void scene::init(engine_api* api) {
	std::cout << "scene init" << std::endl;

	API = api;
	if (API == NULL) {
		return;
	}

	engine = new create_engine();
	spawner = engine->init(API);
	updater = new motion_manger(spawner);
	if (spawner == NULL) {
		return;
	}

	//deltaTime = API->get_timing()->get_time_change_static();

	//city_generator pipe(spawner);

	//pipe.create_platform(10,10,10);

	//create_blank_world();
	//aircraft_test();

	//radio_test();
	//spawner_test();
	running_tests = false;

	world_generation_test();

	std::cout << "done scene init" << std::endl;

}

void scene::create_blank_world() {
	//city_generator pipe(spawner);

	worlds = new world();

	//worlds->init(10, 10, 10, spawner);
}

void scene::spawner_test() {

	if (spawner != NULL) {
		std::cout << "spawner spawning" << std::endl;

		int y = 0;
		int x_size = 11;
		int z_size = 11;

		for (int x = 0; x < x_size; x++) {
			for (int z = 0; z < z_size; z++) {
				spawner->spawn_item(WALL_TEMP, x, y, z);
				spawner->spawn_item(FLOOR_TEMP, x, y, z);

				if ((x == x_size / 2) && (z == z_size / 2)) {
					for (y = 1; y < 4; y++) {
						spawner->spawn_item(WALL_TEMP, x, y, z);
						spawner->spawn_item(FLOOR_TEMP, x, y, z);
					}
					y = 0;
				}

			}
		}


std::cout << "done spawner spawning" << std::endl;
	}
	else {
	std::cout << "spawner was NULL" << std::endl;
	}
}

void scene::aircraft_test() {
	std::cout << "testing aircraft" << std::endl;
	if (spawner != NULL) {
		int x_size = 15;
		int z_size = 15;
		int y = 0;

		//spawn a temp groud under the planes 
		for (int x = 0; x < x_size; x++) {
			for (int z = 0; z < z_size; z++) {
				spawner->spawn_item(DIRT_WALL, x, y, z);
				//spawner->spawn_item(GRASS_FLOOR, x, y+1, z);
			}
		}

		aircraft_manager* AirContorl = new aircraft_manager(spawner);
		AirContorl->init(AIRCRAFT_T);

	}
	else {
		std::cout << "can not test aircraft when there is no spawner" << std::endl;
	}
}

void scene::radio_test() {
	if (spawner != NULL) {

		int x_size = 15;
		int z_size = 15;
		int y = 0;


		//spawn a temp groud under the planes 
		for (int x = 0; x < x_size; x++) {
			for (int z = 0; z < z_size; z++) {
				spawner->spawn_item(DIRT_WALL, x, y, z);
				spawner->spawn_item(GRASS_FLOOR, x, y + 1, z);
			}
		}

		//makesure that the models work

		bool model_test = true;

		if (model_test) {
			spawner->spawn_item(BROADCAST_TOWER, 1, 1, 1);
			spawner->spawn_item(RADIO_CONSOLE, 6, 1, 1);
			spawner->spawn_item(WALL_SPEAKER, 8, 1, 1);
			spawner->spawn_item(SUPPORT, 9, 1, 1);
			spawner->spawn_item(SUPPORT, 9, 2, 1);
			spawner->spawn_item(SUPPORT, 9, 3, 1);
			spawner->spawn_item(SUPPORT, 9, 4, 1);
			spawner->spawn_item(SPEAKER_TOP, 9, 5, 1);
		}
		else {

			for (y = 1; y < 3; y++) {
				for (int x = x_size - 5; x < x_size; x++) {
					for (int z = z_size - 5; z < z_size; z++) {
						spawner->spawn_item(DIRT_WALL, x, y, z);
						spawner->spawn_item(GRASS_FLOOR, x, y + 1, z);
					}
				}
			}

			spawner->spawn_item(BROADCAST_TOWER, x_size - 3, y, z_size - 3);
			spawner->spawn_item(RADIO_CONSOLE, x_size - 3, 1, z_size - 6, 90);

			int x_cent = x_size / 2;
			int z_cent = z_size / 2;



		}

	}
}

void scene::show_crane_area_test() {

	//crane_mgr = crane_manager(updater);

	//int output = place_crane(loc<int>(10, 2, 10), 7, 7);

	//std::vector<loc<int> > list =crane_mgr.get_converate(0);

	//for (int i = 0; i < list.size(); i++) {
	//	spawner->spawn_item(CUBE_T, list[i].x, list[i].y, list[i].z);
	//}

}

void scene::world_generation_test() {

	world_generation pipe(spawner);

	world_gen_settings* test = pipe.flat_land_settings();

	testing_w = pipe.create_world(test, updater);

	env = new environment(spawner, updater);

	//creating managers
	//crane_mgr = crane_manager(updater);

	if (running_tests) {
		show_crane_area_test();
		return;
	}
	//spawn some trees 

	spawner->spawn_item(CUBE_TREE_T, 8, 1, 5);

	//code to test out the aircraft

	aircraft_manager* AirContorl = new aircraft_manager(spawner);

	//fighter landing pad
	spawner->spawn_item(AIRCRAFT_LANDING_PAD, 4, 2, 5);
	for (int x = 0; x < 3; x++) {
		for (int z = 0; z < 3; z++) {
			spawner->spawn_item(CONCRETE_WALL, 3 + x, 1, 4 + z);
		}
	}

	//BOMBER landing pad
	spawner->spawn_item(AIRCRAFT_LANDING_PAD, 20, 2, 7);
	spawner->spawn_item(BOMBER, 20, 2, 7);
	for (int x = 0; x < 3; x++) {
		for (int z = 0; z < 3; z++) {
			spawner->spawn_item(CONCRETE_WALL, 19 + x, 1, 6 + z);
		}
	}

	loc<int> start_loc(5, 5, 5);
	AirContorl->start_animation_sim(start_loc);

	//code to test out the radio systems (just models for now)
	int x_off = 0;
	int z_off = 10;
	spawner->spawn_item(BROADCAST_TOWER, 2, 1, 5 + z_off);
	spawner->spawn_item(RADIO_CONSOLE, 5, 1, 2 + z_off);
	spawner->spawn_item(WALL_SPEAKER, 8, 1, 1 + z_off);
	spawner->spawn_item(SUPPORT, 9, 1, 1 + z_off);
	spawner->spawn_item(SUPPORT, 9, 2, 1 + z_off);
	spawner->spawn_item(SUPPORT, 9, 3, 1 + z_off);
	spawner->spawn_item(SUPPORT, 9, 4, 1 + z_off);
	spawner->spawn_item(SPEAKER_TOP, 9, 5, 1 + z_off);

	//spawn the human for scale

	spawner->spawn_item(HEAD_T, 3, 1, -1 + z_off);
	spawner->spawn_item(BODY_T, 3, 1, -1 + z_off);
	spawner->spawn_item(LEFT_LEG, 3, 1, -1 + z_off);
	spawner->spawn_item(RIGHT_LEG, 3, 1, -1 + z_off);
	spawner->spawn_item(LEFT_ARM, 3, 1, -1 + z_off);
	spawner->spawn_item(RIGHT_ARM, 3, 1, -1 + z_off);


	//code to test out the weapon system
	spawner->spawn_item(ROATING_TURRET, 2, 1, 9 + z_off);
	spawner->spawn_item(TURRET_BASE, 2, 1, 9 + z_off);
	spawner->spawn_item(SAM_ATTACH, 2, 1, 9 + z_off);
	spawner->spawn_item(SMALL_MISSLE, 3, 1, 9 + z_off);
	spawner->spawn_item(SMALL_MISSLE, 4, 1, 9 + z_off);


	//code to test out the rails

	rail_mgr = railRoad::rail_manager(updater);

	//create the rail at the bottom of the map
	for (int i = 0; i < 40; i++) {
		if (!place_rail(loc<int>(2 + i, 1, 3), true, railRoad::STRAIGHT)) {
			std::cout << "failed to place rail" << std::endl;
		}
	}

	//temp_cart = spawner->spawn_item(CART, 2, 1, 1);
	start = 2;
	end = 39;

	int cart_id = place_cart(loc<int>(2, 1, 3));
	if (cart_id != -1) {
		toggle_cart(cart_id, 10);
	}
	else {
		std::cout << "failed to toggle cart, cart was not spawned" << std::endl;
	}

	//create the rail going over top of the rail

	for (int i = 0; i < 12; i++) {
		if (!place_rail(loc<int>(6, 2, 1 + i), false, railRoad::STRAIGHT)) {
			std::cout << "failed to place rail" << std::endl;
		}
		spawner->spawn_item(STONE_FLOOR, 6, 2, 1 + i);
		if (1 + i != 3) {
			spawner->spawn_item(STONE_WALL, 6, 1, 1 + i);
		}

	}


	if (!place_rail(loc<int>(12, 1, 1), true, railRoad::STRAIGHT)) {
	}

	cart_id = place_cart(loc<int>(12, 1, 1));
	if (cart_id != -1) {
		toggle_cart(cart_id, 25);
	}
	else {
		std::cout << "failed to toggle cart, cart was not spawned" << std::endl;
	}

	if (!place_rail(loc<int>(11, 1, 1), true, railRoad::STRAIGHT)) {
	}


	if (!place_rail(loc<int>(8, 2, 1), true, railRoad::STRAIGHT)) {
		std::cout << "failed to place slant rail" << std::endl;
	}

if (!place_rail(loc<int>(10, 1, 1), true, railRoad::SLANT)) {
		std::cout << "failed to place slant rail" << std::endl;
	}

	cart_id = place_cart(loc<int>(6, 2, 1));
	if (cart_id != -1) {
		toggle_cart(cart_id, 2);
	}
	else {
		std::cout << "failed to toggle cart, cart was not spawned" << std::endl;
	}

	//create a block of rails to test the connection


	for (int x = 10; x < 20; x++) {
		for (int z = 10; z < 20; z++) {
			//if (z % 2 == 0) {
				if (!place_rail(loc<int>(x, 1, z), true, railRoad::STRAIGHT)) {
					std::cout << "failed to place rail" << std::endl;
				}
		//	}
			if (x == 10) {
			//if (x == 10) {
				cart_id = place_cart(loc<int>(x, 1, z));
				if (cart_id != -1) {
					toggle_cart(cart_id, 2* cart_id);
				}
				else {
					std::cout << "failed to toggle cart, cart was not spawned" << std::endl;
				}
			}
		}
	}

	//testing out the slanted rails

	for (int i = 0; i < 12; i++) {
		if (!place_rail(loc<int>(1+i, 1, 0), true, railRoad::STRAIGHT)) {
			std::cout << "failed to place rail" << std::endl;
		}

		if (i == 11) {
			cart_id = place_cart(loc<int>(1+i, 1, 0));
			if (cart_id != -1) {
				toggle_cart(cart_id, 7);
			}
			else {
				std::cout << "failed to toggle cart, cart was not spawned" << std::endl;
			}
		}

	}

	if (!place_rail(loc<int>(0, 1, 0), true, railRoad::SLANT)) {
		std::cout << "failed to place slant rail" << std::endl;
	}

	if (!place_rail(loc<int>(3, 1, 7), true, railRoad::CURVE)) {
		std::cout << "failed to place curve rail" << std::endl;
	}

	place_rail(loc<int>(3, 1, 7), true, railRoad::STRAIGHT);
	place_rail(loc<int>(4, 1, 7), true, railRoad::STRAIGHT);
	place_rail(loc<int>(5, 1, 7), true, railRoad::STRAIGHT);

	place_rail(loc<int>(1, 1, 4), false, railRoad::STRAIGHT);
	place_rail(loc<int>(1, 1, 3), false, railRoad::STRAIGHT);
	place_rail(loc<int>(1, 1, 5), false, railRoad::STRAIGHT);

	cart_id = place_cart(loc<int>(1, 1, 4));
	if (cart_id != -1) {
		toggle_cart(cart_id, 5);
	}
	else {
		std::cout << "failed to toggle cart, cart was not spawned" << std::endl;
	}

	cart_id = place_cart(loc<int>(3, 1, 7));
	if (cart_id != -1) {
		toggle_cart(cart_id, 9);
	}
	else {
		std::cout << "failed to toggle cart, cart was not spawned" << std::endl;
	}

	spawner->spawn_item(HOPPER, 6, 2, -1 + z_off);
	spawner->spawn_item(DIRT_WALL, 7, 1, -2 + z_off);
	spawner->spawn_item(DIRT_WALL, 7, 1, 0 + z_off);
	spawner->spawn_item(DIRT_WALL, 5, 1, -2 + z_off);
	spawner->spawn_item(DIRT_WALL, 5, 1, 0 + z_off);

	spawner->spawn_item(CONCRETE_FLOOR, 7, 2, -2 + z_off);
	spawner->spawn_item(CONCRETE_FLOOR, 7, 2, 0 + z_off);
	spawner->spawn_item(CONCRETE_FLOOR, 5, 2, -2 + z_off);
	spawner->spawn_item(CONCRETE_FLOOR, 5, 2, 0 + z_off);

	prin_rail_info();
	//rail_mgr.print_rail_connections();
	//rail_mgr.check_for_bad_connections();

	//code to test out the cranes

	int new_crane = env->place_crane(loc<int>(10, 1, 6), 12, 10);
	env->toggle_crane(new_crane);

	//spawner->spawn_item(HOPPER, 2, 1, 3);


	//the testing code for the vehicles

	vehicle_mgr = vehicle_manager(updater);

	place_truck(loc<int>(2, 1, 9));
	place_truck(loc<int>(0, 1, 9));
	place_truck(loc<int>(2, 1, 11));
	place_truck(loc<int>( 0, 1, 11));

}

void scene::key_press() {
}

bool scene::place_rail(loc<int>& location,bool x_axis, railRoad::rail_type aType) {
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
		rail_mgr.add_rail(location, x_axis, aType);
	}
	return output;
}

bool scene::can_place_rail(loc<int>& location) {
	bool output = true;
	return true;
	std::pair < loc<int>, loc<int> > world_locs;// = world_map->get_map_local_cords(location);

	//check to makesure the locs are valid
	if (world_locs.first == loc<int>()) {

		//check to makesure that there are no other objects 

		output = false;
	}

	return output;
}


int scene::place_cart(loc<int>& location) {
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

int scene::can_place_cart(loc<int>& location) {
	return rail_mgr.can_place_cart(location);
}

void scene::toggle_cart(int id, double velocity) {
	rail_mgr.set_cart_vel(id,velocity);
	rail_mgr.toggle_cart(id);
}

void scene::prin_rail_info() {
	rail_mgr.print_info();
}

int scene::place_truck(loc<int>& spawn) {
	int output = vehicle_mgr.create_truck( spawn);
	vehicle_mgr.all_vehicles[0]->body = spawner->spawn_item(TRUCK3, spawn.x, spawn.y, spawn.z);
	vehicle_mgr.all_vehicles[0]->headlights = spawner->spawn_item(HEADLIGHTS, spawn.x, spawn.y, spawn.z);
	vehicle_mgr.all_vehicles[0]->FLW = spawner->spawn_item(FLW, spawn.x, spawn.y, spawn.z);
	vehicle_mgr.all_vehicles[0]->FRW = spawner->spawn_item(FRW, spawn.x, spawn.y, spawn.z);
	vehicle_mgr.all_vehicles[0]->BLW = spawner->spawn_item(BLW, spawn.x, spawn.y, spawn.z);
	vehicle_mgr.all_vehicles[0]->BRW = spawner->spawn_item(BRW, spawn.x, spawn.y, spawn.z);
	
	return output;
}

bool scene::set_truck_dest(int id, loc<int>& spawn) {
	return vehicle_mgr.drive_truck(id, spawn);
}