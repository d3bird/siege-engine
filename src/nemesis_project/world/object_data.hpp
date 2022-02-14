#pragma once

//this file is located in the scene as an extention of the rendering objects


#include <rendering/rendering_object_data.hpp>

#include "res_items/res_item.hpp"
#include "../core/spawning_enums.hpp"

struct floor_item {
	item_info* render_oj = NULL;
	res_item* f_item_data = NULL;
};

//information for theremal systems
struct material_proporties {
	std::string materal_name;

	float melting_point;
	bool metalble;
	bool flamible;
	float heat_trans; //the percent of heat that transfer per 1 sec 

	int max_hit_points;
	int durablity; //all around damage reduction
	int blunt_durablity;// blunt damage reduction
	int piercing_durablity;// piercing damage reduction

	int material_id;
};

struct object_proporites {
	bool on_fire;
	bool melting;
	bool sold;
	bool liquid;
	float tempature;
	bool visable;
	int hit_points;

	material_proporties* material;
};

struct thermal_block {
	bool empty = true;
	int x, y, z;
	float tempature;

	bool heat_source = false;
	float source_tempature;
	float time_remaining;

	bool being_updated = false;
	int updates_since_temp_changed =0;
	item_info* obj = NULL;
};

//information for zone data
enum zone_type{ STOCKPILE, FARM};

struct zone_cell {
	int x, y, z;
	bool empty;

	item_info* obj_on_top;
	unsigned int buffer_index;// location in the zone vector
	unsigned int ID;
	zone_type type;

	//connecting zones
	zone_cell* west = NULL;
	zone_cell* east = NULL;
	zone_cell* south = NULL;
	zone_cell* north = NULL;
};

static void clean_material_proporties(material_proporties* mat) {
	if (mat == NULL) {
		return;
	}
	delete mat;
}

static void clean_object_proporites(object_proporites* prop) {
	if (prop == NULL) {
		return;
	}
	delete prop;
}


static material_proporties* create_material(std::string name,
	float melting_point, bool metalble, bool flamible, float heat_trans,
	int max_hit_points, int durablity, int blunt_durablity, int piercing_durablity) {
	material_proporties* output = new material_proporties;

	output->materal_name = name;

	output->melting_point = melting_point;
	output->metalble = metalble;
	output->flamible = flamible;
	output->heat_trans = heat_trans;

	output->max_hit_points = max_hit_points;
	output->durablity = durablity;
	output->blunt_durablity = blunt_durablity;
	output->piercing_durablity = piercing_durablity;

	output->material_id = -1;

	return output;
}
