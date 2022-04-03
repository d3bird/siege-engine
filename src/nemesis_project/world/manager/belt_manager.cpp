#include "belt_manager.h"

#include <iostream>

belt_manager::belt_manager(optimized_spawner* objm){
	ID_index = 0;
	OBJM = objm;
}

belt_manager::~belt_manager(){

}

item_info* belt_manager::place_belt(int x, int y, int z, int dir) {
	item_info* output = NULL;
	
	belt* temp = new belt(ID_index,dir,x,y,z);

	if (dir == 0 || dir == 1) {
		temp->angle = 90;
	}

	ID_index++;
	//connect_belt(temp);

	int type = get_belt_type(temp->ID);
	float angle = get_belt_angle(temp->ID);

	 if (type == 1) {
		output = OBJM->spawn_item(BELT_2, x, y, z, angle);
	}
	else if (type == 2) {
		output = OBJM->spawn_item(BELT_3, x, y, z, angle);
	}
	else if (type == 3) {
		output = OBJM->spawn_item(BELT_4, x, y, z, angle);
	}
	else {
		output = OBJM->spawn_item(BELT_1, x, y, z, angle);
	}

	//auto found = belts.find(temp_loc);

	//if (found == belts.end()) {
	//	std::cout << "the given location doe not have belt, but will now" << std::endl;
	//}
	
	//if (!does_belt_exist(temp_loc)) {
	//	belt* new_b = new belt(ID_index, dir, x, y, z);
	//	ID_index++;

	//}

	return output;
}

bool belt_manager::does_belt_exist(belt* test) {
	//if (test == NULL) {
		return false;
	//}
	//else {
	//	int index = test->ID;
	//	if (index >= 0 && index < belts.size() && !test->old) {
	//		return *test == *belts[index];
	//	}
	//	else {
	//		return false;
	//	}
	//}
}

bool belt_manager::does_belt_exist(loc_i<int> test) {
	//for the vecotr
	//for (int i = 0; i < belts.size(); i++) {
	//	if (belts[i] != NULL && !belts[i]->old) {
	//		if (test == belts[i]->location) {
	//			return true;
	//		}
	//	}
	//}
	return false;
}

bool belt_manager::connect_belt(belt* input) {
	bool connected = false;

	//check to see if the belt can connect to another belt

	int x = input->location.x;
	int y = input->location.y;
	int z = input->location.z;
	for (int i = 0; i < belts.size(); i++) {
		if (belts[i]->location.y == y) {
			for (int dir = 0; dir < 4; dir++) {
				if (con_exist(dir, input->location, belts[i]->location)) {
					switch (dir)
					{
					case 0:
						std::cout << "belt " << input->ID << " north connection" << std::endl;
						input->north = belts[i];
						break;
					case 1:
						std::cout << "belt " << input->ID << " south connection" << std::endl;
						input->south = belts[i];
						break;
					case 2:
						std::cout << "belt " << input->ID << " east connection" << std::endl;
						input->east = belts[i];
						break;
					case 3:
						std::cout << "belt " << input->ID << " west connection" << std::endl;
						input->west = belts[i];
						break;
					}
				}
			}
		}
	}

	//add to the master list
	belts.push_back(input);
	return connected;
}

int belt_manager::get_belt_type(int id) {

	if (id > 0 && id < belts.size()) {
		return belts[id]->type;
	}
	return -1;
}

float belt_manager::get_belt_angle(int id) {

	if (id > 0 && id < belts.size()) {
		return belts[id]->angle;
	}
	return 0;
}


bool belt_manager::con_exist(int dir, loc_i<int> loc_org, loc_i<int> loc_conn) {
	//0 = north
	//1 = south
	//2 = east
	//3 = west

	if (loc_org.y != loc_conn.y) {
		return false;
	}

	int x = loc_org.x;
	int y = loc_org.y;
	int z = loc_org.z;

	int x2 = loc_conn.x;
	int y2 = loc_conn.y;
	int z2 = loc_conn.z;

	if (y != y2) {
		return false;
	}

	if (dir == 0) {
		if (z == z2 - 1) {
			return true;
		}
	}
	else if (dir == 1) {
		if (z == z2 + 1) {
			return true;
		}
	}
	else if (dir == 2) {
		if (x == x2 - 1) {
			return true;
		}
	}
	else {
		if (x == x2 + 1) {
			return true;
		}
	}

	
	return false;
}

void belt_manager::print_belt(int index) {
	if (!belts.empty() && index >= 0 && index < belts.size()) {
		std::cout << "belt  : " << index << std::endl;
		std::cout << "angle : " << belts[index]->angle << std::endl;
		std::cout << "type  : " << belts[index]->type << std::endl;
		std::cout << "N con : " << (belts[index]->north == NULL ? "FALSE" : "TRUE") << std::endl;
		std::cout << "S con : " << (belts[index]->south == NULL ? "FALSE" : "TRUE") << std::endl;
		std::cout << "E con : " << (belts[index]->east == NULL ? "FALSE" : "TRUE") << std::endl;
		std::cout << "W con : " << (belts[index]->west == NULL ? "FALSE" : "TRUE") << std::endl;

	}
	else {
		std::cout << "there are no belts to print" << std::endl;
	}
}

void belt_manager::print_all_belts() {
	if (!belts.empty()) {
		std::cout << std::endl;
		std::cout << "printing all belts" << std::endl;
		for (int i = 0; i < belts.size(); i++) {
			print_belt(i);
			std::cout << std::endl;
		}
		std::cout << std::endl;

	}
	else {
		std::cout << "there are no belts to print" << std::endl;
	}
}