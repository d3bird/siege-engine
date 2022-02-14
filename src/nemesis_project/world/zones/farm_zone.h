#pragma once
#include "zone.h"
class farm_zone : public zone
{
public:
	farm_zone(std::string n);

	int add_spot_to_zone(int x, int y, int z);
	void remove_spot_from_zone(int x, int y, int z);
	//int get_interaction_spot(actions act, item_info* obj = NULL);

	void update();

private:

};

