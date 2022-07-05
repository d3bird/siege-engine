#include "rail.h"

#include <iostream>

railRoad::rail::rail() {
	ID = -1;

	location = loc<int>(-1, -1, -1);
	connecttion1 = 0;
	connecttion2 = 0;
	type = STRAIGHT;
	x_axais = true;
	location_array = 0;
	location_array = NULL;
}

railRoad::rail::rail(int aID, int aX, int aY, int aZ, rail_type aType, bool axias) {
	ID = aID;

	location = loc<int>(aX, aY, aZ);
	connecttion1 = 0;
	connecttion2 = 0;
	type = aType;
	x_axais = axias;

	switch (type)
	{
	case railRoad::CURVE:
		location_array = 0;
		location_array = NULL;
		break;
	case railRoad::STRAIGHT:
		location_array = 0;
		location_array = NULL;
		break;
	case railRoad::SLANT:
		std::cout << "making a rail that is a slant" << std::endl;
		location_array = new loc<double>[2];
		location_array[0].x = aX;
		location_array[0].y = aY+ 0.5;
		location_array[0].z = aZ;

		location_array[1].x = aX;
		location_array[1].y = aY + 1;
		location_array[1].z = aZ;

		location_amount = 2;

		if (axias) {
			location_array[1].x = aX - 2;
		}
		else {
			location_array[1].z = aZ - 2;
		}
		break;
	default:
		location_array = 0;
		location_array = NULL;
		break;
	}

}

railRoad::rail::rail(int aID, loc<int>& alocation, rail_type aType, bool axias) {
	location = alocation;
	ID = aID;
	connecttion1 = 0;
	connecttion2 = 0;
	type = aType;
	x_axais = axias;

	location = alocation;

	switch (type)
	{
	case railRoad::CURVE:
		location_array = 0;
		location_array = NULL;
		break;
	case railRoad::STRAIGHT:
		location_array = 0;
		location_array = NULL;
		break;
	case railRoad::SLANT:
		location_array = new loc<double>[2];
		location_array[0].x = alocation.x;
		location_array[0].y = alocation.y +.5;
		location_array[0].z = alocation.z;

		location_array[1].x = alocation.x;
		location_array[1].y = alocation.y + 1;
		location_array[1].z = alocation.z;
		
		location_amount = 2;

		if (axias) {
			location_array[1].x = alocation.x - 1;
		}
		else {
			location_array[1].z = alocation.z - 1;
		}
		break;
	default:
		location_array = 0;
		location_array = NULL;
		break;
	}
}

loc<double>  railRoad::rail::get_loc_array(int index) {
	if (location_array != NULL && index >=0 && index < location_amount) {
		return location_array[index];
	}
	loc<double> output;
	output.x = location.x;
	output.y = location.y;
	output.z = location.z;
	return output;
}

bool railRoad::rail::operator ==(const rail& right) {
	return (ID == right.ID);
}

bool  railRoad::rail::can_connect(rail* other, bool connect) {
	bool output = false;

	switch (type)
	{
	case railRoad::STRAIGHT:
		output = straight_connection(other, connect);
		break;
	case railRoad::SLANT:
		slanted_connection(other, connect);
		break;
	case railRoad::CURVE:
	default:
	//	std::cout << "there is no connection for this rail type" << std::endl;
		curved_connection(other, connect);
		break;
	}

	return output;
}

bool railRoad::rail::straight_connection(rail* other, bool connect) {

	bool output = false;

	if (other != NULL) {

		//std::cout << "this.id " << ID << " compare " << other->get_ID() << std::endl;

		if (other->get_axais() == x_axais) {


			loc<int> other_loc = other->get_loc();

			int pos = -1;
			//-1 == none
			// 1 == left
			// 2 == right
			// 3 == up
			// 4 == down

			//must be on the same axis
			if (location.y != other_loc.y) {
				return false;
			}

			//std::cout << other_loc.x << " == " << location.x << std::endl;
			//std::cout << other_loc.z << " == " << location.z << std::endl;
			if (x_axais) {

				if (other_loc.z == location.z) {
					if (other_loc.x == location.x + 1) {
						pos = 1;
					}
					else if (other_loc.x == location.x - 1) {
						pos = 2;
					}
				}
			}
			else {
				if (other_loc.x == location.x) {
					if (other_loc.z == location.z + 1) {
						pos = 3;
					}
					else if (other_loc.z == location.z - 1) {
						pos = 4;
					}
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

bool railRoad::rail::slanted_connection(rail* other, bool connect) {
	bool output = false;

	//std::cout << "this sia slant connection" << std::endl;
	if (other != NULL) {

		if (other->get_axais() == x_axais) {


			loc<int> other_loc = other->get_loc();

			int pos = -1;
			//-1 == none
			// 1 == left
			// 2 == right
			// 3 == up
			// 4 == down

			//must be on the same axis
			if (location.y != other_loc.y) {
				return false;
			}

			//std::cout << other_loc.x << " == " << location.x << std::endl;
			//std::cout << other_loc.z << " == " << location.z << std::endl;
			if (x_axais) {

				if (other_loc.z == location.z) {
					if (other_loc.x == location.x + 1) {
						pos = 1;
					}
					else if (other_loc.x == location.x - 1) {
						pos = 2;
					}
				}
			}
			else {
				if (other_loc.x == location.x) {
					if (other_loc.z == location.z + 1) {
						pos = 3;
					}
					else if (other_loc.z == location.z - 1) {
						pos = 4;
					}
				}
			}


			//if the first possition fails try the scond pos
			if (pos == -1) {

				//must be on the same axis
				if (location_array[1].y != other_loc.y) {
					return false;
				}

				//std::cout << other_loc.x << " == " << location.x << std::endl;
				//std::cout << other_loc.z << " == " << location.z << std::endl;
				if (x_axais) {

					if (other_loc.z == location_array[1].z) {
						if (other_loc.x == location_array[1].x + 1) {
							pos = 1;
						}
						else if (other_loc.x == location_array[1].x - 1) {
							pos = 2;
						}
					}
				}
				else {
					if (other_loc.x == location_array[1].x) {
						if (other_loc.z == location_array[1].z + 1) {
							pos = 3;
						}
						else if (other_loc.z == location_array[1].z - 1) {
							pos = 4;
						}
					}
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

	return output;
}

bool railRoad::rail::curved_connection(rail* other, bool connect) {
	return false;
}

bool  railRoad::rail::can_connect_point(rail* other, loc<int> location, int connection) {

	return false;
}