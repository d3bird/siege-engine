#pragma once

#include <rendering/rendering_object_data.hpp>

#include "../zones/zone.h"
#include "../zones/farm_zone.h"

#include "../../common_obj/location.h"

#include "room.hpp"

class map_cell;

struct room {
	std::string room_name;
	std::vector< map_cell*> cells_in_room;
};

struct additional_proporities {
	std::vector< item_info*> additional_items;
};

class map_cell {
public:
	map_cell();
	~map_cell();

	int x;
	int y;
	int z;

	item_info* ground = NULL;//this is the main object in the square (could be a wall, table etc..)
	item_info* floor = NULL;

	bool gen_without_items = false;
	int ground_type = CUBE_T;
	int floor_type = CUBE_T;


	additional_proporities* props = NULL;

	zone* zone_on_top = NULL;

	map_cell* link_to_platform = NULL;

	bool inclosed = false;
	bool checked = false;
	bool failed_to_find_room = false;

	room* part_of_room = NULL;

	bool passibe() {
		if (ground != NULL) {
			switch (ground->type)
			{
			case LADDER_T:
				return true;
				break;
			default:
				return false;
				break;
			}
		}
		else {
			return floor != NULL;
		}
	}


private:
};