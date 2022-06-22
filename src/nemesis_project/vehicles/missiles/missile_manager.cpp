#include "missile_manager.h"

missile_manager::missile_manager(motion_manger* mm):
	missile_id(0), launcher_id(0)
{
	updater = mm;
}

missile_manager::~missile_manager(){

	for (int i = 0; i < missiles.size(); i++) {
		delete missiles[i];
	}
	missiles.clear();

	for (int i = 0; i < launchers.size(); i++) {
		delete launchers[i];
	}
	launchers.clear();

}

void missile_manager::update(double time) {

}


int missile_manager::spawn_missile(const loc<int>& location, item_info* model) {
	int output = -1;
	if (model != NULL) {
		missile* temp = new missile(missile_id, location);
		temp->model = model;
		output = missile_id;
		missile_id++;
		missiles.push_back(temp);
	}
	return output;
}

int missile_manager::spawn_launcher(const loc<int>& location, item_info* model) {
	int output = -1;
	if (model != NULL) {
		launcher* temp = new launcher(missile_id, location);
		temp->model = model;
		output = missile_id;
		missile_id++;
		launchers.push_back(temp);
	}
	return output;
}

bool missile_manager::move_missile_to_launcher(int amissile, int alauncher) {
	bool preformed = false;
	missile* miss = get_missile(amissile);
	launcher* lan = get_launcher(alauncher);
	if (miss != NULL && lan != NULL) {
		if (lan->slotted_missile == NULL) {
			preformed = true;
			lan->slotted_missile = miss;
			lan->update_missile_model();
			updater->update_item(miss->model);
		}
	}
	return preformed;
}

bool missile_manager::fire_launcher(int alauncher, const loc<int>& target) {
	bool preformed = false;
	launcher* lan = get_launcher(alauncher);
	if (lan != NULL && lan->slotted_missile != NULL) {

	}
	return preformed;
}

bool missile_manager::is_launcher_empty(int alauncher) {
	launcher* temp = get_launcher(alauncher);
	return temp != NULL && temp->slotted_missile == NULL;
}

int missile_manager::get_launcher_id(const loc<int>& location) {
	for (int i = 0; i < launchers.size(); i++) {
		if (launchers[i]->get_location() == location) {
			return launchers[i]->get_ID();
		}
	}
	return -1;
}

missile* missile_manager::get_missile(int id) {
	for (int i = 0; i < missiles.size(); i++) {
		if (missiles[i]->get_ID() == id) {
			return missiles[i];
		}
	}
	return NULL;
}

launcher* missile_manager::get_launcher(int id) {
	for (int i = 0; i < launchers.size(); i++) {
		if (launchers[i]->get_ID() == id) {
			return launchers[i];
		}
	}
	return NULL;
}