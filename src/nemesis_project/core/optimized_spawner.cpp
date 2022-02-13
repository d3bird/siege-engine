#include "optimized_spawner.h"

#include <iostream>

optimized_spawner::optimized_spawner(){
	objs = NULL;
	OBJM = NULL;
	time = NULL;
}

optimized_spawner::~optimized_spawner(){

}

item_info* optimized_spawner::spawn_item(item_type type, int x, int y, int z, glm::mat4* given_mat) {
	if (OBJM != NULL) {
		return OBJM->spawn_item(type, x, y, z, given_mat);
	}
	else {
		return NULL;
	}
}
item_info* optimized_spawner::spawn_item(item_type type, int x, int y, int z, float angle) {
	if (OBJM != NULL) {
		return OBJM->spawn_item(type, x, y, z, angle);
	}
	else {
		return NULL;
	}
}


//init functiuons

void optimized_spawner::init(data_ball* objs) {

	if (objs != NULL) {
		OBJM = objs->OBJM;
		time = objs->time;

		import_models();
	}
	else {
		std::cout << "THE DATABALL WAS NULL" << std::endl;
	}
}

void optimized_spawner::import_models() {
	std::cout << "importing models" << std::endl;

	external_paths paths;
	unsigned int buffer_size = 50;

	OBJM->add_model("FLOOR_TEMP", paths.get_objs_loc("terrian/floor.obj"), buffer_size, FLOOR_TEMP);
	OBJM->add_model("WALL_TEMP", paths.get_objs_loc("terrian/wall.obj"), buffer_size, WALL_TEMP);


	std::cout << "done" << std::endl;
}