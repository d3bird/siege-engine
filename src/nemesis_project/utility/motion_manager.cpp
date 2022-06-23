#include "motion_manager.h"

#include <iostream>

motion_manger::motion_manger() {
	OBJM = NULL;

}

motion_manger::motion_manger(optimized_spawner* objm){
	OBJM = objm;
}

motion_manger::~motion_manger()
{
}

void motion_manger::update_item(item_info* obj) {

	if (obj == NULL) {
		std::cout << "can not update the obj was NULL" << std::endl;
		return;
	}

	update_pak update_pac;

	update_pac.x = obj->x_m;
	update_pac.y = obj->y_m;
	update_pac.z = obj->z_m;

	update_pac.x_scale = 1;
	update_pac.y_scale = 1;
	update_pac.z_scale = 1;

	update_pac.angle = obj->angles;

	update_pac.buffer_loc = obj->buffer_loc;
	update_pac.item_id = obj->item_id;

	OBJM->update_item_matrix(&update_pac);

}


void motion_manger::update_item_matrix(update_pak& up) {
	OBJM->update_item_matrix(&up);
}

void motion_manger::push_updates() {

	for (int i = 0; i < updates.size(); i++) {
		update temp = updates[i];
		if (temp.use_mat) {
			OBJM->update_item_matrix(&temp.up, temp.mat);
		}
		else {
			OBJM->update_item_matrix(&temp.up);
		}
	}
	updates.clear();
}

void motion_manger::regester_sensor_net(sensor_net& net) {



}