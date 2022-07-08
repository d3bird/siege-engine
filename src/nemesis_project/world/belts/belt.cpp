#include "belt.h"

#include <iostream>

belt::belt(int id, loc<int> aLocation, int aOutDirection):
	object(NULL), ID(id), location(aLocation), outDirection(aOutDirection),
	north_connection(NULL), south_connection(NULL), east_connection(NULL), west_connection(NULL)
{
	if (outDirection > 3) {
		outDirection = outDirection % 4;
	}
	else if (outDirection < 0) {
		outDirection = 0;
	}
}

belt::~belt()
{
}

bool belt::can_connect(bool connect) {
	bool output = false;

	return output;
}

bool belt::operator ==(const belt& other) {
	return ID = other.ID;
}

bool belt::operator ==(int aID) {
	return ID = aID;
}

int belt::get_num_connections() {
	int output = 0; 
	if (north_connection != NULL) {
		output++;
	}
	if (south_connection != NULL) {
		output++;
	}
	if (east_connection != NULL) {
		output++;
	}
	if (west_connection != NULL) {
		output++;
	}
	return output;
}

bool belt::open_connections() {
	return (north_connection != NULL ||
		south_connection != NULL ||
		east_connection != NULL ||
		west_connection != NULL);
}

void belt::set_obj(rendering::item_info* new_obj) {
	object = new_obj;
}
