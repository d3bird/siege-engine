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

		int spawn_obj(const loc<int>& location, grnd_obj_type type);
		void delete_obj(const loc<int>& location);
		void delete_obj(int ID);

		bool convert_obj(grnd_obj& object, grnd_obj_type type);


	private:
		optimized_spawner* spawner;
		motion_manger* updater;

		int ID_counter;

		std::vector< grnd_obj*> grnd_objs;
	};
}