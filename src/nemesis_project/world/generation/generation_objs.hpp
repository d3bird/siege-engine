#pragma once

#include <vector>

struct city_gen_settings {
	int x_size;
	int y_size;
	int z_size;


};

enum biomes{FOREST, PLANE, VALLEY, HILLS, AIR_DROP};

struct world_gen_settings {
	//world tile
	int x_size;
	int y_size;
	int z_size;

	//world size
	int cells_wide;//x
	int cells_long;//z

	bool spawn_items = true;

	int ground_level;

	bool use_mix_of_biomes;
	biomes specific_biome;

	bool biome_size_range;
	int biome_size;
	int biome_min_size;
	int biome_max_size;

	std::vector< biomes> encluded_bioms;
};

struct gen_setttings {

	bool spawn_items;
	bool create_thermal_system;
	bool create_motion_system;

	bool check_for_errors;

	city_gen_settings* city_settings;
	world_gen_settings* world_settings;
};



static void delete_settings(gen_setttings* remove) {
	if (remove != NULL) {
		if (remove->city_settings != NULL) {
			delete remove->city_settings;
		}
		if (remove->world_settings != NULL) {
			delete remove->world_settings;
		}
		delete remove;
		remove = NULL;
	}
}