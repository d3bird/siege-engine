#include "world.h"


world::world() {
	world_map = NULL;
	belts = NULL;
	updater = NULL;
}

world::~world() {
	//delete_map_data(world_map);
}

void world::draw_gui() {
}

void world::update(double deltaTime) {

}


void world::init(optimized_spawner* objm, motion_manger* mmm) {
	std::cout << "initing world" << std::endl;

	OBJM = objm;
	updater = mmm;
	//create the managers
	belts = new belt_manager(OBJM);
	doors = new door_data::door_manager_old();
}

/*
void world::spawn_door_objs(door_data::door* data) {
	if (data == NULL) {
		return;
	}

	if (data->d_sec != NULL) {
		std::cout << "spawning in the door" << std::endl;
		for (int x = 0; x < data->ar_x; x++) {
			for (int z = 0; z < data->ar_z; z++) {
				if (data->d_sec[x][z].door_sec == NULL) {
					data->d_sec[x][z].door_sec = OBJM->spawn_item(DOOR_SECTION,
						data->d_sec[x][z].x_current, data->d_sec[x][z].y_current, data->d_sec[x][z].z_current,
						data->d_sec[x][z].angle);
				}
			}

		}

	}
	else {
		std::cout << "failed t0 spawn in the door" << std::endl;

	}

}


void world::place_belt(int x, int y, int z, int dir) {

	if (belts != NULL && is_inbounds_of_map_local(x, y, z, world_map)) {
		item_info* belt = belts->place_belt(x, y, z, dir);
		if (belt == NULL) {
			std::cout << "can not place belt, belt was null" << std::endl;
		}
		else {
			world_map->map[y][x][z].ground = belt;
		}
	}
	else {
		std::cout << "can not place belt, out of bounds" << std::endl;
	}
}

void world::place_door(door_data::opening type, int x_start, int y_start, int z_start,
	int x_end, int y_end, int z_end) {

	door_data::door* data = doors->place_door(type, x_start, y_start, z_start, x_end, y_end, z_end);

	spawn_door_objs(data);
}
*/