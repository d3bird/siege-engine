#include "rail_manager.h"

#include <iostream>

railRoad::rail_manager::rail_manager(motion_manger* mm) {
	cart_id = 0;
	rail_id = 0;
	MM = mm;
}

railRoad::rail_manager::~rail_manager() {
	old_IDs.clear();
	rails.clear();
	carts.clear();
}

void railRoad::rail_manager::update(double deltaTime) {
	//std::cout << deltaTime << std::endl;

	for (int i = 0; i < carts.size(); i++) {
		if (carts[i].is_running()) {
			carts[i].update(deltaTime);
			//carts[i].cart_obj->x_m += (5 * deltaTime);
			MM->update_item(carts[i].cart_obj);
		}
	}

}

int railRoad::rail_manager::can_place_cart(loc<int>& location) {
	int output = 0;
	for (int i = 0; i < rails.size(); i++) {

	//	std::cout << rails[i]->get_loc().x<<","<< rails[i]->get_loc().y<<","<<rails[i]->get_loc().z
	//		<< " == " << location.x<<","<< location.y<<","<< location.z << std::endl;
		if (rails[i]->get_loc() == location) {
		
			if (rails[i]->get_axais()) {
				output = 1;
			}
			else {
				output = 2;
			}

		}
	}
	return output;
}

int railRoad::rail_manager::place_cart(loc<int>& location) {

	for (int i = 0; i < rails.size(); i++) {
		if (rails[i]->get_loc() == location) {
			//railRoad::cart temp(cart_id, rails[i]);
			carts.push_back(railRoad::cart(cart_id,(rails[i])));
			cart_id++;
		//	std::cout << "adding a cart to the vector" << std::endl;
			return cart_id - 1;
		}
	}

	return -1;
}

void railRoad::rail_manager::toggle_cart(int id) {

	for (int i = 0; i < carts.size(); i++) {
		if (carts[i] == id) {
			std::cout << "toggling cart: "<<id << std::endl;
			//carts[i].set_velocity(10);
			carts[i].set_running(true);
			return;
		}
	}

}

void  railRoad::rail_manager::set_cart_vel(int id, double velocity) {
	for (int i = 0; i < carts.size(); i++) {
		if (carts[i] == id) {
			carts[i].set_velocity(velocity);
			return;
		}
	}
}


bool railRoad::rail_manager::add_rail(int x, int y, int z, bool x_axis) {
	return add_rail(loc<int>(x,y,z), x_axis);
}

bool railRoad::rail_manager::remove_rail(int x, int y, int z) {
	return remove_rail(loc<int>(x, y, z));;
}

bool railRoad::rail_manager::add_rail(loc<int>& location, bool x_axis) {

	rail* temp = new rail(rail_id, location, railRoad::STRAIGHT, x_axis);

	//std::cout << "rail_id: " << rail_id << std::endl;

	//connect to the other rails
	int connections = 0;
	for (int i = 0; i < rails.size(); i++) {
		if (temp->can_connect(rails[i], true)) {
			connections++;
			if (connections == 2) {
				//std::cout << "connect to two rails" << std::endl;
				break;
			}
		}
	}

	/*if (connections == 0) {
		std::cout << "failed to make connections" << std::endl;
	}
	else if (connections == 1) {
		std::cout << "made one connection" << std::endl;
	}*/

	rails.push_back(temp);
	rail_id++;

	return true;
}

bool railRoad::rail_manager::remove_rail(loc<int>& location) {
	return false;

}

void railRoad::rail_manager::print_info() {
	std::cout << "print out railroad info" << std::endl;
	std::cout << "carts: " << carts.size() << std::endl;
	std::cout << "rails: " << rails.size() << std::endl;

	int connection1 = 0;
	int connection2 = 0;
	int connection0 = 0;

	for (int i = 0; i < rails.size(); i++) {
			int temp = 0;
		if (rails[i]->get_connection1() != NULL) {
			temp++;
		}
		if (rails[i]->get_connection2() != NULL) {
			temp++;
		}
		if (temp == 1) {
			connection1++;
		}
		else if (temp == 2) {
			connection2++;
		}
		else {
			connection0++;
		}
	}

	std::cout << "0 connection:" << connection0 << std::endl;
	std::cout << "1 connection:" << connection1 << std::endl;
	std::cout << "2 connection:" << connection2 << std::endl;

	return;
	//print all the rails
	for (int i = 0; i < rails.size(); i++) {
		std::cout << "rail: "<<i<<" " << rails[i]->get_x()<<" " << rails[i]->get_z()<< std::endl;
	}
}


void railRoad::rail_manager::check_for_bad_connections() {
	int null = 0;
	int wrong_axis = 0;
	int too_far = 0;
	int straight = 0;
	for (int i = 0; i < rails.size(); i++) {
		if (rails[i] == NULL) {
			null++;
		}
		else {
			if (rails[i]->get_type() == railRoad::STRAIGHT) {
				straight++;
				rail* con1 = rails[i]->get_connection1();
				rail* con2 = rails[i]->get_connection2();

				if (con1 != NULL) {
					int x1 = con1->get_x();
					int y1 = con1->get_y();
					int z1 = con1->get_z();

					int x0 = rails[i]->get_x();
					int y0 = rails[i]->get_y();
					int z0 = rails[i]->get_z();

					if (rails[i]->get_axais() != con1->get_axais()) {
						wrong_axis++;
					}
					else {

						if (rails[i]->get_axais()) {

						}
						else {

						}

					}


				}
			}
		}
	}

}

void  railRoad::rail_manager::print_rail_connections() {

}