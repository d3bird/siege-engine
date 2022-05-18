#include "scene.h"

#include "world/generation/world_generation.h"
#include "world/generation/city_generation.h"

scene::scene(){
	API = NULL;
	engine = NULL;
	spawner = NULL;
}

scene::~scene(){

}

void scene::update(double deltaTime) {
	worlds->update(deltaTime);
	update_guis();
}

void scene::display_guis() {
	worlds->draw_gui();
}

void scene::update_guis() {

}

void scene::init(engine_api* api) {
	std::cout << "scene init" << std::endl;

	API = api;
	if (API == NULL) {
		return;
	}

	engine = new create_engine();
	spawner = engine->init(API);

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

	motion_manger* updater = new motion_manger(spawner);

	world* testing = pipe.create_world(test, updater);

	

	aircraft_manager* AirContorl = new aircraft_manager(spawner);

	loc<int> start_loc(5, 5, 5);
	AirContorl->start_animation_sim(start_loc);

	for (int i = 0; i < 40; i++) {
		if (!testing->place_rail(loc<int>(2 + i, 1, 1))) {
			std::cout << "failed to place rail" << std::endl;
		}


	}

	testing->prin_rail_info();

	int cart_id = testing->place_cart(loc<int>(2, 1, 1));
	if (cart_id != -1) {
		testing->toggle_cart(cart_id);
	} {
		std::cout << "failed to toggle cart, cart was not spawned" << std::endl;
	}
	//spawner->spawn_item(CART, 2, 1, 1);

	/*
		city_generation city(spawner);

		mobil_platform* plat = city.create_mobile_plat(city.get_flat_city_settings());
		*/
}
