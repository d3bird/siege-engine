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
	crane_gui.draw();
}

void world::update(double deltaTime) {
	//std::cout << deltaTime << std::endl;
	//update_rails(deltaTime);
	crane_mgr.update(deltaTime);
}

void world::update_rails(double time_change) {

	for (int i = 0; i < rail_mgr.carts.size(); i++) {
		if (rail_mgr.carts[i].cart_obj != NULL && rail_mgr.carts[i].get_velocity() != 0) {
			bool dir = rail_mgr.carts[i].get_velocity() < 0 ? false : true;

			updater->update_item(rail_mgr.carts[i].cart_obj);

			if (dir) {//to 

			}
			else {

			}

		}
	}
}

int world::place_crane(loc<int> location, int height, int radius) {
	int output =-1;

	//make the central pillar
	for (int i = 0; i < height; i++) {
		OBJM->spawn_item(CRANE_B, location.x, location.y + i, location.z);
	}

	//make the arm
	for (int i = location.x - 1; i < radius + location.x - 1; i++) {
		OBJM->spawn_item(CUBE_T, i, location.y +height - 1, location.z);
	}


	return output;
}

void world::toggle_crane(int id) {

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


void world::init(optimized_spawner* objm, motion_manger* mmm) {
	std::cout << "initing world" << std::endl;

	OBJM = objm;
	updater = mmm;
	//create the managers
	belts = new belt_manager(OBJM);
	doors = new door_data::door_manager();
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

bool world::place_rail(loc<int>& location) {
	bool output = can_place_rail(location);

	if (output) {
		OBJM->spawn_item(RAIL, location.x, location.y, location.z);
		rail_mgr.add_rail(location);
	}
	return output;
}

bool world::can_place_rail(loc<int>& location) {
	bool output = true;

	std::pair < loc<int>, loc<int> > world_locs = world_map->get_map_local_cords(location);

	//check to makesure the locs are valid
	if (world_locs.first == loc<int>()) {

		//check to makesure that there are no other objects 

		output = false;
	}

	return output;
}


int world::place_cart(loc<int>& location) {
	bool placable = can_place_cart(location);
	int output = -1;
	if (placable) {
		output = rail_mgr.place_cart(location);

		if (output != -1) {

			item_info* temp = OBJM->spawn_item(CART, location.x, location.y, location.z);

			//yes I know that this is not the best, but it can be optimised latter
			for (int i = 0; i < rail_mgr.carts.size(); i++) {
				if (rail_mgr.carts[i] == output) {
					rail_mgr.carts[i].cart_obj = temp;
					std::cout << "linked the obj with teh cart" << std::endl;
					break;
				}
			}
		}
		else {
			std::cout << "railroad mgr failed to create a cartt object" << std::endl;
		}
	}
	else {
		std::cout << "fail to place cart" << std::endl;
	}
	return output;
}

bool world::can_place_cart(loc<int>& location) {
	return rail_mgr.can_place_cart(location);
}

void world::toggle_cart(int id) {
	rail_mgr.toggle_cart(id);
}

void world::prin_rail_info() {
	rail_mgr.print_info();
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