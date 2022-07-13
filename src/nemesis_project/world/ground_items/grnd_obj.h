#pragma once

#include "../../common_obj/location.h"
#include  <rendering/rendering_object_data.hpp>

namespace grnd_items {

	class grnd_obj
	{
	public:

		enum grnd_obj_type
		{
			NONE, INGOT, BOX
		};

		grnd_obj();
		~grnd_obj();

	private:

	};

}