#pragma once

#include <string>
#include <iostream>
#include <vector>
//#include "../creature/creature_data.hpp"
#include "../object_data.hpp"
//#include "../creature/crew/person.h"

class zone{
public:
	zone(std::string n,zone_type t);
	~zone();

	virtual int add_spot_to_zone(int x, int y, int z);
	virtual void remove_spot_from_zone(int x, int y, int z);
//	virtual int get_interaction_spot(actions act, item_info* obj = NULL) { return -1; }

	virtual void update(){}

	void set_bounds(int x, int y, int z) {
		x_size = x;
		y_size = y;
		z_size = z;
	}

	bool inbounds(zone_cell* in){
		return  ((in->x >= 0 && in->x < x_size) &&
			(in->y >= 0 && in->y < y_size) &&
			(in->z >= 0 && in->z < z_size));
	}

	void debug_print();

protected:

	//update the connections on a cell
	void update_conections(zone_cell* in);

	//world bounds
	int x_size;
	int y_size;
	int z_size;

	unsigned int current_ID;

	zone_type type;
	std::string zone_name;
	std::vector< zone_cell*> all_spots;
	std::vector<int> update_spots;
	std::vector<int> unsued_spots;
};

