#pragma once

#include "bulk_head_door.h"
#include <rendering/rendering_object_data.hpp>
#include "../../common_obj/location.h"
#include "../../core/motion_manager.h"

#include <vector>

class door_manager
{
public:
	door_manager(motion_manger* mm);
	~door_manager();

	void update(double time);

	void spawn_bulk_head_door(loc<int> start, loc<int> end, bool y_axis, bool dir1, optimized_spawner* spawner);

	void open_door(int ID);
	void close_door(int ID);

	bool is_door_open(int ID);

private:
	motion_manger* updater;

	std::vector< bulk_head_door*> doors;
};

