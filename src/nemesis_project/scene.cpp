#include "scene.h"

#include "world/generation/generation_pipeline.h"

scene::scene(){
	API = NULL;
	engine = NULL;
	spawner = NULL;
}

scene::~scene(){

}

void scene::update() {

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

	//city_generator pipe(spawner);

	//pipe.create_platform(10,10,10);

	//create_blank_world();
	aircraft_test();
	//spawner_test();


	std::cout << "done scene init" << std::endl;

}

void scene::create_blank_world() {
	//city_generator pipe(spawner);

	worlds = new world();

	worlds->init(10, 10, 10, spawner);
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

		aircraft_control* AirContorl = new aircraft_control(spawner);
		AirContorl->init(AIRCRAFT_T);

	}
	else {
		std::cout << "can not test aircraft when there is no spawner" << std::endl;
	}
}