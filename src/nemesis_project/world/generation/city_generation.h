#pragma once


#include "../mobil_platform.h"
#include "../terrian_data.hpp"
#include "../../core/optimized_spawner.h"

struct city_gen_settings {
	int x_size;
	int y_size;
	int z_size;

	bool flat_land;
	int ground_level;
	bool mobile;
};

class city_generation {
public:
	city_generation(optimized_spawner* spawn);
	~city_generation();

	city_gen_settings* get_flat_city_settings();

	mobil_platform* create_mobile_plat(city_gen_settings* settings);

private:
	optimized_spawner* spawner;

	bool is_settings_valid(city_gen_settings* settings);
};