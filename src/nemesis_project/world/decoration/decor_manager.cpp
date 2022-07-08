#include "decor_manager.h"



decor::decor_mgr::decor_mgr(motion_manger* mm){
	updater = mm;
	decor_id = 0;
}

decor::decor_mgr::~decor_mgr(){

}

void decor::decor_mgr::update(double time) {
	for (int i = 0; i < decor_items_update.size(); i++) {
		decor_items_update[i]->update(time);
		updater->update_item(decor_items_update[i]->obj2);
	}
}

void decor::decor_mgr::place_fanx3x3(const loc<int>& location, rendering::item_info* frame, rendering::item_info* fan) {
	decor_item* temp = new decor_item(decor_id);
	temp->obj1 = frame;
	temp->obj2 = fan;
	temp->type = decor::FAN;
	add_to_list(temp);
}

void  decor::decor_mgr::add_to_list(decor_item* input) {
	if (input->needs_update()) {
		decor_items_update.push_back(input);
	}
	else {
		decor_items_static.push_back(input);
	}
}
