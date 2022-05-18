#pragma once

#include "../core/optimized_spawner.h"
#include "../sensors/sensor_net.h"

#include <vector>

class motion_manger{
public:
	motion_manger();
	motion_manger(optimized_spawner* objm);
	~motion_manger();

	void update_item(item_info* obj);
	void update_item_matrix(update_pak& up);
	
	void push_updates();
	void regester_sensor_net(sensor_net& net);

private:
	optimized_spawner* OBJM;
	static motion_manger* instance;

	struct update {
		update_pak up;
		glm::mat4 mat;
		bool use_mat;
	};

	std::vector< update> updates;

};

