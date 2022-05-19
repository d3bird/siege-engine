#include "local_map.h"

local_map_data::local_map_data(){

}

local_map_data::~local_map_data(){
	delete_map_data();
}



void local_map_data::delete_map_data() {


	//checks to makesure that the map was compleatly deleted
	if (map != NULL) {
		int count = 0;
		for (int y = 0; y < y_size; y++) {
			for (int x = 0; x < x_size; x++) {
				for (int z = 0; z < z_size; z++) {
					if (map[y][x][z].ground != NULL) {
						count++;
					}
					if (map[y][x][z].floor != NULL) {
						count++;
					}
				}
			}
		}
		if (count != 0) {
			std::cout << "WARRNING: " << count << " objs where not delete ahead of time" << std::endl;
		}
	}

	//delete the wheels
	if (Wheels != NULL) {
		delete Wheels;
	}

	//delete the rooms
	if (rooms_on_map.size() > 0) {
		for (int i = 0; i < rooms_on_map.size(); i++) {
			delete rooms_on_map[i];
		}
	}

}


bool local_map_data::is_inbounds_of_map_local(int x, int y, int z) {
	return (map != NULL &&
		x >= 0 && x < x_size &&
		y >= 0 && y < y_size &&
		z >= 0 && z < z_size );
}