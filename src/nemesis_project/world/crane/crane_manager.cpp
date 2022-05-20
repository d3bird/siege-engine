#include "crane_manager.h"

#include <iostream>

crane_manager::crane_manager() {
	ID_max = 0;
}

crane_manager::~crane_manager() {

}

void crane_manager::update(double detlaTime) {

	//std::cout << "crane: " << detlaTime << std::endl;
	crane* active;
	for (int i = 0; i < cranes.size(); i++) {
		active = cranes[i];
		if (active->is_running() && active->is_aproaching_dest()) {
			active->update(detlaTime);
		}
	}

}

crane* crane_manager::create_crane(int height, int radus) {
	std::cout << height << "," << radus << std::endl;
	crane* new_crane = new crane(height, radus, ID_max);
	ID_max++;

	cranes.push_back(new_crane);
	return new_crane;
}


void crane_manager::toggle_crane(int id) {

	for (int i = 0; i < cranes.size(); i++) {
		if (cranes[i]->get_ID() == id) {
			std::cout << "found crane to goggle" << std::endl;
			break;
		}
	}

}
