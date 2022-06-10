#pragma once

#include "decor_item.h"
#include "../../utility/motion_manager.h"
#include "../../common_obj/location.h"

#include <vector>
namespace decor {

	class decor_mgr
	{
	public:
		decor_mgr(motion_manger* mm);
		~decor_mgr();

		void update(double time);

		void place_fanx3x3(const loc<int>& location, item_info* frame, item_info* fan);

	private:

		void add_to_list(decor_item* input);

		motion_manger* updater;

		int decor_id;

		std::vector<decor_item*> decor_items_update;
		std::vector<decor_item*> decor_items_static;
	};

}