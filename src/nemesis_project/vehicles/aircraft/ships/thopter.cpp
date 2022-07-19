#include "thopter.h"

thopter::thopter(int id) : fuel(10, 1),
	ID(id),
	base(NULL), fl_wing(NULL), fr_wing(NULL), bl_wing(NULL), br_wing(NULL),
	current_route(NULL),
	angle_speed(30),
	move_speed(5),
	angle()
{

}

thopter::~thopter() {

}


bool thopter::operator==(const int& id) {
	return ID == id;
}

int thopter::get_ID() { 
	return ID; 
}

loc<int> thopter::get_location() {
	return location;
}

double thopter::get_move_speed_static() { 
	return move_speed;
}

double thopter::get_angle_speed_static() {
	return angle_speed;
}

void thopter::set_location(loc<int> alocation) {
	location = alocation;
	current_location = location;
	
	update_model_loc_from_saved();
}

double thopter::get_move_speed(double distance, double angle_change_req) {
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


double thopter::get_angle_speed(double distance, double angle_change_req) {
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

void thopter::update_model_loc(const loc<double>& alocation,const rendering::rotation& asangle) {
	current_location = alocation;
	angle = asangle;

	update_model_loc_from_saved();
}

void thopter::update_model_loc_from_saved() {

	if (base != NULL) {
		base->x_m = current_location.x;
		base->y_m = current_location.y;
		base->z_m = current_location.z;
		base->angles = angle;
	}


	if (fl_wing != NULL) {
		fl_wing->x_m = current_location.x;
		fl_wing->y_m = current_location.y;
		fl_wing->z_m = current_location.z;
		fl_wing->angles = angle;
	}

	if (fr_wing != NULL) {
		fr_wing->x_m = current_location.x;
		fr_wing->y_m = current_location.y;
		fr_wing->z_m = current_location.z;
		fr_wing->angles = angle;
	}

	if (bl_wing != NULL) {
		bl_wing->x_m = current_location.x;
		bl_wing->y_m = current_location.y;
		bl_wing->z_m = current_location.z;
		bl_wing->angles = angle;
	}

	if (br_wing != NULL) {
		br_wing->x_m = current_location.x;
		br_wing->y_m = current_location.y;
		br_wing->z_m = current_location.z;
		br_wing->angles = angle;

	}
}
