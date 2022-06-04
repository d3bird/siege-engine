#include "environment.h"

environment::environment(optimized_spawner* os, motion_manger* mm) :crane_mgr(mm) {
	spawner = os;
	updater = mm;
}

environment::~environment(){

}

void environment::update(double time_change) {
	crane_mgr.update(time_change);
}



int environment::place_crane(const loc<int>& location, int height, int radius) {
	int output = -1;
	item_info* temp = 0;

	std::cout << "creating crane" << std::endl;

	std::cout << height << " , " << radius << std::endl;

	crane* new_crane = crane_mgr.create_crane(location, height, radius);
	if (new_crane == NULL) {
		std::cout << "failed creating crane" << std::endl;
		return output;
	}

	//make the central pillar
	for (int i = 0; i < height; i++) {
		temp = spawner->spawn_item(CRANE_B, location.x, location.y + i, location.z);
		if (temp != NULL) {
			new_crane->base.push_back(temp);
		}
	}

	//make the arm
	for (int i = location.x - 1; i < radius + location.x - 1; i++) {
		temp = spawner->spawn_item(CUBE_T, i, location.y + height - 2, location.z);
		if (temp != NULL) {
			new_crane->arm.push_back(temp);
		}
	}

	//make the attachment
	temp = spawner->spawn_item(CUBE_T, 0, location.y + height - 2, location.z);
	if (temp != NULL) {
		new_crane->attachment = (temp);
	}

	new_crane->set_running(true);
	new_crane->set_aproaching_dest(true);
	new_crane->print_info();

	std::cout << "done creating crane" << std::endl;

	return output;
}


void environment::toggle_crane(int id) {
	crane_mgr.toggle_crane(id);
}


crane* environment::get_crane(int id) {
	return crane_mgr.get_crane(id);
}
