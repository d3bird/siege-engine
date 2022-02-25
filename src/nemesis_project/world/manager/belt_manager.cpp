#include "belt_manager.h"

#include <iostream>

belt_manager::belt_manager(){
	ID_index = 0;
}

belt_manager::~belt_manager(){

}

int belt_manager::place_belt(int x, int y, int z, int dir) {
	int output = -1;
	
	loc temp_loc(x, y, z);

	auto found = belts.find(temp_loc);

	if (found == belts.end()) {
		std::cout << "the given location doe not have belt, but will now" << std::endl;
	}
	
	//if (!does_belt_exist(temp_loc)) {
	//	belt* new_b = new belt(ID_index, dir, x, y, z);
	//	ID_index++;

	//}

	return output;
}

bool belt_manager::does_belt_exist(belt* test) {
	//if (test == NULL) {
		return false;
	//}
	//else {
	//	int index = test->ID;
	//	if (index >= 0 && index < belts.size() && !test->old) {
	//		return *test == *belts[index];
	//	}
	//	else {
	//		return false;
	//	}
	//}
}

bool belt_manager::does_belt_exist(loc test) {
	//for the vecotr
	//for (int i = 0; i < belts.size(); i++) {
	//	if (belts[i] != NULL && !belts[i]->old) {
	//		if (test == belts[i]->location) {
	//			return true;
	//		}
	//	}
	//}
	return false;
}
