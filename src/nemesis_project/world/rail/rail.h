#pragma once

#include "../../common_obj/location.h"

namespace railRoad {

	enum rail_type{ CURVE=0, STRAIGHT, SLANT};

	class rail {
	public:
		rail();
		rail(int aID, int aX, int aY, int aZ, rail_type aType, bool axias = true);
		rail(int aID, loc<int>& alocation, rail_type aType, bool axias = true);

		int get_x() { return location.x; }
		int get_y() { return location.y; }
		int get_z() { return location.z; }

		loc<int> get_loc() { return location; }

		int get_ID() { return ID; }

		void set_connection1(rail* con) { connecttion1 = con; }
		void set_connection2(rail* con) { connecttion2 = con; }

		rail* get_connection1() { return connecttion1; }
		rail* get_connection2() { return connecttion2; }

		bool operator ==(const rail& right);

		bool can_connect(rail* other, bool connect = false);

		bool get_axais() { return x_axais; }

		rail_type get_type() { return type; }

	private:

		int ID;

		loc<int> location;
		//this is for the slants and curves 
		loc<int> second_location;//if the rail has another endpoint

		rail* connecttion1;//left up
		rail* connecttion2;//right down

		//this determins what axais the rail is on
		bool x_axais;

		rail_type type;

	};

}