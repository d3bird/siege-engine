#include "aircraft.h"

aircraft::aircraft(int id) {
	ID = id;
	obj = NULL;
	current_route = NULL;
	angle_speed = 30;
	move_speed = 5;
}

aircraft::~aircraft() {

}


bool aircraft::operator==(const int& id) {
	return ID == id;
}


void aircraft::set_location(loc<int> alocation) {
	location = alocation;
	if (obj != NULL) {
		obj->x_m = location.x * 2;
		obj->y_m = location.y * 2;
		obj->z_m = location.z * 2;
	}
}

double aircraft::get_move_speed(double distance, double angle_change_req) {
	double output = move_speed;

	if(angle_change_req >=120){
		output /= 2;
	}
	else if (angle_change_req >= 90) {
		output /= 2;

	}
	else if (angle_change_req >= 60) {
		output /= 2;

	}
	else if (angle_change_req >= 30) {
		//output /= 4;

	}
	/*else if(distance >= 10) {
		output *= 1.5;
	}*/

	return output;
}


double aircraft::get_angle_speed(double distance, double angle_change_req) {
	double output = angle_speed;

	if (angle_change_req >= 120) {
		output *= 5;
	}
	else if (angle_change_req >= 90) {
		output *= 4;

	}
	else if (angle_change_req >= 60) {
		output *= 3;

	}
	else if (angle_change_req >= 30) {
		output *= 2;

	}

	return output;
}

void aircraft::update_model_loc(const loc<double>& alocation, double asangle) {
	current_location = alocation;
	angle = asangle;

	obj->x_m = current_location.x;
	obj->y_m = current_location.y;
	obj->z_m = current_location.z;
	obj->angle = angle;
}

void aircraft::update_model_loc_from_saved() {
	obj->x_m = current_location.x;
	obj->y_m = current_location.y;
	obj->z_m = current_location.z;
	obj->angle = angle;
}
