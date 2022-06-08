#include "aircraft.h"

aircraft::aircraft(int id) {
	ID = id;
	obj = NULL;
}

aircraft::~aircraft() {

}


bool aircraft::operator==(const int& id) {
	return ID == id;
}
