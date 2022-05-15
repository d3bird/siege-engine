#include "optimized_spawner.h"

#include <iostream>

optimized_spawner::optimized_spawner(){
	objs = NULL;
	OBJM = NULL;
	time = NULL;
}

optimized_spawner::~optimized_spawner(){

}

item_info* optimized_spawner::spawn_item(item_type type, int x, int y, int z, glm::mat4* given_mat) {
	if (OBJM != NULL) {
		return OBJM->spawn_item(type, x, y, z, given_mat);
	}
	else {
		return NULL;
	}
}
item_info* optimized_spawner::spawn_item(item_type type, int x, int y, int z, float angle) {
	if (OBJM != NULL) {
		return OBJM->spawn_item(type, x, y, z, angle);
	}
	else {
		return NULL;
	}
}

void optimized_spawner::delete_item_from_buffer(item_info* obj) {
	if (OBJM != NULL) {
		OBJM->delete_item_from_buffer(obj);
	}
}

void optimized_spawner::update_item_matrix(update_pak* up, glm::mat4 mat) {
	if (OBJM != NULL) {
		OBJM->update_item_matrix(up, mat);
	}
}


void optimized_spawner::update_item_matrix(update_pak* up) {
	if (OBJM != NULL) {
		OBJM->update_item_matrix(up);
	}
}


//init functiuons

void optimized_spawner::init(data_ball* objs) {

	if (objs != NULL) {
		OBJM = objs->OBJM;
		time = objs->time;

		import_models();
	}
	else {
		std::cout << "THE DATABALL WAS NULL" << std::endl;
	}
}

