#include "farm_zone.h"


farm_zone::farm_zone(std::string n):zone(n, FARM) {
	std::cout << "farm_zone farm zone" << std::endl;
}

int farm_zone::add_spot_to_zone(int x, int y, int z) {
	std::cout << "add_spot_to_zone farm zone (" << x << "," << y << "," << z << ")" << std::endl;

	return zone::add_spot_to_zone(x, y, z);
}

void farm_zone::remove_spot_from_zone(int x, int y, int z) {
	std::cout << "remove_spot_from_zone farm zone (" << x << "," << y << "," << z << ")" << std::endl;

	zone::remove_spot_from_zone(x, y, z);

}

//int farm_zone::get_interaction_spot(actions act, item_info* obj) {
//	std::cout << "get_interaction_spot farm zone" << std::endl;
//	return -1;
//
//}

void farm_zone::update() {
	std::cout << "updating farm zone" << std::endl;
}