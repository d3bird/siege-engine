#include "world.h"


world::world() {
	world_map = NULL;
	belts = NULL;
}

world::~world() {
	//delete_map_data(world_map);
}

void world::draw_gui() {

}

/*
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


void world::init(optimized_spawner* objm) {
	std::cout << "initing world" << std::endl;

	OBJM = objm;
	
	//create the managers
	belts = new belt_manager(OBJM);
	doors = new door_data::door_manager();

	//for the belt and door testing
	//gen_test_world(OBJM);

	// for the aircraft testing
	//gen_flight_world();
}

void world::update_obj_angle(item_info* obj, optimized_spawner* OBJM, float angle) {

	update_pak update_pac;

	update_pac.x = obj->x_m;
	update_pac.y = obj->y_m;
	update_pac.z = obj->z_m;

	update_pac.x_scale = 1;
	update_pac.y_scale = 1;
	update_pac.z_scale = 1;

	update_pac.angle = angle;

	update_pac.buffer_loc = obj->buffer_loc;
	update_pac.item_id = obj->item_id;

	OBJM->update_item_matrix(&update_pac);

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
*/