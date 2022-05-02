#pragma once

#include <vector>

#include "terrian_data.hpp"
#include "../common_obj/location.hpp"
#include "../core/optimized_spawner.h"

class mobil_platform{
public:
	mobil_platform();
	~mobil_platform();
	
	void update(float delta_time);
	void increase_velocity(bool forward);
	void change_angle(double delta_angle);

	//moves the p[latform so 0,0,0 starts at the location that is given
	void move_plat_to_loc(loc<double> location);

	//creates the mangers
	void init(optimized_spawner* spawn);

	local_map_data* map_info;//created externally 

	
private:
	optimized_spawner* spawner;

	bool moving;

	double velocity;
	double velocity_max;
	double angle;
	void update_pos(float delta_time);
};

