#pragma once

#include "rail.h"
#include "cart.h"
#include "../../common_obj/location.hpp"

#include <vector>
/**
* This class handles the placement of the carts and rails
* it will connect rails together and link the cart to a rail
* 
*/
namespace railRoad {

	class rail_manager {
	public:
		rail_manager();
		~rail_manager();

		bool can_place_cart(loc<int>& location);
		bool can_place_rail(loc<int>& location);

		bool add_rail(int x, int y, int z);
		bool remove_rail(int x, int y, int z);

		bool add_rail(loc<int> &location);
		bool remove_rail(loc<int> &location);

	private:
		std::vector<int> old_IDs;


	};

}