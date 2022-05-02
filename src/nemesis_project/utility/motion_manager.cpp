#include "motion_manager.h"

motion_manger::motion_manger() {
	OBJM = NULL;

}

motion_manger::motion_manger(optimized_spawner* objm){
	OBJM = objm;
}

motion_manger::~motion_manger()
{
}


void motion_manger::update_item_matrix(update_pak& up) {

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