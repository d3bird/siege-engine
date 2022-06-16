#include "landing_strip.h"

landing_strip::landing_strip(int id){
	ID = id;
	obj = NULL;

}

landing_strip::~landing_strip()
{
}

bool landing_strip::operator==(const int& id) {
	return ID == id;
}
