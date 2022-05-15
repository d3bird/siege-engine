#include "rail_manager.h"

#include <iostream>

railRoad::rail_manager::rail_manager() {
	cart_id = 0;
	rail_id = 0;
}

railRoad::rail_manager::~rail_manager() {
	old_IDs.clear();
	rails.clear();
	carts.clear();
}

void railRoad::rail_manager::update(double deltaTime) {


}

bool railRoad::rail_manager::can_place_cart(loc<int>& location) {

	for (int i = 0; i < rails.size(); i++) {

	//	std::cout << rails[i].get_loc().x<<","<< rails[i].get_loc().y<<","<<rails[i].get_loc().z
	//		<< " == " << location.x<<","<< location.y<<","<< location.z << std::endl;
		if (rails[i].get_loc() == location) {
			return true;
		}
	}
	return false;
}

int railRoad::rail_manager::place_cart(loc<int>& location) {

	for (int i = 0; i < rails.size(); i++) {
		if (rails[i].get_loc() == location) {
			railRoad::cart temp(cart_id, rails[i]);
			cart_id++;
			return cart_id - 1;
		}
	}

	return -1;
}

void railRoad::rail_manager::toggle_cart(int id) {

	for (int i = 0; i < carts.size(); i++) {
		if (carts[i] == id) {
			std::cout << "toggling cart: "<<id << std::endl;
			return;
		}
	}

}


bool railRoad::rail_manager::add_rail(int x, int y, int z) {
	return add_rail(loc<int>(x,y,z));
}

bool railRoad::rail_manager::remove_rail(int x, int y, int z) {
	return remove_rail(loc<int>(x, y, z));;
}

bool railRoad::rail_manager::add_rail(loc<int>& location) {

	rail temp(rail_id, location);

	//std::cout << "rail_id: " << rail_id << std::endl;

	//connect to the other rails
	int connections = 0;
	for (int i = 0; i < rails.size(); i++) {
		if (temp.can_connect(&rails[i], true)) {
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
		if (rails[i].get_connection1() != NULL) {
			temp++;
		}
		if (rails[i].get_connection2() != NULL) {
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

}
