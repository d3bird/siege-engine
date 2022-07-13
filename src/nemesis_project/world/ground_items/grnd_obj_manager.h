#pragma once

#include "grnd_obj.h"
#include "recipe.h"
#include "../../core/optimized_spawner.h"
#include "../../core/motion_manager.h"

#include <vector>
namespace grnd_items {

	class grnd_obj_mgr
	{
	public:
		grnd_obj_mgr(optimized_spawner* spawn, motion_manger* mm);
		~grnd_obj_mgr();

		bool convert_obj(const grnd_obj& object, grnd_obj::grnd_obj_type type);


	private:
		optimized_spawner* spawner;
		motion_manger* updater;
	};
}