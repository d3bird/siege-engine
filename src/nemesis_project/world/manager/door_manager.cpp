#include "door_manager.h"

#include <iostream>

namespace door_data {

	door_manager::door_manager() {
		ID_index = 0;
	}

	door_manager::~door_manager() {
		for (int i = 0; i < doors.size(); i++) {
			delete_door(doors[i]);
		}
		doors.clear();
	}

	door* door_manager::place_door(opening type, int x_start, int y_start, int z_start,
		int x_end, int y_end, int z_end) {

		std::cout << "creating a door" << std::endl;

		door* output = NULL;

		bool given_right_inputs = false;

		bool x_open = is_x_opening(x_start, y_start, z_start, x_end, y_end, z_end);
		bool y_open = is_y_opening(x_start, y_start, z_start, x_end, y_end, z_end);
		bool z_open = is_z_opening(x_start, y_start, z_start, x_end, y_end, z_end);

		int openings_found = 0;

		if (x_open) {
			openings_found++;
			std::cout << "found x opening" << std::endl;
		}

		if (y_open) {
			openings_found++;
			std::cout << "found y opening" << std::endl;
		}

		if (z_open) {
			openings_found++;
			std::cout << "found z opening" << std::endl;
		}

		std::cout << "openings_found: "<< openings_found << std::endl;
		if (openings_found == 1) {
			given_right_inputs = true;
		}

		if (given_right_inputs) {

			std::cout << "met requirements to make a door" << std::endl;

			output = new door;
			output->open = false;
			output->ID = ID_index;
			ID_index++;
			output->type = type;

			output->x_start = x_start;
			output->y_start = y_start;
			output->z_start = z_start;

			output->x_end = x_end;
			output->y_end = y_end;
			output->z_end = z_end;

			//set the boundry based on the opening direction
			if (x_open) {
				output->ar_x = y_end - y_start;
				output->ar_z = z_end - z_start;

			}
			else if (y_open) {
				output->ar_x = x_end - x_start;
				output->ar_z = z_end - z_start;
			}
			else {
				output->ar_x = y_end - y_start;
				output->ar_z = x_end - x_start;
			}

			//create the data structure
			output->d_sec = new d_sec * [output->ar_x];
			for (int i = 0; i < output->ar_x; i++) {
				output->d_sec[i] = new d_sec[output->ar_z];
			}

			//populate the structure
			for (int x = 0; x < output->ar_x; x++) {
				for (int z = 0; z < output->ar_z; z++) {
					output->d_sec[x][z].angle = 0;
					output->d_sec[x][z].need_update = false;

					int x_start = -1;
					int y_start = -1;
					int z_start = -1;

					int x_end = -1;
					int y_end = -1;
					int z_end = -1;

					if (x_open) {
						//output->ar_x = y_end - y_start;
						//output->ar_z = z_end - z_start;
						x_start = output->x_start;
						y_start = output->y_start + x;
						z_start = output->z_start + z;

						x_end = output->x_start;
						y_end = output->y_end;
						z_end = output->z_end;

						output->d_sec[x][z].angle = 90;
					}
					else if (y_open) {
						//output->ar_x = x_end - x_start;
						//output->ar_z = z_end - z_start;
						x_start = output->x_start + x;
						y_start = output->y_start;
						z_start = output->z_start + z;

						x_end = output->x_end;
						y_end = output->y_start;
						z_end = output->z_end;

					}
					else {
						//output->ar_x = y_end - y_start;
						//output->ar_z = x_end - x_start;
						x_start = output->x_start+ z;
						y_start = output->y_start + x;
						z_start = output->z_start;

						x_end = output->x_end;
						y_end = output->y_end;
						z_end = output->z_start;
					}

					//the possition in the grid
					output->d_sec[x][z].x_start = x_start;
					output->d_sec[x][z].y_start = y_start;
					output->d_sec[x][z].z_start = z_start;

					//the location that is will end
					//the opening type should change this
					output->d_sec[x][z].x_end = x_end;
					output->d_sec[x][z].y_end = y_end;
					output->d_sec[x][z].z_end = z_end;

					output->d_sec[x][z].x_current = output->d_sec[x][z].x_start;
					output->d_sec[x][z].y_current = output->d_sec[x][z].y_start;
					output->d_sec[x][z].z_current = output->d_sec[x][z].z_start;

				}
			}

			doors.push_back(output);
		}
		std::cout << "done creating a door" << std::endl;
		return output;
	}

	door* door_manager::get_door(int index) {

		if (index >= 0 && index < doors.size()) {
			return doors[index];
		}
		else {
			return NULL;
		}

	}

	//helper functions

	bool door_manager::is_y_opening(int x_start, int y_start, int z_start,
		int x_end, int y_end, int z_end) {
		if (y_start == y_end) {
			return (x_start != x_end && z_start != z_end);
		}
		return false;
	}

	bool door_manager::is_x_opening(int x_start, int y_start, int z_start,
		int x_end, int y_end, int z_end) {
		if (x_start == x_end) {
			return (y_start != y_end && z_start != z_end);
		}
		return false;
	}

	bool door_manager::is_z_opening(int x_start, int y_start, int z_start,
		int x_end, int y_end, int z_end) {
		if (z_start == z_end) {
			return (y_start != y_end && x_start != x_end);
		}
		return false;
	}

	void door_manager::delete_door(door* input) {
		if (input != NULL) {

			if (input->d_sec != NULL) {

				bool check_item_data = false;

				int ar_x = input->ar_x;
				int ar_z = input->ar_z;

				if (check_item_data) {
					for (int x = 0; x < ar_x; x++) {
						for (int z = 0; z < ar_z; z++) {
							if (input->d_sec[x][z].door_sec != NULL) {
								std::cout << "ther is a dorr section being deleted and the object is still attached" << std::endl;
							}
						}
					}
				}

				for (int x = 0; x < ar_x; x++) {
					delete[] input->d_sec[x];
				}
				delete[] input->d_sec;
			}
			delete input;
		}
	}


}