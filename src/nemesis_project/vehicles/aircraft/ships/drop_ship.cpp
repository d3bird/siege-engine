#include "drop_ship.h"


drop_ship::drop_ship(int id): fuel(20,0.5) {
	ID = id;

	turn_speed = 30;
	move_speed = 20;
	doors_opening = false;
	doors_open = false;
	door_move_speed = 5;
	door_offset = 2;
	current_off = 0;

	parked = true;
	ready_to_take_off = false;
	unloading = true;
	getting_ready_take_off = false;
	getting_ready_park = false;
	doors_closing = false;
	doors_closed = true;

	body = NULL;
	engines = NULL;
	left_doors = NULL;
	right_doors = NULL;

	current_route = NULL;

}

drop_ship::~drop_ship() {

}

//updates the model location and the doors moving
void drop_ship::update_models(loc<double> aLocation, double time){
	//set the new location
	location = aLocation;

	//update the doors
	if (doors_opening) {
		current_off += (door_move_speed * time);
		if (current_off >= door_offset) {
			current_off = door_offset;
			doors_opening = false;
			doors_open = true;
			doors_closed = false;
		}
	}
	else if (doors_closing) {
		current_off -= (door_move_speed * time);
		if (current_off <= 0) {
			current_off = 0;
			doors_closing = false;
			doors_open = false;
			doors_closed = true;
		}
	}

	//update the models
	update_models(false);
}

void drop_ship::update_models(double time) {
	if (doors_opening) {
		current_off += (door_move_speed * time);
		if (current_off >= door_offset) {
			current_off = door_offset;
			doors_opening = false;
			doors_open = true;
			doors_closed = false;
		}
	}
	else if (doors_closing) {
		current_off -= (door_move_speed * time);
		if (current_off <= 0) {
			current_off = 0;
			doors_closing = false;
			doors_open = false;
			doors_closed = true;
		}
	}

	update_models(true);
}

void drop_ship::set_location(loc<int> aLocation){
	location = (loc<double>(aLocation.x * 2, aLocation.y * 2, aLocation.z * 2));
	update_models(false);
}

void drop_ship::set_location(loc<double> aLocation){
	location = aLocation;
	update_models(false);
}

void drop_ship::update_models(bool just_doors) {

	if (left_doors != NULL) {
		left_doors->x_m = location.x + current_off;
		left_doors->y_m = location.y;
		left_doors->z_m = location.z;
	}
	if (right_doors != NULL) {
		right_doors->x_m = location.x - current_off;
		right_doors->y_m = location.y;
		right_doors->z_m = location.z;
	}

	if (!just_doors) {
		if (body != NULL) {
			body->x_m = location.x;
			body->y_m = location.y;
			body->z_m = location.z;
		}
		if (engines != NULL) {
			engines->x_m = location.x;
			engines->y_m = location.y;
			engines->z_m = location.z;
		}
	}

}

void drop_ship::open_doors(){
	if (!doors_open) {
		doors_opening = true;
		doors_closing = false;
	}
}

void drop_ship::close_doors(){
	if (!doors_closed) {
		doors_opening = false;
		doors_closing = true;
	}
}

bool drop_ship::are_doors_open(){
	return doors_open;
}

double drop_ship::get_move_speed(){
	return move_speed;
}

double drop_ship::get_turn_speed() {
	return turn_speed;
}

void drop_ship::start_landing_procedures() {
	parked = true;
	ready_to_take_off = false;
	getting_ready_park = true;
	unloading = true;
	open_doors();
}

void drop_ship::start_take_off_procedures() {
	parked = false;
	unloading = false;
	getting_ready_take_off = true;
	close_doors();
}

bool drop_ship::operator==(const int id) {
	return ID == id;
}