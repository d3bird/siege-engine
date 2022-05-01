#include "cart.h"


railRoad::cart::cart(int aID, rail* start_loc) {
	ID = aID;
	velocity = 0;
	max_speed = 50;
	location = start_loc;
}

bool railRoad::cart::operator ==(const cart& right) {
	return (ID == right.ID);
}

void railRoad::cart::operator +=(double vel) {
	change_speed(vel);
}

void  railRoad::cart::operator -=(double vel) {
	change_speed(vel);
}

void  railRoad::cart::operator ++() {
	change_speed(1);
}
void  railRoad::cart::operator --() {
	change_speed(-1);

}

void railRoad::cart::change_speed(double vel) {
	velocity += vel;
	if (velocity > max_speed) {
		velocity = max_speed;
	}
	if (velocity < (max_speed * -1)) {
		velocity = (max_speed * -1);
	}

}