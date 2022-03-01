#include "world.h"


world::world() {
	world_map = NULL;
	belts = NULL;
}

world::~world() {
	delete_map_data(world_map);
}

void world::place_belt(int x, int y, int z, int dir) {

	if (belts != NULL && is_inbounds_of_map(x, y, z, world_map)) {
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

void world::init(int x_siz, int y_siz, int z_siz, optimized_spawner* objm) {
	std::cout << "initing world" << std::endl;

	OBJM = objm;

	x_size = x_siz;
	y_size= y_siz;
	z_size= z_siz;

	world_map = new map_data();

	world_map->x_size = x_siz;
	world_map->y_size = y_siz;
	world_map->z_size = z_siz;

	world_map->map = new map_cell**[y_size];

	for (int y = 0; y < y_size; y++) {
		world_map->map[y] = new map_cell * [x_size];
		for (int x = 0; x < x_size; x++) {
			world_map->map[y][x] = new map_cell[z_size];
		}
	}
	
	//create the managers
	belts = new belt_manager(OBJM);
	doors = new door_data::door_manager();

	//for the belt and door testing
	gen_test_world(OBJM);

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

void world::gen_test_world(optimized_spawner* OBJM) {

//create the map

	for (int x = 0; x < x_size; x++) {
		for (int z = 0; z < z_size; z++) {
			world_map->map[1][x][z].floor = OBJM->spawn_item(GRASS_FLOOR, x, 1, z);
			world_map->map[0][x][z].ground = OBJM->spawn_item(DIRT_WALL, x, 0, z);
		}
	}
	
	//create the belts

	//for (int x = 1; x < x_size-1; x++) {
	//	for (int z = 1; z < z_size-1; z++) {
	//		if ((x == 1 || x == x_size - 2) ||
	//			(z == 1 || z == z_size - 2)) {
	//			if (x == 1 && z ==1) {
	//				world_map->map[1][x][z].ground = OBJM->spawn_item(BELT_2, x, 1, z);
	//			}
	//			else if (x == 1 && z == z_size-2) {
	//				world_map->map[1][x][z].ground = OBJM->spawn_item(BELT_2, x, 1, z,90);
	//			}
	//			else if (x == x_size-2 && z == 1) {
	//				world_map->map[1][x][z].ground = OBJM->spawn_item(BELT_2, x, 1, z, 270);
	//			}
	//			else if (x == x_size-2 && z == z_size-2) {
	//				world_map->map[1][x][z].ground = OBJM->spawn_item(BELT_2, x, 1, z,180);
	//			}
	//			else {
	//				if (z == 1 || z ==z_size-2) {
	//					world_map->map[1][x][z].ground = OBJM->spawn_item(BELT_1, x, 1, z);
	//				}
	//				else {
	//					world_map->map[1][x][z].ground = OBJM->spawn_item(BELT_1, x, 1, z,90);
	//				}
	//			}
	//			
	//		}
	//	}
	//}
	place_belt(0, 1, 0, 0);

	place_belt(0, 1, 1, 0);
	place_belt(0, 1, 2, 0);
	place_belt(0, 1, 3, 0);
	place_belt(0, 1, 4, 0);

	//world_map->map[1][2][0].ground = OBJM->spawn_item(STONE_WALL, 2, 1, 0);
	//world_map->map[1][0][1].ground = OBJM->spawn_item(STONE_WALL, 0, 1, 1);

	belts->print_all_belts();


	std::cout << "spawning the test door" << std::endl;
	place_door(door_data::LEFT, x_size-1, 1, 0, x_size-1, 5, 7);
}


void world::gen_flight_world() {





}

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