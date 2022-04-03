#include "mobil_platform.h"

mobil_platform::mobil_platform() {
	map_info = NULL;

	double velocity = 0;
	double velocity_max = 20;
	angle = 0;
	moving = false;
}

mobil_platform::~mobil_platform() {

}

void mobil_platform::update(float delta_time) {

	if (moving) {
		update_pos(delta_time);
	}
}

void mobil_platform::update_pos(float delta_time) {

	if (map_info != NULL && velocity != 0) {
		update_pak pak;

		double change = velocity * delta_time;
		for (int y = 0; y < map_info->y_size; y++) {
			for (int x = 0; x < map_info->x_size; x++) {
				for (int z = 0; z < map_info->z_size; z++) {



					if (map_info->map[y][x][z].ground != NULL) {
						pak.x = map_info->map[y][x][z].ground->x_m;
						pak.y = map_info->map[y][x][z].ground->y_m;
						pak.z = map_info->map[y][x][z].ground->z_m;

						pak.x_scale = 1;
						pak.y_scale = 1;
						pak.z_scale = 1;

						pak.angle = map_info->map[y][x][z].ground->angle;

						pak.buffer_loc = map_info->map[y][x][z].ground->buffer_loc;
						pak.item_id = map_info->map[y][x][z].ground->item_id;

						spawner->update_item_matrix(&pak);
					}
					if (map_info->map[y][x][z].floor != NULL) {

					}
				}
			}
		}
	}

}


void mobil_platform::increase_velocity(bool forward) {
	moving = true;
	if (forward) {
		
		if (velocity + 1 > velocity_max) {
			std::cout << "at max speed" << std::endl;
		}
		else {
			velocity += 1;
		}
	}
	else {
		if (velocity - 1 <= 0) {
			std::cout << "at a stop" << std::endl;
			moving = false;
		}
		else {
			velocity -= 1;
		}
	}
}

void mobil_platform::change_angle(double delta_angle) {
	if (delta_angle + angle > 360) {
		angle = delta_angle + angle - 360;
	}
	else if (delta_angle + angle < 0) {
		angle = 360- (delta_angle + angle);
	}
	else {
		angle += delta_angle;
	}
}


void mobil_platform::move_plat_to_loc(loc_i<double> location) {
}


void mobil_platform::init(optimized_spawner* spawn) {
	spawner = spawn;

}