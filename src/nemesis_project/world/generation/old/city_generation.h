#pragma once

#include "../../object_data.hpp"
#include "../../../utility/logger.h"
#include <time.h>

#include "../../../core/optimized_spawner.h"
#include "../../terrian_data.hpp"

#include "../../../utility/random_gen.hpp"

#include "../../mobil_platform.h"

#include <vector>

/*This is the city generation class, it creates the mobil the citys that wander the world
* 
* the city_gen_sets struct contains the information that the determins how to break down the
* platform into smaller sections for each purpose
* 
* the processes for generating a city
* 1. define a area for the city
* 2. create the outside of the city
* 3. break down the inside into areas for the differnt rooms
* 4. fill in the related rooms
*/

enum city_gen_room {ENGINE, STOCK_PILE, CRANE_COL, PRODUCTION,
	SHIP_BAY, OVERLOOK, COMMAND,BED_ROOM,BARRACKS, MESS_HALL };

struct gen_room_info {

	city_gen_room type;

	int min_x_size = 2;
	int min_y_size = 1;
	int min_z_size = 2;

	//desirded size
	int des_x_size = 2;
	int des_y_size = 1;
	int des_z_size = 2;

	bool exposed_to_sky = false;
	bool connected_to_crane = false;


	//if an area does not have floors then place floors
	bool place_floors = true;
	bool place_walls = false;


	//determins the order that the 
	int placement_priority = 0;
};

struct city_gen_sets {
	std::vector< gen_room_info*> rooms_to_gen;
};

//this class creates local_map_data and modifys local_map_data to create differnt worlds
class city_generator {
public:
	city_generator(optimized_spawner* objm);
	~city_generator();

	//creates a blank platform
	local_map_data* create_platform(int x_siz, int y_siz, int z_siz);
	
	//creates a platfrom from generation settings
	local_map_data* create_city_from_settings(city_gen_sets* settings, local_map_data* map_in);

	local_map_data* turn_platform_into_factory(local_map_data* input = NULL);

	void place_wheel_on_city(local_map_data* input);

	//create defult generation settings
	city_gen_sets* generate_def_gen_room_info();

	gen_room_info* generate_def_gen_room_engine();
	gen_room_info* generate_def_gen_room_stock_pile();
	gen_room_info* generate_def_gen_room_crane_col();
	gen_room_info* generate_def_gen_room_production();
	gen_room_info* generate_def_gen_room_ship_bay();
	gen_room_info* generate_def_gen_room_overlook();
	gen_room_info* generate_def_gen_room_command();
	gen_room_info* generate_def_gen_room_bed_room();
	gen_room_info* generate_def_gen_room_barracks();
	gen_room_info* generate_def_gen_room_mess_hall();

private:

	int def_x_size;
	int def_y_size;
	int def_z_size;


	/* Bellow are the creation functions used to create differnt parts of the city
	* the top collection is used for generic tasks
	* the bottom collection is used for spefic tasks
	* all functions will return a bool specficiing if they compleated without error
	*/

	struct area_data {
		int start_x = 0;
		int start_y = 0;
		int start_z = 0;

		int end_x = 0;
		int end_y = 0;
		int end_z = 0;

		bool been_checked = false;
		bool made_changes = false;
	};

	bool check_fix_area(area_data& check, local_map_data* map_in);

	//generic creation function
	void create_city_base(local_map_data* map_in);
	bool fill_in_edge_walls(local_map_data* map_in, int start, int end);
	bool fill_in_floor(local_map_data* map_in, int floor);

	int amount_possible_split_floor_into_rooms(local_map_data* map_in, int floor, int r_width, int r_length);
	int split_floor_into_rooms(local_map_data* map_in, int floor, int r_width, int r_length);

	int amount_possible_split_area_into_rooms(local_map_data* map_in, int floor, int r_width, int r_length,area_data& area);
	int split_area_into_rooms(local_map_data* map_in, int floor, int r_width, int r_length, area_data &area);

	void create_crane(local_map_data* map_in, area_data& area);

	int* create_prioorty_que_from_settings(city_gen_sets* settings);

	//specific creation functions

	//hooks the wheelbox up to a gearbox or a furnace on whatever floor they are on
	bool hook_wheel_box_up(local_map_data* input, bool just_furnace);

	//create a production floor
	bool create_production_floor(local_map_data* input, int floor);


	optimized_spawner* OBJM;

};

