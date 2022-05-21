#pragma once

#include "rail.h"
#include "cart.h"
#include "../../common_obj/location.h"
#include "../../utility/motion_manager.h"

#include <vector>

/**
* This class handles the placement of the carts and rails
* it will connect rails together and link the cart to a rail
* 
*/
namespace railRoad {

	class rail_manager {
	public:
		rail_manager(motion_manger* mm);
		~rail_manager();

		void update(double deltaTime);

		int can_place_cart(loc<int>& location);
		int place_cart(loc<int>& location);
		void toggle_cart(int id);
		void set_cart_vel(int id, double velocity);


		bool add_rail(int x, int y, int z, bool x_axis);
		bool remove_rail(int x, int y, int z);

		bool add_rail(loc<int> &location, bool x_axis);
		bool remove_rail(loc<int> &location);

		void print_info();

		//since the carts are moving and not linked to any objects
		//they are public to any class that is handling the objs
		std::vector<cart> carts;

	private:
		std::vector<int> old_IDs;

		std::vector<rail*> rails;
		
		int cart_id;
		int rail_id;
		motion_manger* MM;
	};

}