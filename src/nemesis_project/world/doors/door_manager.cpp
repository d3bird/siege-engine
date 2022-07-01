#include "door_manager.h"

door_manager::door_manager(motion_manger* mm) : updater(mm)
{
}

door_manager::~door_manager()
{
}

void door_manager::update(double time) {
	for (int i = 0; i < doors.size(); i++) {
		doors[i]->update(time);
		if (!doors[i]->is_moving()) {
			if (doors[i]->is_open()) {
				doors[i]->close_door();
			}
			else {
				doors[i]->open_door();
			}
		}
		for (int x = 0; x < doors[i]->x_size; x++) {
			for (int z = 0; z < doors[i]->z_size; z++) {
				updater->update_item(doors[i]->door_objs[x][z].obj);
			}
		}
	}
}

void door_manager::spawn_bulk_head_door(loc<int> start, loc<int> end, bool y_axis, bool dir1, optimized_spawner* spawner) {
	bulk_head_door* door = new bulk_head_door();
	door->create_door(start, end, y_axis, dir1);

	int x_size = door->x_size;
	int z_size = door->z_size;

	for (int x = 0; x < x_size; x++) {
		for (int z = 0; z < z_size; z++) {
			if (x == 0 && z == 0 ||
				x == x_size-1 && z == 0 ||
				x == 0 && z == z_size-1 ||
				x == x_size-1 && z == z_size-1) {
				door->door_objs[x][z].obj = spawner->spawn_item(BULK_D_MID_TRACK, -1, -1, -1);
			}
			else {
				door->door_objs[x][z].obj = spawner->spawn_item(BULK_D_MID, -1, -1, -1);
			}
		}
	}
	door->set_models();
	for (int x = 0; x < door->x_size; x++) {
		for (int z = 0; z < door->z_size; z++) {
			updater->update_item(door->door_objs[x][z].obj);
		}
	}
	doors.push_back(door);
}

void door_manager::open_door(int ID) {

}

void door_manager::close_door(int ID) {

}

bool door_manager::is_door_open(int ID) {
	return false;
}