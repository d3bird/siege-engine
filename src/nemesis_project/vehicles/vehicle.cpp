#include "vehicle.h"

grnd_vehicle::grnd_vehicle(const loc<double>& location){

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

grnd_vehicle::grnd_vehicle(const loc<int>& location) {

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


void grnd_vehicle::update(const loc<double>& new_location) {

	obj_cords = new_location;

	if (body != NULL) {
		body->x_m = new_location.x * 2;
		body->y_m = new_location.y * 2;
		body->z_m = new_location.z * 2;
	}

	//wheels
	if (BLW != NULL) {
		BLW->x_m = new_location.x * 2;
		BLW->y_m = new_location.y * 2;
		BLW->z_m = new_location.z * 2;
	}

	if (BRW != NULL) {
		BRW->x_m = new_location.x * 2;
		BRW->y_m = new_location.y * 2;
		BRW->z_m = new_location.z * 2;
	}

	if (FLW != NULL) {
		FLW->x_m = new_location.x * 2;
		FLW->y_m = new_location.y * 2;
		FLW->z_m = new_location.z * 2;
	}

	if (FRW != NULL) {
		FRW->x_m = new_location.x * 2;
		FRW->y_m = new_location.y * 2;
		FRW->z_m = new_location.z * 2;
	}

	//misc
	if (headlights != NULL) {
		headlights->x_m = new_location.x * 2;
		headlights->y_m = new_location.y * 2;
		headlights->z_m = new_location.z * 2;
	}
}