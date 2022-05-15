#pragma once

#include "rail.h"

namespace railRoad {

	class cart {
	public:
		cart(int aID,  rail& start_loc);

		void move_location(rail& new_loc) { location = new_loc; }

		int get_ID() { return ID; }
		rail* get_location() { return &location; }

		bool operator ==(const cart& right);
		bool operator ==(const int& id);
		void operator +=(double vel);
		void operator -=(double vel);

		void operator ++();
		void operator --();
	private:

		void change_speed(double vel);

		int ID;
		rail location;

		double velocity;

		double max_speed;

	};

}