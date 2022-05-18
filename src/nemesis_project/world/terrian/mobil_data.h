#pragma once

#include <vector>
#include <rendering/rendering_object_data.hpp>


struct wheel {
	int turn_speed = 1;
	bool pos_directio = true;

	int wheight_limit = 0;
	item_info* obj = NULL;
	item_info* wheel_block_link = NULL;
};

struct wheels {
	std::vector<wheel*> wheels;
	std::vector<item_info*> wheel_blocks;
};