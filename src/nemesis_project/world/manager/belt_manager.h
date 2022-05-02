#pragma once

#include "../../common_obj/location.hpp"

#include "../../core/optimized_spawner.h"

#include <vector>
//#include <unordered_map>

class belt_manager
{
public:
	belt_manager(optimized_spawner* objm);
	~belt_manager();

	item_info* place_belt(int x, int y, int z, int dir);

	int get_belt_type(int id);
	float get_belt_angle(int id);

	void print_belt(int index);
	void print_all_belts();

private:

	int ID_index;

	optimized_spawner* OBJM;

	struct belt {
		
		loc<int> location;
		//0 = north
		//1 = south
		//2 = east
		//3 = west
		int direction = -1;//the output directions
		int ID =-1;

		int type = 0;
		float angle = 0;

		//the directions that are connected
		belt* north = NULL;
		belt* south = NULL;
		belt* west = NULL;
		belt* east = NULL;

		//if this is marked as old then it can be moved to the back 
		//of the vector and be overrided
		bool old = false;

		belt(int id, int dir,  int x, int y, int z) {
			location = loc<int>(x, y, z);
			ID = id;
			direction = dir;
			type = 0;
			angle = 0;
		}

		bool operator==(const belt& other) {

			if (ID >= 0 && other.ID >= 0) {
				return location == other.location;
			}
			return false;
		}
		bool operator==(const loc<int>& other) {
			return location == other;
		}
	};


	bool does_belt_exist(belt* test);
	bool does_belt_exist(loc<int> test);

	std::vector<belt*> belts;
	//std::unordered_map<loc, belt*>belts;

	bool connect_belt(belt* input);

	bool con_exist(int dir, loc<int> loc_org, loc<int> loc_conn);
};

//world_map->map[1][2][0].ground = OBJM->spawn_item(STONE_WALL, 2, 1, 0);
//world_map->map[1][0][1].ground = OBJM->spawn_item(STONE_WALL, 0, 1, 1);
