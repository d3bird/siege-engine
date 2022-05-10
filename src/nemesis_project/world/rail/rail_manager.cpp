#include "rail_manager.h"

railRoad::rail_manager::rail_manager() {

}

railRoad::rail_manager::~rail_manager() {

}

bool railRoad::rail_manager::can_place_cart(loc<int>& location) {

	for (int i = 0; i < rails.size(); i++) {
		if (rails[i].get_loc() == location) {
			return true;
		}
	}

	return false;
}

bool railRoad::rail_manager::can_place_rail(loc<int>& location) {
	return true;
}

bool railRoad::rail_manager::add_rail(int x, int y, int z) {
	return add_rail(loc<int>(x,y,z));
}

bool railRoad::rail_manager::remove_rail(int x, int y, int z) {
	return remove_rail(loc<int>(x, y, z));;
}

bool railRoad::rail_manager::add_rail(loc<int>& location) {
	return false;

}

bool railRoad::rail_manager::remove_rail(loc<int>& location) {
	return false;

}