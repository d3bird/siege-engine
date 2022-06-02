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
			updater->update_item(active->attachment);
		}
		else {
			if (!active->is_running()) {
			//	std::cout << active->get_ID() << " is not ruinning" << std::endl;
			}
			if (!active->is_aproaching_dest()) {
			//	std::cout << active->get_ID() << " is not aproaching_dest" << std::endl;
				create_rand_dest(active);
			}
			//std::cout << "not ready to update" << std::endl;
		}
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

std::vector<loc<int> >  crane_manager::get_converate(int id, int y) {
	std::vector<loc<int> > output;
	crane* input =get_crane(id);

	if (input != NULL) {
		for (int x = 0; x < 20; x++) {
			for (int z = 0; z < 20; z++) {
				loc<int> new_dest(x, y, z);
				if (input->can_reach_dest(new_dest)) {
					output.push_back(new_dest);
				}
			}
		}
	}

	return output;
}

//these functions are only for testing

#include <stdio.h>
#include <stdlib.h>
#include<time.h>

void crane_manager::create_rand_dest(crane* input) {
	std::cout << "setting new destination for "<< input->get_ID() << std::endl;

	srand(time(0));

	loc<int> destination = input->get_location();
	int radius = input->get_radius();

	int x = rand() % radius;
	int z = rand() % radius;

	destination.x += x;
	destination.z += z;

	bool result = input->set_dest(destination);

	if (!result) {
		std::cout << "failed to create a new destination" << std::endl;
		std::cout << "dest: "<<destination.x << " " << destination.z << std::endl;
		std::cout << "dest: " << input->get_location().x << " " << input->get_location().z << std::endl;
	}

}

crane* crane_manager::get_crane(int id) {

	for (int i = 0; i < cranes.size(); i++) {
		if (cranes[i]->get_ID() == id) {
			return cranes[i];
		}
	}
	return NULL;
}