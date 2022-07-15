#include "grnd_obj_manager.h"

namespace grnd_items {

	grnd_obj_mgr::grnd_obj_mgr(optimized_spawner* spawn, motion_manger* mm) :
		spawner(spawn), updater(mm), ID_counter(0)
	{
	}

	grnd_obj_mgr::~grnd_obj_mgr()
	{
	}

	int grnd_obj_mgr::spawn_obj(const loc<int>& location, grnd_obj_type type) {
		int return_ID = ID_counter;
		int amount = 1;
		int max_amount = 1;
		grnd_obj* temp = new  grnd_obj(return_ID, type, amount, max_amount, location);
		rendering::item_info* model = NULL;

		switch (type)
		{
		case grnd_items::INGOT:
			model = spawner->spawn_item(COPPER_INGOT, location);
			break;
		case grnd_items::BOX:
			model = spawner->spawn_item(CRATE, location);
			break;
		case grnd_items::BARREL:
			model = spawner->spawn_item(BARROW, location);

			break;
		default:
			break;
		}

		if(model)
		ID_counter++;
		return return_ID;
	}

	void grnd_obj_mgr::delete_obj(const loc<int>& location) {
		for (int i = 0; i < grnd_objs.size(); i++) {
			if (grnd_objs[i]->get_location() == location) {
				rendering::item_info* temp_model = grnd_objs[i]->get_model();
				if (temp_model != NULL) {
					spawner->delete_item_from_buffer(temp_model);
				}
				delete grnd_objs[i];
				if (grnd_objs.size() == 1) {
					grnd_objs.clear();
				}
				else {
					grnd_objs[i] = grnd_objs[0];
					grnd_objs.erase(grnd_objs.begin());
				}
				return;
			}
		}
	}

	void grnd_obj_mgr::delete_obj(int ID) {
		for (int i = 0; i < grnd_objs.size(); i++) {
			if (grnd_objs[i]->get_ID() == ID) {
				rendering::item_info* temp_model = grnd_objs[i]->get_model();
				if (temp_model != NULL) {
					spawner->delete_item_from_buffer(temp_model);
				}
				delete grnd_objs[i];
				if (grnd_objs.size() == 1) {
					grnd_objs.clear();
				}
				else {
					grnd_objs[i] = grnd_objs[0];
					grnd_objs.erase(grnd_objs.begin());
				}
				return;
			}
		}
	}

	bool grnd_obj_mgr::convert_obj(grnd_obj& object, grnd_obj_type type) {
		
		object.set_type(type);
		return false;
	}
}