#include "door_manager.h"

#include <iostream>

namespace door_data {

	door_manager::door_manager() {
		ID_index = 0;
	}

	door_manager::~door_manager() {

	}

	door* door_manager::place_door(opening type, int x_start, int y_start, int z_start,
		int x_end, int y_end, int z_end) {

		return NULL;
	}

	door* door_manager::get_door(int index) {

		if (index >= 0 && index < doors.size()) {
			return doors[index];
		}
		else {
			return NULL;
		}

	}

}