#pragma once

#include "core/create_engine.h"

#include "world/world.h"
#include "aircraft/aircraft_manager.h"

class scene
{
public:
	scene();
	~scene();

	void display_guis();

	void update();

	void init(engine_api* api);

private:
	engine_api* API;

	external_paths paths;

	create_engine* engine;
	optimized_spawner* spawner;
	void spawner_test();

	void update_guis();

	void create_blank_world();

	world* worlds = NULL;

	void aircraft_test();
	void radio_test();
};

