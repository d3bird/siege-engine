#include "landing_site.h"

landing_site::landing_site(int id){
	ID = id;
	obj = NULL;

}

landing_site::~landing_site()
{
}

bool landing_site::operator==(const int& id) {
	return ID == id;
}
