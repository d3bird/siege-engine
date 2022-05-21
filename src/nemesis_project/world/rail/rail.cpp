#include "rail.h"

#include <iostream>

railRoad::rail::rail() {
	ID = -1;

	location = loc<int>(-1, -1, -1);
	connecttion1 = 0;
	connecttion2 = 0;

	x_axais = true;
}

railRoad::rail::rail(int aID, int aX, int aY, int aZ, bool axias) {
	ID = aID;

	location = loc<int>(aX, aY, aZ);
	connecttion1 = 0;
	connecttion2 = 0;
	x_axais = axias;
}

railRoad::rail::rail(int aID, loc<int>& alocation, bool axias) {
	location = alocation;
	ID = aID;
	connecttion1 = 0;
	connecttion2 = 0;
	x_axais = axias;
}


bool railRoad::rail::operator ==(const rail& right) {
	return (ID == right.ID);
}

bool  railRoad::rail::can_connect(rail* other, bool connect) {
	bool output = false;

	if (other != NULL) {

		//std::cout << "this.id " << ID << " compare " << other->get_ID() << std::endl;

		if (other->get_axais() == x_axais) {
			int pos = -1;
			//-1 == none
			// 1 == left
			// 2 == right
			// 3 == up
			// 4 == down

			loc<int> other_loc = other->get_loc();

			//must be on the same axis
			if (location.y != other_loc.y) {
				return false;
			}

			//std::cout << other_loc.x << " == " << location.x << std::endl;
		//	std::cout << other_loc.z << " == " << location.z << std::endl;
			if (x_axais) {

				if (other_loc.x == location.x + 1) {
					pos = 1;
				}
				else if (other_loc.x == location.x - 1) {
					pos = 2;
				}
			}
			else {

				if (other_loc.z == location.z + 1) {
					pos = 3;
				}
				else if (other_loc.z == location.z - 1) {
					pos = 4;
				}
			}

			if (pos != -1) {
				output = true;
				//connect to the other rail
				if (connect) {

					if (pos == 1 || pos == 3) {
						connecttion1 = other;
						other->set_connection2(this);
					}
					else if (pos == 2 || pos == 4) {
						connecttion2 = other;
						other->set_connection1(this);
					}
				}

			}
			else {
				//std::cout << "rail failed to make the connection" << std::endl;
			}

		}
	}
	else {
		std::cout << "other rail was null" << std::endl;
	}

	return output;
}
