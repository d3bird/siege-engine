#include "missile.h"


missile::missile(int id, loc<int> aLocation) : fuel(20,0.25),
	ID(id),
	location(aLocation), actual_location(aLocation.x * 2, aLocation.y * 2, aLocation.z * 2), target(-1, -1, -1),
	target_set(false), fired(false), 
	state(TAKE_OFF), acceleration(1), velocity(10), max_velocity(100),
	angle_change(30), horizontal_angle(0),
	model(NULL)
{

}

missile::~missile()
{
}

void missile::fire(const loc<double>& atarget) {
	target = atarget;
	fired = true;
}

bool missile::is_fired() {
	return fired;
}

void missile::explode() {
	fired = false;
	
}


double missile::get_velocity() {
	double output = velocity;
	switch (state)
	{
	case missile::TAKE_OFF:
		break;
	case missile::ANGLE_TOWARD:
		break;
	case missile::HOMING:
		break;
	case missile::FULL_SPEED:
		break;
	default:
		break;
	}
	return output;
}

double missile::get_angle_changle() {
	return angle_change;
}

void missile::set_fly_state(flight_state new_state) {
	state = new_state;
}

void missile::set_grid_location(const loc<int>& alocation) {
	location = alocation;
	actual_location.x = location.x * 2;
	actual_location.y = location.y * 2;
	actual_location.z = location.z * 2;
	update_model_info();
}

void missile::update_model_location(const loc<double>& alocation, double angle) {
	actual_location = alocation;
	horizontal_angle = angle;
	update_model_info();
}

void missile::update_model_info() {
	if (model != NULL) {
		model->x_m = actual_location.x;
		model->y_m = actual_location.y;
		model->z_m = actual_location.z;
		model->angles.set_y_angle(horizontal_angle);
	}
}
