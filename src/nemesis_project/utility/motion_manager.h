#pragma once

#include "../core/optimized_spawner.h"
#include "../sensors/sensor_net.h"

#include <vector>

class motion_manger
{
public:
	motion_manger(optimized_spawner* objm);
	~motion_manger();

	void update_item_matrix(update_pak* up);
	
	void push_updates();
	void regester_sensor_net(sensor_net& net);

private:
	optimized_spawner* OBJM;


};

