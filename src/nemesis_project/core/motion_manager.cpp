#include "motion_manager.h"

#include <iostream>

motion_manger::motion_manger():
	OBJM(NULL), motion_gui(NULL)
{

}

motion_manger::motion_manger(optimized_spawner* objm):
	OBJM(objm), motion_gui(NULL)
{
}

motion_manger::~motion_manger()
{
}

void motion_manger::update_track(track_data* data) {
	if (data == NULL) {
		std::cout << "can not update the track_data was NULL" << std::endl;
		return;
	}

	if (!is_data_tracked(data)) {
		track_stream.insert(std::pair<std::string, track_data*>(data->track_name, data));
	}

	if (data->amount_models > 0) {
		for (int i = 0; i < data->amount_models;i++) {
			if (data->models[i] != NULL) {

				rendering::item_info* obj = data->models[i];

				if (obj != NULL) {
					rendering::update_pak update_pac;

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
			}
		}
	}

}


void motion_manger::update_item(rendering::item_info* obj) {

	if (obj == NULL) {
		std::cout << "can not update the obj was NULL" << std::endl;
		return;
	}

	rendering::update_pak update_pac;

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


void motion_manger::update_item_matrix(rendering::update_pak& up) {
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

void motion_manger::show_gui() {
	if (motion_gui == NULL) {
		motion_gui = new motion_manager_gui(&track_stream);
	}
	else {
		motion_gui->show();
	}
}

void motion_manger::hide_gui() {
	if (motion_gui != NULL) {
		motion_gui->hide();
	}
}

void motion_manger::draw_gui_window() {
	if (motion_gui == NULL) {
		motion_gui = new motion_manager_gui(&track_stream);
	}
	else {
		motion_gui->draw_gui_window();
	}
}

void motion_manger::draw_gui_pannel() {
	if (motion_gui == NULL) {
		motion_gui = new motion_manager_gui(&track_stream);
	}
	else {
		motion_gui->draw_gui_pannel();
	}
}

bool  motion_manger::is_data_tracked(track_data* data) {
	bool output = false;

	if (data != NULL) {
		track_stream.find(data->track_name);
	}

	return output;
}
