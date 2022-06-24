#include "vehicle.h"

grnd_vehicle::grnd_vehicle(const loc<double>& location): fuel(10, 0.1) {

	obj_cords = location;

	body = NULL;

	//wheels
	BLW = NULL;
	BRW = NULL;
	FLW = NULL;
	FRW = NULL;

	//misc
	headlights = NULL;
}

grnd_vehicle::grnd_vehicle(const loc<int>& location) : fuel(10, 0.1) {

	obj_cords.x = location.x;
	obj_cords.y = location.y;
	obj_cords.z = location.z;

	body = NULL;

	//wheels
	BLW = NULL;
	BRW = NULL;
	FLW = NULL;
	FRW = NULL;

	//misc
	headlights = NULL;
}

grnd_vehicle::~grnd_vehicle(){

}


void grnd_vehicle::update(const loc<double>& new_location, bool mult) {

	obj_cords = new_location;
	int mult_num = 2;
	if (!mult) {
		mult_num = 1;
	}
	if (body != NULL) {
		body->x_m = new_location.x * mult;
		body->y_m = new_location.y * mult;
		body->z_m = new_location.z * mult;
	}

	//wheels
	if (BLW != NULL) {
		BLW->x_m = new_location.x * mult;
		BLW->y_m = new_location.y * mult;
		BLW->z_m = new_location.z * mult;
	}

	if (BRW != NULL) {
		BRW->x_m = new_location.x * mult;
		BRW->y_m = new_location.y * mult;
		BRW->z_m = new_location.z * mult;
	}

	if (FLW != NULL) {
		FLW->x_m = new_location.x * mult;
		FLW->y_m = new_location.y * mult;
		FLW->z_m = new_location.z * mult;
	}

	if (FRW != NULL) {
		FRW->x_m = new_location.x * mult;
		FRW->y_m = new_location.y * mult;
		FRW->z_m = new_location.z * mult;
	}

	//misc
	if (headlights != NULL) {
		headlights->x_m = new_location.x * mult;
		headlights->y_m = new_location.y * mult;
		headlights->z_m = new_location.z * mult;
	}
}