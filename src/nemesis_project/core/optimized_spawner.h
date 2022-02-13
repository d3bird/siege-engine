#pragma once

#include "API_data_ball.hpp"


enum item_type {
	CUBE_T, MOON_T, FLOOR_TEMP, WALL_TEMP, RAMP_T, CORNOR_RAMP_T, CORNOR_RAMP_DOWN_T, LADDER_T, CUBE_TREE_T,
	FURNACE_T, FURNACE_GEAR_T, GEAR_BEAM_T, BEAM_T, TEST_T,
	SMALL_WHEEL_T, MED_WHEEL_T, WHEEL_BLOCK_T,
	GEAR_BOX_FRAME, GEAR_BOX_G_UP, GEAR_BOX_G_DOWN, GEAR_BOX_G_L, GEAR_BOX_G_R, GEAR_BOX_G_N, GEAR_BOX_G_S,
	HEAD_T, BODY_T, LEFT_LEG, RIGHT_LEG, LEFT_ARM, RIGHT_ARM,
	CRANE_TOP, CRANE_BOT, CRANE_RAIL, CRANE_POST,
	ROATING_TURRET, TURRET_BASE, SMALL_MISSLE, SAM_ATTACH,
	DOOR_SECTION,
	LIFT_WHEEL, LIFT_CABEL, LIFT_FLOOR, LIFT_BASE,
	BELT_1, BELT_2, BELT_3, BELT_4,
	COPPER_INGOT, BARROW, CRATE,
	//more floors and walls
	CONCRETE_WALL, DIRT_WALL, STONE_WALL,
	CONCRETE_FLOOR, GRASS_FLOOR, STONE_FLOOR, TILE_FLOOR,

	CARRY_ALL_T, LANDING_PAD

};

class optimized_spawner
{
public:
	optimized_spawner();
	~optimized_spawner();

	
	item_info* spawn_item(item_type type, int x, int y, int z, glm::mat4* given_mat = NULL);
	item_info* spawn_item(item_type type, int x, int y, int z, float angle );

	
	void init(data_ball* objs);

private:

	data_ball* objs;

	object_manger* OBJM;
	timing* time;

	void import_models();

};
