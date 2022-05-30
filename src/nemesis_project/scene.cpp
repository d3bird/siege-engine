#include "scene.h"

#include "world/generation/world_generation.h"
#include "world/generation/city_generation.h"

scene::scene(): rail_mgr(NULL) {
	API = NULL;
	engine = NULL;
	spawner = NULL;
	testing_w = NULL;
}

scene::~scene(){

}

void scene::update(double deltaTime) {
	worlds->update(deltaTime);
	crane_mgr.update(deltaTime);

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
	world_generation_test();
	//radio_test();
	//spawner_test();


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

void scene::world_generation_test() {

	world_generation pipe(spawner);

	world_gen_settings* test = pipe.flat_land_settings();

	testing_w = pipe.create_world(test, updater);

	aircraft_manager* AirContorl = new aircraft_manager(spawner);

	loc<int> start_loc(5, 5, 5);
	AirContorl->start_animation_sim(start_loc);

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

	prin_rail_info();
	//rail_mgr.print_rail_connections();
	//rail_mgr.check_for_bad_connections();

	place_crane(loc<int>(10, 1, 6), 12, 10);
	//spawner->spawn_item(HOPPER, 2, 1, 3);
}

void scene::key_press() {
}

int scene::place_crane(const loc<int> &location, int height, int radius) {
	int output = -1;
	item_info* temp = 0;

	std::cout << "creating crane" << std::endl;

	std::cout << height << " , " << radius << std::endl;

	crane* new_crane = crane_mgr.create_crane(height, radius);
	if (new_crane == NULL) {
		std::cout << "failed creating crane" << std::endl;
		return output;
	}

	//make the central pillar
	for (int i = 0; i < height; i++) {
		temp = spawner->spawn_item(CRANE_B, location.x, location.y + i, location.z);
		if (temp != NULL) {
			new_crane->base.push_back(temp);
		}
	}

	//make the arm
	for (int i = location.x - 1; i < radius + location.x - 1; i++) {
		temp = spawner->spawn_item(CUBE_T, i, location.y + height - 1, location.z);
		if (temp != NULL) {
			crane::crane_sect new_sect;
			new_sect.obj = temp;
			new_crane->arm.push_back(new_sect);
		}
	}


	new_crane->print_info();

	std::cout << "done creating crane" << std::endl;

	return output;
}


void scene::toggle_crane(int id) {



}


bool scene::place_rail(loc<int>& location,bool x_axis, railRoad::rail_type aType) {
	bool output = can_place_rail(location);

	if (output) {
		item_info* temp = NULL;

		switch (aType)
		{
		case railRoad::CURVE:
			std::cout << "there is no model for this rail" << std::endl;
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