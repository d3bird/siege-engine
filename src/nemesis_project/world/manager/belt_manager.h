#pragma once

#include "../location.hpp"

#include <vector>
#include <unordered_map>

class belt_manager
{
public:
	belt_manager();
	~belt_manager();

	int place_belt(int x, int y, int z, int dir);


private:

	int ID_index;

	struct belt {
		
		loc location;
		//0 = north
		//1 = south
		//2 = east
		//3 = west
		int direction = -1;
		int ID =-1;

		//if this is marked as old then it can be moved to the back 
		//of the vector and be overrided
		bool old = false;

		belt(int id, int dir,  int x, int y, int z) {
			location = loc(x, y, z);
			ID = id;
			direction = dir;
		}

		bool operator==(const belt& other) {

			if (ID >= 0 && other.ID >= 0) {
				return location == other.location;
			}
			return false;
		}
		bool operator==(const loc& other) {
			return location == other;
		}
	};


	bool does_belt_exist(belt* test);
	bool does_belt_exist(loc test);

	//std::vector<belt*> belts;
	std::unordered_map<loc, belt*>belts;
};

