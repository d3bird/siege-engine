#pragma once

#include "manager/belt_manager.h"
#include "manager/manager_guis/door_manager_gui.h"
#include "manager/door_manager.h"

#include "../core/optimized_spawner.h"
#include "terrian_data.hpp"

#include "radio/radio_manager_global.h"

#include "rail/rail_manager.h"
#include "../utility/motion_manager.h"
#include "crane/crane_manager.h"
#include "crane/crane_manager_gui.h"

class world {
public:
	world();
	~world();

	void update(double deltaTime);

	void draw_gui();

	/*void place_belt(int x, int y, int z, int dir);
	void place_door(door_data::opening type, int x_start, int y_start, int z_start,
		int x_end, int y_end, int z_end);*/

	void init(optimized_spawner* OBJM, motion_manger * mmm);

	map_data* world_map;

private:

	//updating functions
//	void spawn_door_objs(door_data::door* data);

	bool inited = false;

	int x_size;
	int z_size;
	int y_size;

	belt_manager* belts;
	door_data::door_manager* doors;
	door_manager_gui* door_gui;
	optimized_spawner* OBJM;
	motion_manger* updater;
};