void optimized_spawner::import_models() {
	std::cout << "importing models" << std::endl;

	external_paths paths;
	unsigned int buffer_size = 50;

	int obj_temp = OBJM->add_model("CUBE", paths.get_objs_loc() + "terrian/cube.obj", buffer_size, CUBE_T);
	//table["CUBE"] = obj_temp;

	obj_temp = OBJM->add_model("MOON", paths.get_objs_loc() + "planet/planet.obj", buffer_size, MOON_T);
	//table["MOON"] = obj_temp;

	obj_temp = OBJM->add_model("FLOOR_TEMP", paths.get_objs_loc() + "terrian/floor.obj", buffer_size, FLOOR_TEMP);
	//table["FLOOR_TEMP"] = obj_temp;
	obj_temp = OBJM->add_model("WALL_TEMP", paths.get_objs_loc() + "terrian/wall.obj", buffer_size, WALL_TEMP);
	//table["WALL_TEMP"] = obj_temp;

	obj_temp = OBJM->add_model("SMALL_WHEEL_T", paths.get_objs_loc() + "movement/small_wheel.obj", buffer_size, SMALL_WHEEL_T);
	//table["SMALL_WHEEL_T"] = obj_temp;
	obj_temp = OBJM->add_model("MED_WHEEL_T", paths.get_objs_loc() + "movement/med_wheel.obj", buffer_size, MED_WHEEL_T);
	//table["MED_WHEEL_T"] = obj_temp;
	obj_temp = OBJM->add_model("WHEEL_BLOCK_T", paths.get_objs_loc() + "movement/wheel_block.obj", buffer_size, WHEEL_BLOCK_T);
	//table["WHEEL_BLOCK_T"] = obj_temp;


	obj_temp = OBJM->add_model("RAMP_T", paths.get_objs_loc() + "terrian/ramp.obj", buffer_size, RAMP_T);
	//table["RAMP_T"] = obj_temp;
	obj_temp = OBJM->add_model("CORNOR_RAMP_T", paths.get_objs_loc() + "terrian/cornor_ramp.obj", buffer_size, CORNOR_RAMP_T);
	//table["CORNOR_RAMP_T"] = obj_temp;
	obj_temp = OBJM->add_model("CORNOR_RAMP_DOWN_T", paths.get_objs_loc() + "terrian/cornor_ramp_down.obj", buffer_size, CORNOR_RAMP_DOWN_T);
	//table["CORNOR_RAMP_DOWN_T"] = obj_temp;
	obj_temp = OBJM->add_model("GEAR_BOX_G_UP", paths.get_objs_loc() + "production/box_gear_top.obj", buffer_size, GEAR_BOX_G_UP);
	//table["GEAR_BOX_G_UP"] = obj_temp;
	obj_temp = OBJM->add_model("CUBE_TREE_T", paths.get_objs_loc() + "terrian/cube_tree.obj", buffer_size, CUBE_TREE_T);
	//table["CUBE_TREE_T"] = obj_temp;
	obj_temp = OBJM->add_model("LADDER_T", paths.get_objs_loc() + "terrian/ladder.obj", buffer_size, LADDER_T);
	//table["LADDER_T"] = obj_temp;
	obj_temp = OBJM->add_model("GEAR_BOX_G_DOWN", paths.get_objs_loc() + "production/box_gear_down.obj", buffer_size, GEAR_BOX_G_DOWN);
	//table["GEAR_BOX_G_DOWN"] = obj_temp;

	obj_temp = OBJM->add_model("FURNACE_T", paths.get_objs_loc() + "production/furnace.obj", buffer_size, FURNACE_T);
	//table["FURNACE_T"] = obj_temp;
	obj_temp = OBJM->add_model("FURNACE_GEAR_T", paths.get_objs_loc() + "production/furnace_gear.obj", buffer_size, FURNACE_GEAR_T);
	//table["FURNACE_GEAR_T"] = obj_temp;
	obj_temp = OBJM->add_model("GEAR_BEAM_T", paths.get_objs_loc() + "production/gear_to_beam.obj", buffer_size, GEAR_BEAM_T);
	//table["GEAR_BEAM_T"] = obj_temp;
	obj_temp = OBJM->add_model("BEAM_T", paths.get_objs_loc() + "production/beam.obj", buffer_size, BEAM_T);
	//table["BEAM_T"] = obj_temp;

	obj_temp = OBJM->add_model("GEAR_BOX_FRAME", paths.get_objs_loc() + "production/box_frame.obj", buffer_size, GEAR_BOX_FRAME);
	//table["GEAR_BOX_FRAME"] = obj_temp;
	obj_temp = OBJM->add_model("test", paths.get_objs_loc() + "production/box_frame.obj", buffer_size, TEST_T);
	//table["test"] = obj_temp;

	//add_model("GEAR_BOX_G_DOWN object", paths.get_objs_loc() + "production/box_gear_down.obj", buffer_size, GEAR_BOX_G_DOWN);
	obj_temp = OBJM->add_model("GEAR_BOX_G_L", paths.get_objs_loc() + "production/box_gear_l.obj", buffer_size, GEAR_BOX_G_L);
	//table["GEAR_BOX_G_L"] = obj_temp;
	obj_temp = OBJM->add_model("GEAR_BOX_G_R", paths.get_objs_loc() + "production/box_gear_r.obj", buffer_size, GEAR_BOX_G_R);
	//table["GEAR_BOX_G_R"] = obj_temp;
	obj_temp = OBJM->add_model("GEAR_BOX_G_N", paths.get_objs_loc() + "production/box_gear_n.obj", buffer_size, GEAR_BOX_G_N);
	//table["GEAR_BOX_G_N"] = obj_temp;
	obj_temp = OBJM->add_model("GEAR_BOX_G_S", paths.get_objs_loc() + "production/box_gear_s.obj", buffer_size, GEAR_BOX_G_S);
	//table["GEAR_BOX_G_S"] = obj_temp;


	obj_temp = OBJM->add_model("head", paths.get_objs_loc() + "person/head.obj", buffer_size, HEAD_T);
	//table["head"] = obj_temp;
	obj_temp = OBJM->add_model("body", paths.get_objs_loc() + "person/body.obj", buffer_size, BODY_T);
	//table["body"] = obj_temp;
	obj_temp = OBJM->add_model("left_arm", paths.get_objs_loc() + "person/left_arm.obj", buffer_size, LEFT_ARM);
	//table["left_arm"] = obj_temp;
	obj_temp = OBJM->add_model("left_leg", paths.get_objs_loc() + "person/left_leg.obj", buffer_size, LEFT_LEG);
	//table["left_leg"] = obj_temp;
	obj_temp = OBJM->add_model("right_arm", paths.get_objs_loc() + "person/right_arm.obj", buffer_size, RIGHT_ARM);
	//table["right_arm"] = obj_temp;
	obj_temp = OBJM->add_model("right_leg", paths.get_objs_loc() + "person/right_leg.obj", buffer_size, RIGHT_LEG);
	//table["right_leg"] = obj_temp;

	obj_temp = OBJM->add_model("CRANE_TOP", paths.get_objs_loc() + "belts_machines/crane_top.obj", buffer_size, CRANE_TOP);
	//table["CRANE_TOP"] = obj_temp;
	obj_temp = OBJM->add_model("CRANE_BOT", paths.get_objs_loc() + "belts_machines/crane_bot.obj", buffer_size, CRANE_BOT);
	//table["CRANE_BOT"] = obj_temp;
	obj_temp = OBJM->add_model("CRANE_RAIL", paths.get_objs_loc() + "belts_machines/crane_main_rail.obj", buffer_size, CRANE_RAIL);
	//table["CRANE_RAIL"] = obj_temp;
	obj_temp = OBJM->add_model("CRANE_POST", paths.get_objs_loc() + "belts_machines/crane_piller.obj", buffer_size, CRANE_POST);
	//table["CRANE_POST"] = obj_temp;

	obj_temp = OBJM->add_model("ROATING_TURRET", paths.get_objs_loc() + "weapons/rotating_turret.obj", buffer_size, ROATING_TURRET);
	//table["ROATING_TURRET"] = obj_temp;
	obj_temp = OBJM->add_model("TURRET_BASE", paths.get_objs_loc() + "weapons/turret_base.obj", buffer_size, TURRET_BASE);
	//table["TURRET_BASE"] = obj_temp;
	obj_temp = OBJM->add_model("SMALL_MISSLE", paths.get_objs_loc() + "weapons/small_missle.obj", buffer_size, SMALL_MISSLE);
	//table["SMALL_MISSLE"] = obj_temp;
	obj_temp = OBJM->add_model("SAM_ATTACH", paths.get_objs_loc() + "weapons/sam_attachment.obj", buffer_size, SAM_ATTACH);
	//table["SAM_ATTACH"] = obj_temp;

	obj_temp = OBJM->add_model("DOOR_SECTION", paths.get_objs_loc() + "production/door_section.obj", buffer_size, DOOR_SECTION);
	//table["DOOR_SECTION"] = obj_temp;


	obj_temp = OBJM->add_model("LIFT_WHEEL", paths.get_objs_loc() + "belts_machines/lift_wheel.obj", buffer_size, LIFT_WHEEL);
	//table["LIFT_WHEEL"] = obj_temp;
	obj_temp = OBJM->add_model("LIFT_CABEL", paths.get_objs_loc() + "belts_machines/lift_cabel.obj", buffer_size, LIFT_CABEL);
	//table["LIFT_CABEL"] = obj_temp;
	obj_temp = OBJM->add_model("LIFT_FLOOR", paths.get_objs_loc() + "belts_machines/lift_floor.obj", buffer_size, LIFT_FLOOR);
	//table["LIFT_FLOOR"] = obj_temp;
	obj_temp = OBJM->add_model("LIFT_BASE", paths.get_objs_loc() + "belts_machines/lift_base.obj", buffer_size, LIFT_BASE);
	//table["LIFT_BASE"] = obj_temp;


	obj_temp = OBJM->add_model("BELT_1", paths.get_objs_loc() + "belts_machines/belt.obj", buffer_size, BELT_1);
	//table["BELT_1"] = obj_temp;
	obj_temp = OBJM->add_model("BELT_2", paths.get_objs_loc() + "belts_machines/intersection_2_belt.obj", buffer_size, BELT_2);
	//table["BELT_2"] = obj_temp;
	obj_temp = OBJM->add_model("BELT_3", paths.get_objs_loc() + "belts_machines/intersection_3_belt.obj", buffer_size, BELT_3);
	//table["BELT_3"] = obj_temp;
	obj_temp = OBJM->add_model("BELT_4", paths.get_objs_loc() + "belts_machines/intersection_4_belt.obj", buffer_size, BELT_4);
	//table["BELT_4"] = obj_temp;

	obj_temp = OBJM->add_model("COPPER_INGOT", paths.get_objs_loc() + "floor_items/copper_ingot.obj", buffer_size, COPPER_INGOT);
	//table["COPPER_INGOT"] = obj_temp;
	obj_temp = OBJM->add_model("BARROW", paths.get_objs_loc() + "floor_items/barrow.obj", buffer_size, BARROW);
	//table["BARROW"] = obj_temp;
	obj_temp = OBJM->add_model("CRATE", paths.get_objs_loc() + "floor_items/crate.obj", buffer_size, CRATE);
	//table["CRATE"] = obj_temp;

	obj_temp = OBJM->add_model("CONCRETE_WALL", paths.get_objs_loc() + "terrian/concrete_wall.obj", buffer_size, CONCRETE_WALL);
	//table["CONCRETE_WALL"] = obj_temp;
	obj_temp = OBJM->add_model("DIRT_WALL", paths.get_objs_loc() + "terrian/dirt_wall.obj", buffer_size, DIRT_WALL);
	//table["DIRT_WALL"] = obj_temp;
	obj_temp = OBJM->add_model("STONE_WALL", paths.get_objs_loc() + "terrian/stone_wall.obj", buffer_size, STONE_WALL);
	//table["STONE_WALL"] = obj_temp;
	obj_temp = OBJM->add_model("CONCRETE_FLOOR", paths.get_objs_loc() + "terrian/concrete_floor.obj", buffer_size, CONCRETE_FLOOR);
	//table["CONCRETE_FLOOR"] = obj_temp;
	obj_temp = OBJM->add_model("GRASS_FLOOR", paths.get_objs_loc() + "terrian/grass_floor.obj", buffer_size, GRASS_FLOOR);
	//table["GRASS_FLOOR"] = obj_temp;
	obj_temp = OBJM->add_model("STONE_FLOOR", paths.get_objs_loc() + "terrian/stone_floor.obj", buffer_size, STONE_FLOOR);
	//table["STONE_FLOOR"] = obj_temp;
	obj_temp = OBJM->add_model("TILE_FLOOR", paths.get_objs_loc() + "terrian/tile_floor.obj", buffer_size, TILE_FLOOR);
	//table["TILE_FLOOR"] = obj_temp;

	obj_temp = OBJM->add_model("AIRCRAFT", paths.get_objs_loc() + "aircraft/aircraft.obj", buffer_size, AIRCRAFT_T);
	obj_temp = OBJM->add_model("AIRCRAFT_LANDING_PAD", paths.get_objs_loc() + "aircraft/air_tile.obj", buffer_size, AIRCRAFT_LANDING_PAD);


	obj_temp = OBJM->add_model("BROADCAST_TOWER", paths.get_objs_loc() + "radio/radio_tower_temp.obj", buffer_size, BROADCAST_TOWER);
	obj_temp = OBJM->add_model("RADIO_CONSOLE", paths.get_objs_loc() + "radio/console.obj", buffer_size, RADIO_CONSOLE);
	obj_temp = OBJM->add_model("WALL_SPEAKER", paths.get_objs_loc() + "radio/wall_speaker.obj", buffer_size, WALL_SPEAKER);
	obj_temp = OBJM->add_model("SUPPORT", paths.get_objs_loc() + "radio/support.obj", buffer_size, SUPPORT);
	obj_temp = OBJM->add_model("SPEAKER_TOP", paths.get_objs_loc() + "radio/support_speaker.obj", buffer_size, SPEAKER_TOP);
	
	obj_temp = OBJM->add_model("RAIL", paths.get_objs_loc() + "rail/rail.obj", buffer_size, RAIL);
	obj_temp = OBJM->add_model("CART", paths.get_objs_loc() + "rail/cart.obj", buffer_size, CART);
	obj_temp = OBJM->add_model("WHEELS", paths.get_objs_loc() + "rail/wheels.obj", buffer_size, CART_WHEELS);


	std::cout << "done" << std::endl;
}