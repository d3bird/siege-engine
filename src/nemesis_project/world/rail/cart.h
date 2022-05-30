#pragma once


#include <rendering/rendering_object_data.hpp>

#include "rail.h"

namespace railRoad {

	class cart {
	public:
		cart(int aID,  rail* start_loc);

		void update(double deltaTime);

		bool is_running() { return running; }
		void set_running(bool run) { running = run; }

		void move_location(rail* new_loc) { location = new_loc; }

		void set_velocity(double vel) { velocity = vel; }
		double get_velocity() { return velocity; }

		int get_ID() { return ID; }
		rail* get_location() { return location; }

		int get_rail_index() { return raid_index; }
		void set_rail_index(int index) { raid_index = index; }

		void print_info();

		item_info* cart_obj;

		bool operator ==(const cart& right);
		bool operator ==(const int& id);

		//these functions change the velocity that the cart is going
		void operator +=(double vel);
		void operator -=(double vel);
		void operator ++();
		void operator --();

	private:

		void change_speed(double vel);
		void apply_extra_distance(double x_amount,double y_amount, double z_amount);

		int ID;
		rail * location;
		
		bool reached_end;
		int raid_index;//what index in the array the cart is at
		int rail_state;//how to procede in the array of points
		// -2 = need to go to next rail section
		// -1 = need to determin direction
		//0 = starts at 0 going up
		//1 starts at rail index max and going down
		
		//possitive velocity to connection 1
		//negative velocity to connection 1
		double velocity;
		double max_speed;

		bool running;

	};

}