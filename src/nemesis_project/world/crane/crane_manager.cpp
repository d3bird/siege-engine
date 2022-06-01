#include "crane_manager.h"

#include <iostream>

crane_manager::crane_manager(motion_manger* mm) {
	ID_max = 0;
	updater = mm;
}

crane_manager::~crane_manager() {

}

void crane_manager::update(double detlaTime) {

	//std::cout << "crane: " << detlaTime << std::endl;
	crane* active = NULL;
	for (int i = 0; i < cranes.size(); i++) {
		active = cranes[i];
		if (active->is_running() && active->is_aproaching_dest()) {
			active->update(detlaTime);
			for (int i = 0; i < active->arm.size(); i++) {
				updater->update_item(active->arm[i]);
			}
		}
		//else {
		//	if (!active->is_running()) {
		//		std::cout << active->get_ID() << " is not ruinning" << std::endl;
		//	}
		//	if (!active->is_aproaching_dest()) {
		//		std::cout << active->get_ID() << " is not aproaching_dest" << std::endl;
		//	}
		//	//std::cout << "not ready to update" << std::endl;
		//}
	}

}

crane* crane_manager::create_crane(loc<int>location, int height, int radus) {
	std::cout << height << "," << radus << std::endl;
	crane* new_crane = new crane(height, radus, location, ID_max);
	ID_max++;

	cranes.push_back(new_crane);
	return new_crane;
}


void crane_manager::toggle_crane(int id) {

	for (int i = 0; i < cranes.size(); i++) {
		if (cranes[i]->get_ID() == id) {
			cranes[i]->set_aproaching_dest(true);
			cranes[i]->set_running(true);
			std::cout << "found crane to toggle" << std::endl;
			break;
		}
	}

}
