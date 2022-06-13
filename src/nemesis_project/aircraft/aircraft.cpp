#include "aircraft.h"

aircraft::aircraft(int id) {
	ID = id;
	obj = NULL;
	current_route = NULL;
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
