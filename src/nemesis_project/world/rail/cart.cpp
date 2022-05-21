#include "cart.h"

#include <iostream>

railRoad::cart::cart(int aID,  rail* start_loc) {
	ID = aID;
	velocity = 0;
	max_speed = 20;
	location = start_loc;
	cart_obj = NULL;
	running = true;
}

void railRoad::cart::update(double deltaTime) {
	//std::cout << "updating cart: " <<ID << std::endl;
	//print_info();
	
	if (cart_obj == NULL) {
		running = false;
		std::cout << "the cart obj was false" << std::endl;
		return;
	}

	double x = cart_obj->x_m;
	double y = cart_obj->y_m;
	double z = cart_obj->z_m;

	double x_end;
	double y_end;
	double z_end;

	double change;

	if (velocity > 0) {
		if (location->get_connection1() != NULL) {
			x_end = location->get_connection1()->get_x();
			y_end = location->get_connection1()->get_y();
			z_end = location->get_connection1()->get_z();
			change = deltaTime * velocity;
		}
		else {
			std::cout << "the next connection1 was null" << std::endl;
			print_info();
			//running = false;
			//velocity = 0;
			std::cout << "reversing direction" << std::endl;
			velocity *= -1;
			return;
		}
	}
	else if (velocity < 0) {
		if (location->get_connection2() != NULL) {
			x_end = location->get_connection2()->get_x();
			y_end = location->get_connection2()->get_y();
			z_end = location->get_connection2()->get_z();
			change = deltaTime * velocity * -1;
		}
		else {
			std::cout << "the next connection2 was null" << std::endl;
			print_info();
			//running = false;
			//velocity = 0;
			std::cout << "reversing direction" << std::endl;
			velocity *= -1;
			return;
		}
	}
	else if (velocity == 0) {
		running = false;
		//velocity *= -1;
		return;
	}

	//have to correct for the grids being 2 away from each other
	x_end *= 2;
	y_end *= 2;
	z_end *= 2;

	bool pos_change = false;
	double extra_x = 0;
	double extra_z = 0;

	if (x < x_end) {
		x += change;
		pos_change = true;
		if (x > x_end) {
			extra_x = x - x_end;
			x = x_end;
		}
	}else if (x > x_end) {
		x -= change;
		pos_change = true;
		if (x < x_end) {
			extra_x = x_end -x ;
			x = x_end;
		}
	}

	if (z < z_end) {
		z += change;
		pos_change = true;
		if (z > z_end) {
			extra_z = z - z_end;
			z = z_end;
		}
	}
	else if (z > z_end) {
		z -= change;
		pos_change = true;
		if (z < z_end) {
			extra_z = z_end - z;
			z = z_end;
		}
	}

	//if the pos did not change then switch to the next rail
	//if the next rail is NULL then set the velocity to zero
	if (!pos_change) {
		rail* next = NULL;
		if (velocity > 0) {
			next = location->get_connection1();
		//	std::cout << "grabbing new connection1" << std::endl;
		}
		else if (velocity < 0) {
			next = location->get_connection2();
			//std::cout << "grabbing new connection2" << std::endl;

		}
		apply_extra_distance(extra_x, extra_z);
		location = next;
	}
	else {
		//std::cout << "current obj cords " << x << " " << z << std::endl;
		//std::cout << "end obj cords "<<x_end<<" "<<z_end << std::endl;
		cart_obj->x_m = x;
		cart_obj->y_m = y;
		cart_obj->z_m = z;
	}

}

//this applies the extra distance that was caught when moving to the next spot
void  railRoad::cart::apply_extra_distance(double x_amount, double z_amount) {
	//this solution will only really work for strieght paths and should be changed when
	//curves are added
	cart_obj->x_m += x_amount;
	//cart_obj->y_m += y;
	cart_obj->z_m += z_amount;
}


bool railRoad::cart::operator ==(const cart& right) {
	return (ID == right.ID);
}

bool railRoad::cart::operator ==(const int& id) {
	return (ID == id);
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

void railRoad::cart::print_info() {
	std::cout << "cart " << ID << std::endl;
	if (running) {
		std::cout << "cart is running" << std::endl;
	}
	std::cout << "velocity " << velocity << std::endl;
	std::cout << "max_speed " << max_speed << std::endl;
	std::cout << "connection1 " << (location->get_connection1() == NULL ? "NULL" : "conected") << std::endl;
	std::cout << "connection2 " << (location->get_connection2() == NULL ? "NULL" : "conected") << std::endl;

	std::cout << std::endl;
}