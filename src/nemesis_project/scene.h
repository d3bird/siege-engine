#pragma once

#include "core/create_engine.h"

#include "world/world.h"
#include "aircraft/aircraft_manager.h"

#include "testing/world_test.h"

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

	//

	//everything need to test the crane manager
	crane_manager crane_mgr;
	int place_crane(const loc<int> &location, int height, int radius);
	void toggle_crane(int id);
	crane* get_crane(int id);

	//everything needd to run the rail system
	bool place_rail(loc<int>& location, bool x_axis, railRoad::rail_type aType);
	bool can_place_rail(loc<int>& location);
	int place_cart(loc<int>& location);//returns the id of the cart
	int can_place_cart(loc<int>& location);
	void toggle_cart(int id, double velocity);
	void prin_rail_info();
	railRoad::rail_manager rail_mgr;

};

