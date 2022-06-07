#pragma once

#include "core/create_engine.h"

#include "world/world.h"
#include "aircraft/aircraft_manager.h"

#include "testing/world_test.h"

#include "vehicles/vehicle_manager.h"

#include "environment/environment.h"

class scene
{
public:
	scene();
	~scene();

	void display_guis();

	void update(double deltaTime);

	void init(engine_api* api);

	void key_press();

private:
	engine_api* API;

	external_paths paths;

	create_engine* engine;
	optimized_spawner* spawner;
	motion_manger* updater;

	//testing classes
	testing::world_test world_t;

	void spawner_test();


	void create_blank_world();

	world* worlds = NULL;

	void aircraft_test();
	void radio_test();

	void world_generation_test();

	void show_crane_area_test();
	bool running_tests = false;

	//misc vars
	int start;
	int end;
	bool dir = false;
	int speed = 5;
	//item_info* temp_cart = NULL;
	world* testing_w;

	environment* env;


};

