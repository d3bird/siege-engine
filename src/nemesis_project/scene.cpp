#include "scene.h"

#include "world/generation/world_generation.h"
#include "world/generation/city_generation.h"

#include "utility/math/math_check.h"

scene::scene() {
	API = NULL;
	engine = NULL;
	spawner = NULL;
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

		//aircraft_manager* AirContorl = new aircraft_manager(spawner);
	//	AirContorl->init(AIRCRAFT_T);

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

	map_data* world_map = pipe.create_world(test, updater);

	env = new environment(spawner, updater);
	
	env->set_map_data(world_map);


	//creating managers
	//crane_mgr = crane_manager(updater);

	//spawn some trees 

	env->spawn_ground_item(CUBE_TREE_T, loc<int>(8, 1, 5));

	//code to test out the aircraft

	//aircraft_manager* AirContorl = new aircraft_manager(spawner);

	//fighter landing pad
	//spawner->spawn_item(AIRCRAFT_LANDING_PAD, 4, 2, 5);
	int pad1 = env->spawn_landing_pad(loc<int>(4, 2, 5));
	for (int x = 0; x < 3; x++) {
		for (int z = 0; z < 3; z++) {
			env->spawn_ground_item(CONCRETE_WALL, loc<int>(3 + x, 1, 4 + z));
		}
	}

	//BOMBER landing pad
	//spawner->spawn_item(AIRCRAFT_LANDING_PAD, 20, 2, 7);
	//spawner->spawn_item(BOMBER, 20, 2, 7);
	int pad2 = env->spawn_landing_pad(loc<int>(20, 2, 7));
	for (int x = 0; x < 3; x++) {
		for (int z = 0; z < 3; z++) {
			env->spawn_ground_item(CONCRETE_WALL, loc<int>(19 + x, 1, 6 + z));
		}
	}

	loc<int> start_loc(5, 5, 5);


	//AirContorl->start_animation_sim(start_loc);

	//code to test out the radio systems (just models for now)
	int x_off = 0;
	int z_off = 10;
	env->spawn_ground_item(BROADCAST_TOWER, loc<int>(2, 1, 5 + z_off));
	env->spawn_ground_item(RADIO_CONSOLE, loc<int>(5, 1, 2 + z_off));
	env->spawn_ground_item(WALL_SPEAKER, loc<int>(8, 1, 1 + z_off));
	env->spawn_ground_item(SUPPORT, loc<int>(9, 1, 1 + z_off));
	env->spawn_ground_item(SUPPORT, loc<int>(9, 2, 1 + z_off));
	env->spawn_ground_item(SUPPORT, loc<int>(9, 3, 1 + z_off));
	env->spawn_ground_item(SUPPORT, loc<int>(9, 4, 1 + z_off));
	env->spawn_ground_item(SPEAKER_TOP, loc<int>(9, 5, 1 + z_off));

	//spawn the human for scale

	env->spawn_person(loc<int>(3, 1, -1 + z_off));

	//code to test out the weapon system
	spawner->spawn_item(ROATING_TURRET, 2, 1, 9 + z_off);
	spawner->spawn_item(TURRET_BASE, 2, 1, 9 + z_off);
	spawner->spawn_item(SAM_ATTACH, 2, 1, 9 + z_off);
	spawner->spawn_item(SMALL_MISSLE, 3, 1, 9 + z_off);
	spawner->spawn_item(SMALL_MISSLE, 4, 1, 9 + z_off);


	//code to test out the rails



	//create the rail at the bottom of the map
	for (int i = 0; i < 40; i++) {
		if (!env->place_rail(loc<int>(2 + i, 1, 3), true, railRoad::STRAIGHT)) {
			std::cout << "failed to place rail" << std::endl;
		}
	}

	//temp_cart = spawner->spawn_item(CART, 2, 1, 1);
	start = 2;
	end = 39;

	int cart_id = env->place_cart(loc<int>(2, 1, 3));
	if (cart_id != -1) {
		env->toggle_cart(cart_id, 10);
	}
	else {
		std::cout << "failed to toggle cart, cart was not spawned" << std::endl;
	}

	//create the rail going over top of the rail

	for (int i = 0; i < 12; i++) {
		if (!env->place_rail(loc<int>(6, 2, 1 + i), false, railRoad::STRAIGHT)) {
			std::cout << "failed to place rail" << std::endl;
		}
		env->spawn_floor_item(STONE_FLOOR, loc<int>(6, 2, 1 + i));
		if (1 + i != 3) {
			env->spawn_ground_item(STONE_WALL, loc<int>(6, 1, 1 + i));
		}

	}


	if (!env->place_rail(loc<int>(12, 1, 1), true, railRoad::STRAIGHT)) {
	}

	cart_id = env->place_cart(loc<int>(12, 1, 1));
	if (cart_id != -1) {
		env->toggle_cart(cart_id, 25);
	}
	else {
		std::cout << "failed to toggle cart, cart was not spawned" << std::endl;
	}

	if (!env->place_rail(loc<int>(11, 1, 1), true, railRoad::STRAIGHT)) {
	}


	if (!env->place_rail(loc<int>(8, 2, 1), true, railRoad::STRAIGHT)) {
		std::cout << "failed to place slant rail" << std::endl;
	}

	if (!env->place_rail(loc<int>(10, 1, 1), true, railRoad::SLANT)) {
		std::cout << "failed to place slant rail" << std::endl;
	}

	cart_id = env->place_cart(loc<int>(6, 2, 1));
	if (cart_id != -1) {
		env->toggle_cart(cart_id, 2);
	}
	else {
		std::cout << "failed to toggle cart, cart was not spawned" << std::endl;
	}

	//create a block of rails to test the connection


	for (int x = 10; x < 20; x++) {
		for (int z = 10; z < 20; z++) {
			//if (z % 2 == 0) {
			if (!env->place_rail(loc<int>(x, 1, z), true, railRoad::STRAIGHT)) {
				std::cout << "failed to place rail" << std::endl;
			}
			//	}
			if (x == 10) {
				//if (x == 10) {
				cart_id = env->place_cart(loc<int>(x, 1, z));
				if (cart_id != -1) {
					env->toggle_cart(cart_id, 2 * cart_id);
				}
				else {
					std::cout << "failed to toggle cart, cart was not spawned" << std::endl;
				}
			}
		}
	}

	//testing out the slanted rails

	for (int i = 0; i < 12; i++) {
		if (!env->place_rail(loc<int>(1 + i, 1, 0), true, railRoad::STRAIGHT)) {
			std::cout << "failed to place rail" << std::endl;
		}

		if (i == 11) {
			cart_id = env->place_cart(loc<int>(1 + i, 1, 0));
			if (cart_id != -1) {
				env->toggle_cart(cart_id, 7);
			}
			else {
				std::cout << "failed to toggle cart, cart was not spawned" << std::endl;
			}
		}

	}

	if (!env->place_rail(loc<int>(0, 1, 0), true, railRoad::SLANT)) {
		std::cout << "failed to place slant rail" << std::endl;
	}

	if (!env->place_rail(loc<int>(3, 1, 7), true, railRoad::CURVE)) {
		std::cout << "failed to place curve rail" << std::endl;
	}

	env->place_rail(loc<int>(3, 1, 7), true, railRoad::STRAIGHT);
	env->place_rail(loc<int>(4, 1, 7), true, railRoad::STRAIGHT);
	env->place_rail(loc<int>(5, 1, 7), true, railRoad::STRAIGHT);

	env->place_rail(loc<int>(1, 1, 4), false, railRoad::STRAIGHT);
	env->place_rail(loc<int>(1, 1, 3), false, railRoad::STRAIGHT);
	env->place_rail(loc<int>(1, 1, 5), false, railRoad::STRAIGHT);

	cart_id = env->place_cart(loc<int>(1, 1, 4));
	if (cart_id != -1) {
		env->toggle_cart(cart_id, 5);
	}
	else {
		std::cout << "failed to toggle cart, cart was not spawned" << std::endl;
	}

	cart_id = env->place_cart(loc<int>(3, 1, 7));
	if (cart_id != -1) {
		env->toggle_cart(cart_id, 9);
	}
	else {
		std::cout << "failed to toggle cart, cart was not spawned" << std::endl;
	}

	env->spawn_ground_item(HOPPER, loc<int>(6, 2, -1 + z_off));
	env->spawn_ground_item(DIRT_WALL, loc<int>(7, 1, -2 + z_off));
	env->spawn_ground_item(DIRT_WALL, loc<int>(7, 1, 0 + z_off));
	env->spawn_ground_item(DIRT_WALL, loc<int>(5, 1, -2 + z_off));
	env->spawn_ground_item(DIRT_WALL, loc<int>(5, 1, 0 + z_off));

	env->spawn_floor_item(CONCRETE_FLOOR, loc<int>(7, 2, -2 + z_off));
	env->spawn_floor_item(CONCRETE_FLOOR, loc<int>(7, 2, 0 + z_off));
	env->spawn_floor_item(CONCRETE_FLOOR, loc<int>(5, 2, -2 + z_off));
	env->spawn_floor_item(CONCRETE_FLOOR, loc<int>(5, 2, 0 + z_off));

	env->prin_rail_info();
	//rail_mgr.print_rail_connections();
	//rail_mgr.check_for_bad_connections();

	//code to test out the cranes

	int new_crane = env->place_crane(loc<int>(10, 1, 6), 12, 10);
	env->toggle_crane(new_crane);

	env->show_crane_area(new_crane);

	//spawner->spawn_item(HOPPER, 2, 1, 3);

	//misc testing
	//env->place_fanx3x3(loc<int>(40, 1, 6));

	//the testing code for the vehicles


	env->place_truck(loc<int>(2, 1, 9));
	env->place_truck(loc<int>(0, 1, 9));
	env->place_truck(loc<int>(2, 1, 11));
	env->place_truck(loc<int>(0, 1, 11));

	env->place_car_worksation(loc<int>(25, 1, 11));
	env->spawn_car_on_station(0);

	mathfunc::check_circle_math();

	env->spawn_plane(pad1);
	env->spawn_plane(pad2);
	env->send_craft_patrol(0, loc<int>(15, 10, 15));
	//env->draw_plane_route(0);
	env->run_air_sim();

	env->spawn_drop_ship(loc<int>(30, 2, 10));
	env->spawn_thopter(loc<int>(40, 1, 10));
	env->spawn_landing_strip(loc<int>(30, 2, 20));

//	env->spawn_missile(loc<int>(27, 2, 15));
	env->spawn_missile_lancher(loc<int>(30, 2, 15));
	int test_lan = env->spawn_missile_lancher(loc<int>(34, 2, 15));
	//int test_lan = env->spawn_missile_w_lancher(loc<int>(34, 2, 15));
	//env->fire_launcher(test_lan, loc<int>(0, 0, 0));
	env->start_missile_sim();


	env->spawn_bulk_head_door(loc<int>(14, 1, 0), loc<int>(20, 5, 0),true, true);

	//testing for the ground item manager

	env->place_ground_object(grnd_items::BOX, loc<int>(0, 1, 1));
	env->place_ground_object(grnd_items::INGOT, loc<int>(1, 1, 1));
	env->place_ground_object(grnd_items::BARREL, loc<int>(2,1,1));

	//testing for the belt manager
	env->spawn_ground_item(SUPPORT, loc<int>(9, 1, 11));

	env->spawn_belt(loc<int>(12, 1, 6), 0);
	env->spawn_belt(loc<int>(13, 1, 6), 0);
	env->spawn_belt(loc<int>(14, 1, 6), 0);
	env->spawn_belt(loc<int>(14, 1, 7), 1);
	env->spawn_belt(loc<int>(13, 1, 7), 2);


}

void scene::key_press() {

}
