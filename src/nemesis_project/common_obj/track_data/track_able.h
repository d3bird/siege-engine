#pragma once

#include "track_aircraft_data.h"
#include "track_weapon_data.h"
#include "track_grnd_vehicle_data.h"

#include "../location.h"

#include <rendering/rendering_object_data.hpp>

#include <string>

struct track_data {

	std::string track_name;

	track_weapon_data* weapons = 0;
	track_grnd_vehicle_data* grnd_vehicle = 0;
	track_aircraft_data* air_vehicle = 0;

	int amount_models = 0;
	rendering::item_info** models = 0;

	loc<double> base_location;
};