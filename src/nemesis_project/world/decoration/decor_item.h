#pragma once

#include "decor_type.hpp"
#include <rendering/rendering_object_data.hpp>

namespace decor {

	class decor_item
	{
	public:
		decor_item(int id);
		~decor_item();

		void update(double time);

		rendering::item_info* obj1;
		rendering::item_info* obj2;

		decor_type type;

		bool needs_update();

	private:
		int ID;
		double turn_speed;


	};

}