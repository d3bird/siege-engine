#include "belt_manager.h"

#include <iostream>

belt_manager::belt_manager(motion_manger* mm) :
	updater(mm), ID_num(0)
{
}

belt_manager::~belt_manager()
{
	for (int i = 0; i < belts_update.size(); i++) {
		if (belts_update[i]->get_obj() != NULL) {
			std::cout << "belt rendering object was not cleaned up" << std::endl;
		}
		delete belts_update[i];
		belts_update[i] = NULL;
	}
	belts_update.clear();
}

void belt_manager::update(double deltaTime) {


}

std::pair<int, int> belt_manager::spawn_belt(loc<int> location, int out_dir) {

	std::pair<int, int> output(-1, -1);

	belt* temp = new belt(ID_num, location, out_dir);
	output.first = ID_num;
	ID_num++;
	belts_update.push_back(temp);
	return output;
}

int belt_manager::get_num_connections(int ID) {

	for (int i = 0; i < belts_update.size(); i++) {
		if (belts_update[i]->get_ID() == ID) {
			return belts_update[i]->get_num_connections();
		}
	}
	return -1;
}

item_info* belt_manager::replace_obj(int ID,item_info* new_obj) {

	for (int i = 0; i < belts_update.size(); i++) {
		if (belts_update[i]->get_ID() == ID) {

			item_info* old_obj = belts_update[i]->get_obj();
			belts_update[i]->set_obj(new_obj);//should rotate the object to fit connections
			updater->update_item(new_obj);

			return old_obj;
		}
	}

	return NULL;
}

std::vector<item_info*> belt_manager::get_all_objs() {
	std::vector<item_info*> output;

	for (int i = 0; i < belts_update.size(); i++) {
		if (belts_update[i]->get_obj() != NULL) {
			output.push_back(belts_update[i]->get_obj());
		}
	}

	return output;
}
