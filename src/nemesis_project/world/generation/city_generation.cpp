#include "city_generation.h"

#include <iostream>


city_generation::city_generation(optimized_spawner* spawn) {

}

city_generation::~city_generation() {

}

city_gen_settings* city_generation::get_flat_city_settings() {
	city_gen_settings* output = new city_gen_settings;

	output->x_size = 5;
	output->y_size = 5;
	output->z_size = 5;

	output->flat_land = true;
	output->ground_level = 0;
	output->mobile = true;

	return output;
}

mobil_platform* city_generation::create_mobile_plat(city_gen_settings* settings) {

	mobil_platform* output = NULL;

	if (is_settings_valid(settings)) {


	}

	return output;
}

bool city_generation::is_settings_valid(city_gen_settings* settings) {
	bool output = false;

	if (settings != NULL) {

		output = true;
	}

	return output;
}
