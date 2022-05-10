#pragma once

#include "../../common_obj/location.hpp"

namespace railRoad {
	class rail {
	public:
		rail(int aID, int aX, int aY, int aZ);
		rail(int aID, loc<int>& alocation);

		int get_x() { return location.x; }
		int get_y() { return location.y; }
		int get_z() { return location.z; }

		loc<int>& get_loc() { return location; }

		int get_ID() { return ID; }

		void set_connection1(rail* con) { connecttion1 = con; }
		void set_connection2(rail* con) { connecttion2 = con; }

		rail* get_connection1() { return connecttion1; }
		rail* get_connection2() { return connecttion2; }

		bool operator ==(const rail& right);

	private:

		int ID;

		loc<int> location;

		rail* connecttion1;
		rail* connecttion2;

	};

}