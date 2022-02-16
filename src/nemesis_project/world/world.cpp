#include "world.h"


world::world() {
	world_map = NULL;

}

world::~world() {
	delete_map_data(world_map);
}


void world::init(int x_siz, int y_siz, int z_siz, optimized_spawner* OBJM) {
	std::cout << "initing world" << std::endl;

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


	for (int x = 0; x < x_size; x++) {
		for (int z = 0; z < z_size; z++) {
			world_map->map[1][x][z].ground = OBJM->spawn_item(GRASS_FLOOR, x, 1, z);
			world_map->map[0][x][z].ground = OBJM->spawn_item(DIRT_WALL, x, 0, z);
		}
	}
	
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