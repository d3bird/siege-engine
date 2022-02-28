#pragma once

#include "../location.hpp"

#include "../../core/optimized_spawner.h"

#include <vector>
//#include <unordered_map>
namespace door_data {

	enum opening { LEFT = 0, SPLIT = 1, RIGHT = 2 };

	struct d_sec {
		int x_start;
		int y_start;
		int z_start;

		int x_end;
		int y_end;
		int z_end;

		int x_current;
		int y_current;
		int z_current;

		item_info* door_sec = NULL;

		bool need_update;
	};

	struct door {
		opening type;
		bool open;
		int axis_type;//0 = x, 1 = y, 2 = z

		int x_start;
		int y_start;
		int z_start;

		int x_end;
		int y_end;
		int z_end;


		int ar_x;
		int ar_z;
		d_sec** d_sec;

		bool need_update;
	};

	class door_manager
	{
	public:

		door_manager();
		~door_manager();

		door* place_door(opening type, int x_start, int y_start, int z_start,
			int x_end, int y_end, int z_end);

		door* get_door(int index);

	private:

		int ID_index;

		std::vector<door*>doors;

	};
};