#include "bulk_head_door.h"

#include "../../utility/math/utility_math.h"
#include <iostream>

bulk_head_door::bulk_head_door() :
	door_objs(NULL), x_size(-1), z_size(-1),
	m_is_open(false), m_openeing(true), m_move_speed(10),
	m_open_y_axis(false), m_open_dir(false)
{
}

bulk_head_door::~bulk_head_door()
{
}

void bulk_head_door::update(double time) {

	if (door_objs != NULL) {
		
		double change = time * m_move_speed;
		bool mark_open = false;
		bool mark_close = false;
		for (int x = 0; x < x_size; x++) {
			for (int z = 0; z < z_size; z++) {
				
				if (m_openeing) {

					if (m_open_y_axis) {
						door_objs[x][z].current_location.y += change;;
						if (door_objs[x][z].current_location.y >= door_objs[x][z].open_location.y) {
							door_objs[x][z].current_location.y = door_objs[x][z].open_location.y;
							mark_open = true;
						}
					}
					else {
						std::cout << "door does not open on this axises" << std::endl;
					}

				}
				else if(m_closing) {
					if (m_open_y_axis) {
						door_objs[x][z].current_location.y -= change;;
						if (door_objs[x][z].current_location.y <= door_objs[x][z].close_location.y) {
							door_objs[x][z].current_location.y = door_objs[x][z].close_location.y;
							mark_close = true;
						}
					}
					else {
						std::cout << "door does not close on this axises" << std::endl;
					}
				}
				
			}
		}
		if (mark_open) {
			m_is_open = true;
			m_openeing = false;
			m_is_close = false;
			m_closing = false;
			//std::cout << "door was marked as open" << std::endl;
		}
		else if (mark_close) {
			m_is_close = true;
			m_closing = false;
			m_is_open = false;
			m_openeing = false;
			//std::cout << "door was marked as closed" << std::endl;
		}
		set_models();
	}

}

void bulk_head_door::create_door(loc<int> start, loc<int> end, bool y_axis, bool dir1) {
	if (door_objs == NULL) {

		m_open_y_axis = y_axis;
		m_open_dir = dir1;

		int x_diff = abs(start.x - end.x);
		int y_diff = abs(start.y - end.y);
		int z_diff = abs(start.z - end.z);

		std::cout << "creating bulk head door" << std::endl;
		std::cout << "x_diff: " << x_diff << std::endl;
		std::cout << "y_diff: " << y_diff << std::endl;
		std::cout << "z_diff: " << z_diff << std::endl;

		if (x_diff != 0 &&
			y_diff != 0 &&
			z_diff != 0) {
			std::cout << "failed to create bulkhead door" << std::endl;
			return;
		}

		//axies information
		int x_eq_axies = -1;
		int z_eq_axies = -1;

		if (x_diff != 0) {
			x_size = x_diff;
			x_eq_axies = 0;
		}

		if (y_diff != 0) {
			if (x_size == -1) {
				x_size = y_diff;
				x_eq_axies = 1;
			}
			else {
				z_size = y_diff;
				z_eq_axies = 1;
			}
		}

		if (z_diff != 0) {
			if (x_size == -1) {
				x_size = z_diff;
				x_eq_axies = 2;
			}
			else if(z_size ==-1) {
				z_size = z_diff;
				z_eq_axies = 2;
			}
		}

		if (x_size == -1 || z_size == -1) {
			std::cout << "failed to set door size" << std::endl;
			return;
		}

		std::cout << "x_eq_axies " << x_eq_axies << std::endl;
		std::cout << "z_eq_axies " << z_eq_axies << std::endl;

		if (x_eq_axies > 2 || x_eq_axies < 0 ||
			z_eq_axies >2 || z_eq_axies < 0 || 
			x_eq_axies == z_eq_axies) {
			std::cout << "failed to set door axiese information" << std::endl;
			return;
		}

		//create the data structure
		door_objs = new door_section * [x_size];
		for (int x = 0; x < x_size; x++) {
			door_objs[x] = new door_section[z_size];
		}

		//set the location information
		for (int x = 0; x < x_size; x++) {
			for (int z = 0; z < z_size; z++) {
				loc<int> temp_loc = start;

				if (x_eq_axies == 0) {
					temp_loc.x += x;
				}
				else if (x_eq_axies == 1) {
					temp_loc.y +=x;
				}
				else if (x_eq_axies == 2) {
					temp_loc.z += x;
				}

				if (z_eq_axies == 0) {
					temp_loc.x += z;
				}
				else if (z_eq_axies == 1) {
					temp_loc.y += z;
				}
				else if (z_eq_axies == 2) {
					temp_loc.z += z;
				}


				door_objs[x][z].close_location = loc<double>(temp_loc.x * 2, temp_loc.y * 2, temp_loc.z * 2);
				door_objs[x][z].current_location = door_objs[x][z].close_location;

				if (m_open_y_axis) {
					if (m_open_dir) {
						temp_loc.y += y_diff;
					}
					else {
						std::cout << "NO CLOSE POSITION DEFINED FOR THIS DOOR DIR" << std::endl;
					}
				}
				else {
					std::cout << "NO CLOSE POSITION DEFINED FOR THIS DOOR" << std::endl;
				}

				door_objs[x][z].open_location = loc<double>(temp_loc.x*2, temp_loc.y*2, temp_loc.z*2);
			}
		}

	}
}

void bulk_head_door::set_models() {
	if (door_objs != NULL) {
		for (int x = 0; x < x_size; x++) {
			for (int z = 0; z < z_size; z++) {
				if (door_objs[x][z].obj != NULL) {
					door_objs[x][z].obj->x_m = door_objs[x][z].current_location.x;
					door_objs[x][z].obj->y_m = door_objs[x][z].current_location.y;
					door_objs[x][z].obj->z_m = door_objs[x][z].current_location.z;
					door_objs[x][z].obj->angles = door_objs[x][z].angle;
				}
				else {
					std::cout << "obj was NULL?" << std::endl;
				}
			}
		}
	}
	else {
		std::cout << "door was NULL" << std::endl;
	}
}

bool bulk_head_door::is_open() {
	return m_is_open;
}

bool bulk_head_door::is_moving() {
	return m_openeing || m_closing;
}

bool bulk_head_door::is_closing() {
	return m_closing;
}

bool bulk_head_door::is_openeing() {
	return m_openeing;
}

void bulk_head_door::open_door() {
	m_openeing = true;
	m_closing = false;
}

void bulk_head_door::close_door() {
	m_openeing = false;
	m_closing = true;
}