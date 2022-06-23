#include "decor_item.h"

decor::decor_item::decor_item(int id){
	ID = id;
	obj1 = NULL;
	obj2 = NULL;
	type = decor::FAN;
	turn_speed = 20;
}

decor::decor_item::~decor_item()
{
}

void decor::decor_item::update(double time) {

	switch (type)
	{
	case decor::FAN:
		double angle_change = turn_speed * time;
		float angle = obj2->angles.get_y_angle();
		angle += angle_change;
		if (angle >= 360) {
			angle -= 360;
		}
		obj2->angles.set_y_angle(angle);
		break;
	}

}


bool decor::decor_item::needs_update() {
	bool output = false;
	switch (type)
	{
	case decor::FAN:
		output = true;
		break;
	}
	return output;
}
