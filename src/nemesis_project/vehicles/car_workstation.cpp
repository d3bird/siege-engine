#include "car_workstation.h"

car_workstation::car_workstation(int id) {
	ID = id;
	item_info* lift = NULL;
	item_info* leaver = NULL;

	start_pos = -1;
	end_pos = -1;
	orginal = -1;
	need_to_set_pos = true;

	speed = 3;
	direction = true;
}


car_workstation::~car_workstation(){

}

void car_workstation::update(double time) {
	if (need_to_set_pos) {
		if (leaver != NULL) {
			start_pos = leaver->y_m;
			orginal = leaver->y_m;
			end_pos = start_pos +3;
			need_to_set_pos = false;
			std::cout << "setting the possitions" << std::endl;
		}
	}
	else {

		double change = speed * time;

		if (direction) {
			lift->y_m += change;

			if (lift->y_m >= end_pos) {
				lift->y_m = end_pos;
				direction = false;
				std::cout << "switching directions" << std::endl;
			}
		}
		else {
			lift->y_m -= change;

			if (lift->y_m <= start_pos) {
				lift->y_m = start_pos;
				direction = true;
				std::cout << "switching directions" << std::endl;
			}
		}

		if (mounted_vehicle != NULL) {
			loc<double> new_location = mounted_vehicle->get_obj_cords();
			new_location.y = lift->y_m;
			mounted_vehicle->update(new_location);
		}

	}
}
