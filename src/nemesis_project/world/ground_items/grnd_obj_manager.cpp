#include "grnd_obj_manager.h"

namespace grnd_items {

	grnd_obj_mgr::grnd_obj_mgr(optimized_spawner* spawn, motion_manger* mm) :
		spawner(spawn), updater(mm)
	{
	}

	grnd_obj_mgr::~grnd_obj_mgr()
	{
	}
}