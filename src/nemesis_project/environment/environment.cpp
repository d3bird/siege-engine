#include "environment.h"

environment::environment(optimized_spawner* os, motion_manger* mm) :crane_mgr(mm), rail_mgr(mm) {
	spawner = os;
	updater = mm;
	world_map = NULL;
}

environment::~environment(){

}

void environment::update(double time_change) {
	crane_mgr.update(time_change);
	rail_mgr.update(time_change);
	furnace_mgr.update(time_change);
}

bool environment::place_rail(loc<int>& location, bool x_axis, railRoad::rail_type aType) {
	bool output = can_place_rail(location);

	if (output) {
		item_info* temp = NULL;

		switch (aType)
		{
		case railRoad::CURVE:
			temp = spawner->spawn_item(CURVE_RAIL, location.x, location.y, location.z);

			break;
		case railRoad::STRAIGHT:
			temp = spawner->spawn_item(RAIL, location.x, location.y, location.z);
			break;
		case railRoad::SLANT:
			temp = spawner->spawn_item(SLANT_RAIL, location.x, location.y, location.z);
			break;
		default:
			std::cout << "there is no model for this rail" << std::endl;
			break;
		}

		if (temp == NULL) {
			return false;
		}

		if (!x_axis) {
			temp->angle = 90;
			updater->update_item(temp);
		}

		if (!world_map->attach_obj(location, temp, false, true)) {
			std::cout << "failed to attach rail to world map" << std::endl;
		}

		rail_mgr.add_rail(location, x_axis, aType);
	}
	return output;
}

bool environment::can_place_rail(loc<int>& location) {
	bool output = false;
	return true;
	if (world_map != NULL) {

		output = world_map->can_place_ground_obj(location, true);

	}
	return output;
}


int environment::place_cart(loc<int>& location) {
	int rail_state = can_place_cart(location);
	bool placable;

	switch (rail_state)
	{
	case 1:
	case 2:
		placable = true;
		break;
	case 0:
	default:
		placable = false;
		break;
	}

	int output = -1;
	if (placable) {
		output = rail_mgr.place_cart(location);

		if (output != -1) {

			item_info* temp = spawner->spawn_item(CART, location.x, location.y, location.z);

			//the rail is facing another direction
			if (rail_state == 2) {
				temp->angle = 90;
				updater->update_item(temp);
			}

			//yes I know that this is not the best, but it can be optimised latter
			for (int i = 0; i < rail_mgr.carts.size(); i++) {
				if (rail_mgr.carts[i] == output) {
					rail_mgr.carts[i].cart_obj = temp;
					std::cout << "linked the obj with the cart" << std::endl;
					break;
				}
			}
		}
		else {
			std::cout << "railroad mgr failed to create a cart object" << std::endl;
		}
	}
	else {
		std::cout << "fail to place cart" << std::endl;
	}
	return output;
}

int environment::can_place_cart(loc<int>& location) {
	return rail_mgr.can_place_cart(location);
}

void environment::toggle_cart(int id, double velocity) {
	rail_mgr.set_cart_vel(id, velocity);
	rail_mgr.toggle_cart(id);
}

void environment::prin_rail_info() {
	rail_mgr.print_info();
}

int environment::place_crane(const loc<int>& location, int height, int radius) {
	int output = -1;
	item_info* temp = 0;

	std::cout << "creating crane" << std::endl;

	std::cout << height << " , " << radius << std::endl;

	crane* new_crane = crane_mgr.create_crane(location, height, radius);
	if (new_crane == NULL) {
		std::cout << "failed creating crane" << std::endl;
		return output;
	}

	//make the central pillar
	for (int i = 0; i < height; i++) {
		temp = spawner->spawn_item(CRANE_B, location.x, location.y + i, location.z);
		if (temp != NULL) {
			new_crane->base.push_back(temp);
			world_map->attach_obj(loc<int>(location.x, location.y + i, location.z), temp, false, true);
		}
	}

	//make the arm
	for (int i = location.x - 1; i < radius + location.x - 1; i++) {
		temp = spawner->spawn_item(CUBE_T, i, location.y + height - 2, location.z);
		if (temp != NULL) {
			new_crane->arm.push_back(temp);
		}
	}

	//make the attachment
	temp = spawner->spawn_item(CUBE_T, 0, location.y + height - 2, location.z);
	if (temp != NULL) {
		new_crane->attachment = (temp);
	}

	new_crane->set_running(true);
	new_crane->set_aproaching_dest(true);
	new_crane->print_info();

	std::cout << "done creating crane" << std::endl;

	return output;
}


void environment::toggle_crane(int id) {
	crane_mgr.toggle_crane(id);
}


crane* environment::get_crane(int id) {
	return crane_mgr.get_crane(id);
}


int environment::create_furnace(const std::vector<loc<int> >& spots) {
	return furnace_mgr.create_furnace(spots);
}

void environment::add_mass_to_furnace(int id, double mass) {
	furnace_mgr.add_mass_to_furnace(id, mass);
}