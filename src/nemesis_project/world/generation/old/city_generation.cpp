#include "city_generation.h"



city_generator::city_generator(optimized_spawner* objm) {
	OBJM = objm;

	//setting the def city size
	def_x_size = 10;
	def_y_size = 5;
	def_z_size = 10;

}

city_generator::~city_generator() {

}

local_map_data* city_generator::create_platform(int x_siz, int y_siz, int z_siz) {

	int x_size = x_siz;
	int y_size = y_siz;
	int z_size = z_siz;

	std::cout << "creating the blank map" << std::endl;
	std::cout << "x_size: " << x_size << std::endl;
	std::cout << "y_size: " << y_size << std::endl;
	std::cout << "z_size: " << z_size << std::endl;

	map_cell***platform_map = new map_cell * *[y_size];

	for (int y = 0; y < y_size; y++) {
		platform_map[y] = new   map_cell * [x_size];
		for (int x = 0; x < x_size; x++) {
			platform_map[y][x] = new map_cell[z_size];
		}
	}

	local_map_data *map_info = new local_map_data;
	map_info->x_size = x_size;
	map_info->y_size = y_size;
	map_info->z_size = z_size;
	map_info->map = platform_map;

	map_info->mobil = true;

	std::cout << "done creating the blank map" << std::endl;
	std::cout << "filling the map with def values" << std::endl;
	//creates the blank map where everything is the same tempature
	for (int y = 0; y < y_size; y++) {
		for (int x = 0; x < x_size; x++) {
			for (int z = 0; z < z_size; z++) {
				platform_map[y][x][z].x = x;
				platform_map[y][x][z].y = y;
				platform_map[y][x][z].z = z;

				platform_map[y][x][z].ground = NULL;
				platform_map[y][x][z].floor = NULL;
				platform_map[y][x][z].zone_on_top = NULL;
				platform_map[y][x][z].link_to_platform = NULL;


			}
		}
	}
	std::cout << "done filling the map" << std::endl;

	//load_path_test_city(OBJM);
	create_city_base(map_info);
	hook_wheel_box_up(map_info, false);
//	std::cout << "creating pathing system" << std::endl;
	//std::cout << "syncing with mobil city" << std::endl;


	//paths->set_cell_info(0, 0, 0, false, 0, 1);
	//paths->set_cell_info(1, 0, 0, true, 0, 1);

	//std::cout << "done with pathing" << std::endl;
	//std::cout << "adding test person" << std::endl;

	/*body* b = new body;
	head* h = new head;
	arm* left = new arm;
	arm* right = new arm;
	leg* righ_l = new leg;
	leg* left_l = new leg;
	b = build_a_person(b, h, left, right, left_l, righ_l);
	person* input = new person(b, NULL);*/

	//input->set_loc(0, 1, 0);

	//crew.push_back(input);

	std::cout << "done adding test person" << std::endl;
	return map_info;
}

local_map_data* city_generator::create_city_from_settings(city_gen_sets* settings, local_map_data* map_in) {
	if (map_in == NULL || settings == NULL) {
		return NULL;
	}

	//this is the list of the rooms that can be generated
	//it will generate a room with the area data in each list
	std::vector<area_data*> engine_room;
	std::vector<area_data*> stock_pile_crane;
	std::vector<area_data*> production;
	std::vector<area_data*> ship_bay;
	std::vector<area_data*> overlook;
	std::vector<area_data*> command;
	std::vector<area_data*> bed_rooms;
	std::vector<area_data*> barracks;
	std::vector<area_data*> mess_hall;

	int num_diff_rooms = 9;

	int* prioorty_que = create_prioorty_que_from_settings(settings);

	

	//clean mem used
	if (prioorty_que != NULL) {
		delete prioorty_que;
	}
	//break down the city


	//fill in the rooms

	return map_in;
}

local_map_data* city_generator::turn_platform_into_factory(local_map_data* input) {

	std::cout << "generating a factory city" << std::endl;

	if (input == NULL) {
		input = create_platform(def_x_size, def_y_size, def_z_size);
		if (input == NULL) {
			std::cout << "failed  to generating a factory city" << std::endl;

			return NULL;
		}
	}

	map_cell*** gridmap = input->map;

	//progress
	bool added_wheel_furnace = false;
	bool added_workshop_level = false;

	if (!added_wheel_furnace) {
		added_wheel_furnace = hook_wheel_box_up(input, false);
	}

	fill_in_edge_walls(input, 1, 1);

	if (!added_workshop_level) {
		added_workshop_level = create_production_floor(input, 2);
	}


	fill_in_edge_walls(input, 2, 2);
	fill_in_edge_walls(input, 3, 3);
	fill_in_edge_walls(input, 4, 4);
	fill_in_edge_walls(input, 5, 5);

	area_data area;

	area.start_x = 0;
	area.end_x = 25;

	area.start_y = 6;
	area.end_y = 6;

	area.start_z = 6;
	area.end_z = 6;

	create_crane(input, area);

	if (!added_wheel_furnace) {
		std::cout << "WARNING: NO WHEEL_FURNACES WHERE ADDED" << std::endl;
	}
	if (!added_workshop_level) {
		std::cout << "WARNING: NO WORKSHOPS_LEVEL WHERE ADDED" << std::endl;
	}

	std::cout << "done generating a factory city" << std::endl;
	return input;
}

bool city_generator::hook_wheel_box_up(local_map_data* input, bool just_furnace) {
	bool hooked_all_wheel_boxs = true;

	std::cout << "xsize: " << input->x_size << std::endl;
	std::cout << "ysize: " << input->y_size << std::endl;
	std::cout << "zsize: " << input->z_size << std::endl;

	if (input->Wheels != NULL) {
		size_t num_wheels = input->Wheels->wheel_blocks.size();

		map_cell*** gridmap = input->map;


		for (int i = 0; i < num_wheels; i++) {

			float angle = input->Wheels->wheel_blocks[i]->angle;
			int x_loc = input->Wheels->wheel_blocks[i]->x;
			int y_loc = input->Wheels->wheel_blocks[i]->y;
			int z_loc = input->Wheels->wheel_blocks[i]->z;

			if (angle == 0) {
				//place the GEAR_BOX_FRAME
				int box_x = x_loc - 2;
				int box_y = y_loc;
				int box_z = z_loc;

				if ((gridmap[box_y][box_x][box_z].ground == NULL &&
					input->is_inbounds_of_map_local(box_x, box_y, box_z)) &&
					(gridmap[box_y][box_x - 1][box_z].ground == NULL &&
						input->is_inbounds_of_map_local(box_x - 1, box_y, box_z))) {

					gridmap[box_y][box_x][box_z].ground = OBJM->spawn_item(GEAR_BOX_FRAME, box_x, box_y, box_z);
					gridmap[box_y][box_x - 1][box_z].ground = OBJM->spawn_item(BEAM_T, x_loc - 1, y_loc, z_loc);

					//find a spot for the furnace

					if (gridmap[box_y][box_x][box_z - 2].ground == NULL &&// gridmap[box_y][box_x][box_z - 1].ground == NULL &&
						input->is_inbounds_of_map_local(box_x, box_y, box_z - 2)) {
						gridmap[box_y][box_x][box_z - 2].ground = OBJM->spawn_item(FURNACE_T, box_x, box_y, box_z - 2);
						gridmap[box_y][box_x][box_z - 1].ground = OBJM->spawn_item(BEAM_T, box_x, box_y, box_z - 1);
					}
					else if (gridmap[box_y][box_x][box_z + 2].ground == NULL &&// gridmap[box_y][box_x][box_z + 1].ground == NULL &&
						input->is_inbounds_of_map_local(box_x, box_y, box_z + 2)) {
						gridmap[box_y][box_x][box_z + 2].ground = OBJM->spawn_item(FURNACE_T, box_x, box_y, box_z + 2);
						gridmap[box_y][box_x][box_z + 1].ground = OBJM->spawn_item(BEAM_T, box_x, box_y, box_z + 1);
					}
					//uncomment the else if multiple furnacescan be spawned here
					//else
					if (gridmap[box_y][box_x - 2][box_z].ground == NULL && //gridmap[box_y][box_x - 1][box_z].ground == NULL &&
						input->is_inbounds_of_map_local(box_x - 2, box_y, box_z)) {
						gridmap[box_y][box_x - 2][box_z].ground = OBJM->spawn_item(FURNACE_T, box_x - 2, box_y, box_z);
						gridmap[box_y][box_x - 1][box_z].ground = OBJM->spawn_item(BEAM_T, box_x - 1, box_y, box_z);
					}
					else if (gridmap[box_y][box_x + 2][box_z].ground == NULL && //gridmap[box_y][box_x + 1][box_z].ground == NULL &&
						input->is_inbounds_of_map_local(box_x + 2, box_y, box_z)) {
						gridmap[box_y][box_x + 2][box_z].ground = OBJM->spawn_item(FURNACE_T, box_x + 2, box_y, box_z);
						gridmap[box_y][box_x + 1][box_z].ground = OBJM->spawn_item(BEAM_T, box_x + 1, box_y, box_z);
					}
				}
				else {
					std::cout << "can not place the base parts for the wheel block" << std::endl;
					hooked_all_wheel_boxs = false;
				}

			}
			else if (angle == 180) {
				//OBJM->spawn_item(GEAR_BOX_FRAME, x_loc + 2, y_loc, z_loc);
				//OBJM->spawn_item(BEAM_T, x_loc + 1, y_loc, z_loc);

				//place the GEAR_BOX_FRAME
				int box_x = x_loc + 2;
				int box_y = y_loc;
				int box_z = z_loc;

				if ((gridmap[box_y][box_x][box_z].ground == NULL &&
					input->is_inbounds_of_map_local(box_x, box_y, box_z)) &&
					(gridmap[box_y][box_x + 1][box_z].ground == NULL &&
						input->is_inbounds_of_map_local(box_x + 1, box_y, box_z))) {

					gridmap[box_y][box_x][box_z].ground = OBJM->spawn_item(GEAR_BOX_FRAME, box_x, box_y, box_z);
					gridmap[box_y][box_x + 1][box_z].ground = OBJM->spawn_item(BEAM_T, x_loc + 1, y_loc, z_loc);

					//find a spot for the furnace

					if (gridmap[box_y][box_x][box_z + 2].ground == NULL && //gridmap[box_y][box_x][box_z + 1].ground == NULL &&
						input->is_inbounds_of_map_local(box_x, box_y, box_z + 2)) {
						gridmap[box_y][box_x][box_z + 2].ground = OBJM->spawn_item(FURNACE_T, box_x, box_y, box_z + 2);
						gridmap[box_y][box_x][box_z + 1].ground = OBJM->spawn_item(BEAM_T, box_x, box_y, box_z + 1);
					}
					else if (gridmap[box_y][box_x][box_z - 2].ground == NULL &&// gridmap[box_y][box_x][box_z - 1].ground == NULL &&
						input->is_inbounds_of_map_local(box_x, box_y, box_z - 2)) {
						gridmap[box_y][box_x][box_z - 2].ground = OBJM->spawn_item(FURNACE_T, box_x, box_y, box_z - 2);
						gridmap[box_y][box_x][box_z - 1].ground = OBJM->spawn_item(BEAM_T, box_x, box_y, box_z - 1);
					}
					//uncomment the else if multiple furnacescan be spawned here
					//else
					if (gridmap[box_y][box_x + 2][box_z].ground == NULL && //gridmap[box_y][box_x + 1][box_z].ground == NULL &&
						input->is_inbounds_of_map_local(box_x - 2, box_y, box_z)) {
						gridmap[box_y][box_x + 2][box_z].ground = OBJM->spawn_item(FURNACE_T, box_x + 2, box_y, box_z);
						gridmap[box_y][box_x + 1][box_z].ground = OBJM->spawn_item(BEAM_T, box_x + 1, box_y, box_z);
					}
					else if (gridmap[box_y][box_x - 2][box_z].ground == NULL && //gridmap[box_y][box_x - 1][box_z].ground == NULL &&
						input->is_inbounds_of_map_local(box_x - 2, box_y, box_z)) {
						gridmap[box_y][box_x - 2][box_z].ground = OBJM->spawn_item(FURNACE_T, box_x - 2, box_y, box_z);
						gridmap[box_y][box_x - 1][box_z].ground = OBJM->spawn_item(BEAM_T, box_x - 1, box_y, box_z);
					}
				}
				else {
					std::cout << "can not place the base parts for the wheel block" << std::endl;
					hooked_all_wheel_boxs = false;
				}


			}
			else {
				std::cout << "following wheel failed to generate furnaces" << std::endl;
				std::cout << "angle: " << angle << " at " << x_loc << "," << y_loc << "," << z_loc << std::endl;
				hooked_all_wheel_boxs = false;
			}

		}


	}

	return hooked_all_wheel_boxs;
}

bool city_generator::create_production_floor(local_map_data* input, int floor) {
	bool ran_without_problems = true;

	if (input == NULL) {
		return false;
	}

	for (int i = 0; i < input->y_size; i++) {
		clear_checked(i, input);
	}

	//create the floor
	fill_in_edge_walls(input, floor, floor);
	fill_in_floor(input, floor);
	//amount_possible_split_floor_into_rooms(input, floor, 2, 2);
	split_floor_into_rooms(input, floor, 2, 2);



	return ran_without_problems;
}

bool city_generator::fill_in_edge_walls(local_map_data* map_in, int start, int end) {
	bool ran_without_problems = true;

	//std::cout << "adding in walls, start: " << start << ", end: " << end<<std::endl;

	if (map_in == NULL) {
		std::cout << "input was null" << std::endl;
		return false;
	}

	//checking and correcting the input
	if (end < 0) {
		end = 0;
	}

	if (start < 0) {
		start = 0;
	}

	if (start > end) {
		int temp = start;
		start = end;
		end = temp;
	}

	int x_size = map_in->x_size;
	int y_size = map_in->y_size;
	int z_size = map_in->z_size;

	if (start >= y_size || end >= y_size) {
		std::cout << "is taller than the map cell" << std::endl;
		return false;
	}

	//	std::cout << "after checks, start: " << start << ", end: "<<end << std::endl;
	if (start == end) {
		//only one floor

		int y = start;
	
		for (int x = 0; x < x_size; x++) {
			for (int z = 0; z < z_size; z++) {
				if (x == 0 || x == x_size - 1 || z == 0 || z == z_size - 1) {
					if (map_in->map[y][x][z].ground == NULL) {
						map_in->map[y][x][z].ground = OBJM->spawn_item(WALL_TEMP, x, y, z);
					}
					if (map_in->map[y][x][z].floor == NULL) {
						map_in->map[y][x][z].floor = OBJM->spawn_item(FLOOR_TEMP, x, y, z);
					}
				}
			}
		}

	}
	else {
		//multiple floors

		for (int y = start; y < end; y++) {
			for (int x = 0; x < x_size; x++) {
				for (int z = 0; z < z_size; z++) {
					if (x == 0 || x == x_size-1 || z == 0 || z == z_size - 1) {
						if (map_in->map[y][x][z].ground == NULL) {
							map_in->map[y][x][z].ground = OBJM->spawn_item(WALL_TEMP, x, y, z);
						}
						if (map_in->map[y][x][z].floor == NULL) {
							map_in->map[y][x][z].floor = OBJM->spawn_item(FLOOR_TEMP, x, y, z);
						}
					}
				}
			}
		}

	}

	return ran_without_problems;
}

bool city_generator::fill_in_floor(local_map_data* map_in, int floor) {
	bool ran_without_problems = true;

	if (map_in == NULL || floor < 0) {
		return false;
	}

	if (floor >= map_in->y_size) {
		return false;
	}

	int x_size = map_in->x_size;
	int y_size = map_in->y_size;
	int z_size = map_in->z_size;

	int y = floor;

	for (int x = 0; x < x_size; x++) {
		for (int z = 0; z < z_size; z++) {
			if (map_in->map[y][x][z].floor == NULL) {
				map_in->map[y][x][z].floor = OBJM->spawn_item(FLOOR_TEMP, x, y, z);
			}
		}
	}

	return ran_without_problems;
}

int city_generator::amount_possible_split_floor_into_rooms(local_map_data* map_in, int floor, int r_width, int r_length) {
	if (map_in == NULL) {
		return -1;
	}

	if (floor < 0 || floor >= map_in->y_size) {
		return -1;
	}

	if (r_width < 0 || r_length < 0) {
		return -1;
	}

	area_data area;
	area.start_x = 0;
	area.start_y = floor;
	area.start_z = 0;

	area.end_x = map_in->x_size-1;
	area.end_y = floor;
	area.end_z = map_in->z_size - 1;

	return amount_possible_split_area_into_rooms(map_in, floor, r_width, r_length, area);
}

int city_generator::split_floor_into_rooms(local_map_data* map_in, int floor, int r_width, int r_length) {
	if (map_in == NULL) {
		return -1;
	}

	if (floor < 0 || floor >= map_in->y_size) {
		return -1;
	}

	if (r_width < 0 || r_length < 0) {
		return -1;
	}

	area_data area;
	area.start_x = 0;
	area.start_y = floor;
	area.start_z = 0;

	area.end_x = map_in->x_size - 1;
	area.end_y = floor;
	area.end_z = map_in->z_size - 1;

	return split_area_into_rooms(map_in, floor, r_width, r_length, area);
}

//this function works off the assumption that each room has a wall around it
int city_generator::amount_possible_split_area_into_rooms(local_map_data* map_in, int floor, int r_width, int r_length, area_data& area) {
	if (map_in == NULL) {
		return -1;
	}

	if (floor < 0 || floor >= map_in->y_size) {
		return -1;
	}

	if (r_width < 0 || r_length < 0) {
		return -1;
	}

	std::cout << "amount_possible_split_area_into_rooms" << std::endl;

	//need to add the walls into the room length
	r_width += 1;//x  size
	r_length += 1;//z size

	int x_size = area.end_x - area.start_x;
	int z_size = area.end_z - area.start_z;

	bool vertical_halls = true;

	int hall_size = 1;

	int collums = (x_size) / (r_width + hall_size);

	int rows = (z_size) / (r_length);

	int room_amount = collums * rows;

	/*std::cout << "x_size for rooms is:" << x_size << std::endl;
	std::cout << "z_size for rooms is:" << z_size << std::endl;

	std::cout << "r_width for rooms is:" << r_width << std::endl;
	std::cout << "r_length for rooms is:" << r_length << std::endl;

	std::cout << "hall size:" << hall_size << std::endl;
	std::cout << "collums amount:" << collums << std::endl;
	std::cout << "rows amount:" << rows << std::endl;

	std::cout << "room amount:" << room_amount << std::endl;*/



	std::cout << "done with amount_possible_split_area_into_rooms" << std::endl;

	return room_amount;
}

//this function works off the assumption that each room has a wall around it
int city_generator::split_area_into_rooms(local_map_data* map_in, int floor, int r_width, int r_length, area_data& area) {
	bool check = true;
	int rooms_placed = 0;

	if (map_in == NULL) {
		return -1;
	}

	if (floor < 0 || floor >= map_in->y_size) {
		return -1;
	}

	if (r_width < 0 || r_length < 0) {
		return -1;
	}

	std::cout << "split_area_into_rooms" << std::endl;

	//need to add the walls into the room length
	r_width += 1;//x  size
	r_length += 1;//z size

	int x_size = area.end_x - area.start_x;
	int z_size = area.end_z - area.start_z;

	bool vertical_halls = true;

	int hall_size = 1;

	int collums = (x_size) / (r_width + hall_size);

	int rows = (z_size) / (r_length);

	int room_amount = collums * rows;


	int y = floor;

	int x = area.start_x;
	int z = area.start_z;
	bool placing = true;

	while (placing) {


		if (map_in->is_inbounds_of_map_local(x, y, z)) {

			/*	if (x + r_width >= map_in->x_size || z + r_length >= map_in->z_size) {
					std::cout << "ROOM WOULD HAVE GONE OUT OF BOUNDS" << std::endl;
					break;
				}*/

				//place the room

			if (map_in->map[y][x][z].ground == NULL) {
				map_in->map[y][x][z].ground = OBJM->spawn_item(FURNACE_T, x, y, z);
			}


			std::cout << "room start at " << x << "," << x << std::endl;


			x += r_width;

			if (x >= map_in->x_size) {
				x = area.start_x;
				z += r_length;
				if (z >= map_in->z_size) {
					placing = false;
				}
			}
		}
		else {
			std::cout << "ERROR WAS OUT OF BOUNDS WHILE PLACING ROOMS, ABORTING " << std::endl;
			placing = false;
		}



	}

	if (check) {
		int should_be = amount_possible_split_area_into_rooms(map_in, floor, r_width, r_length, area);
		if (should_be != -1) {
			std::cout << "should have placed " << should_be << " rooms" << std::endl;
			std::cout << "placed " << rooms_placed << " rooms" << std::endl;
		}
		else {
			std::cout << "recived errors from amount_possible_split_area_into_rooms" << std::endl;
		}
	}

	std::cout << "done" << std::endl;

	return rooms_placed;
}

//TODO:
bool city_generator::check_fix_area(area_data& check, local_map_data* map_in) {

	if (check.been_checked) {
		return true;
	}

	bool made_change = false;

	if (check.start_y < 0) {
		check.start_y = 0;
		made_change = true;
	}

	if (check.end_y >= map_in->y_size) {
		check.end_y = map_in->y_size - 1;
		made_change = true;
	}

	if (check.start_x < 0) {
		check.start_x = 0;
		made_change = true;
	}

	if (check.end_x >= map_in->x_size) {
		check.end_x = map_in->x_size - 1;
		made_change = true;
	}
	
	if (check.start_z < 0) {
		check.start_z = 0;
		made_change = true;
	}

	if (check.end_z >= map_in->z_size) {
		check.end_z = map_in->z_size - 1;
		made_change = true;
	}

	if (check.start_y > check.end_y) {
		int temp = check.start_y;
		check.start_y = check.end_y;
		check.end_y = temp;
		made_change = true;
	}

	if (check.start_x > check.end_x) {
		int temp = check.start_x;
		check.start_x = check.end_x;
		check.end_x = temp;
		made_change = true;
	}

	if (check.start_z > check.end_z) {
		int temp = check.start_z;
		check.start_z = check.end_z;
		check.end_z = temp;
		made_change = true;
	}

	check.been_checked = true;
	check.made_changes = made_change;

	return !made_change;
}

void city_generator::create_crane(local_map_data* map_in, area_data& area) {
	if (map_in == NULL) {
		return;
	}

	std::cout << "placeing crane" << std::endl;

	if (!check_fix_area(area, map_in)) {
		std::cout << "area was checked and changes where made" << std::endl;
	}

	bool area_placement;
	bool x_dir = false;
	bool z_dir = false;
	//determin if the crane moves strieght across or in a area

	if (area.start_x == area.end_x) {
		area_placement = false;
		x_dir = true;
	}
	else if (area.start_z == area.end_z) {
		area_placement = false;
		z_dir = true;
	}
	else {
		area_placement = true;
	}

	int y = area.start_y;

	if (area_placement) {
		//place crane over an area
	}
	else {
		//place the crane over a line

		if (x_dir) {
			int x = area.start_x;

			for (int z = area.start_z; z < area.end_z; z++) {
				if (map_in->map[y][x][z].ground == NULL) {
					if (z == area.start_z || z == area.start_z - 1) {
						map_in->map[y][x][z].ground = OBJM->spawn_item(CRANE_POST, x, y, z);
					}
					else {
						map_in->map[y][x][z].ground = OBJM->spawn_item(CRANE_RAIL, x, y, z);
					}
				}
			}
		}
		else {
			int z = area.start_z;
			int mid = (area.end_x - area.start_x) / 2;
			for (int x = area.start_x; x < area.end_x; x++) {
				if (map_in->map[y][x][z].ground == NULL) {
					if (x == area.start_x || x == area.start_x - 1) {
						map_in->map[y][x][z].ground = OBJM->spawn_item(CRANE_POST, x, y, z);
						if (map_in->map[y][x][z].floor == NULL) {
							map_in->map[y][x][z].floor = OBJM->spawn_item(FLOOR_TEMP, x, y, z);
						}
					}
					else if (x == area.start_x + mid) {
						map_in->map[y][x][z].ground = OBJM->spawn_item(CRANE_TOP, x, y, z, 90);
						map_in->map[y][x][z].ground = OBJM->spawn_item(CRANE_BOT, x, y, z, 90);
					}
					else  {
						map_in->map[y][x][z].ground = OBJM->spawn_item(CRANE_RAIL, x, y, z, 90);
					}
				}

			}
		}

	}
	std::cout << "done placeing crane" << std::endl;

}

void city_generator::create_city_base(local_map_data* map_in) {

	std::cout << "create_city_base" << std::endl;

	if (map_in == NULL) {
		std::cout << "map_in was null" << std::endl;
		return;
	}

	if (map_in->map == NULL) {
		std::cout << "map_in->map was null" << std::endl;
		return;
	}

	map_cell*** platform_map = map_in->map;

	//clear the map
	for (int y = 0; y < map_in->y_size; y++) {
		for (int x = 0; x < map_in->x_size; x++) {
			for (int z = 0; z < map_in->z_size; z++) {
				platform_map[y][x][z].x = x;
				platform_map[y][x][z].y = y;
				platform_map[y][x][z].z = z;


				platform_map[y][x][z].floor = NULL;
				platform_map[y][x][z].ground = NULL;

				platform_map[y][x][z].zone_on_top = NULL;
				platform_map[y][x][z].link_to_platform = NULL;
			}
		}
	}

	int y = 0;
	for (int x = 0; x < map_in->x_size; x++) {
		for (int z = 0; z < map_in->z_size; z++) {

			//generate the wheel holes
			if ((x == 0 && z == map_in->z_size - 3) ||
				(x == 0 && z == 2)) {
				platform_map[y][x][z].ground = OBJM->spawn_item(WHEEL_BLOCK_T, x, y, z, 180);
				//Wheels->wheel_blocks.push_back(platform_map[y][x][z].ground);
			}
			else if ((x == map_in->x_size - 1 && z == map_in->z_size - 3) ||
				(x == map_in->x_size - 1 && z == 2)) {
				platform_map[y][x][z].ground = OBJM->spawn_item(WHEEL_BLOCK_T, x, y, z);
			//	Wheels->wheel_blocks.push_back(platform_map[y][x][z].ground);
			}
			//generate the rest of the base
			else {

				//place the base frame
				platform_map[y][x][z].floor = OBJM->spawn_item(FLOOR_TEMP, x, y, z);
				if (x == 0 || x == map_in->x_size - 1 || z == 0 || z == map_in->z_size - 1) {
					platform_map[y][x][z].ground = OBJM->spawn_item(WALL_TEMP, x, y, z);
				}
			}
		}
	}

	place_wheel_on_city(map_in);
}

void city_generator::place_wheel_on_city(local_map_data* input) {

	wheels* Wheels = new wheels;

	int wheel_type = 0; //0 = small, 1 = med, 2 = large

	//place the baselayer and wall around the ground
	for (int y = 0; y < input->y_size; y++) {
		for (int x = 0; x < input->x_size; x++) {
			for (int z = 0; z < input->z_size; z++) {
				if (input->map[y][x][z].ground != NULL) {
					if (input->map[y][x][z].ground->type == WHEEL_BLOCK_T) {
						Wheels->wheel_blocks.push_back(input->map[y][x][z].ground);
					}
				}

			}
		}
	}

	//placing wheels
	for (int i = 0; i < Wheels->wheel_blocks.size(); i++) {
		wheel* temp = new wheel;
		int x = Wheels->wheel_blocks[i]->x;
		int y = Wheels->wheel_blocks[i]->y;
		int z = Wheels->wheel_blocks[i]->z;

		float angle = 0;

		if (Wheels->wheel_blocks[i]->angle == 90) {

		}
		else if (Wheels->wheel_blocks[i]->angle == 180) {
			x -= 4;
			angle = 180;
		}
		if (Wheels->wheel_blocks[i]->angle == 270) {

		}
		else {
			x += 2;
		}
		//Wheels->wheel_blocks[i]->angle == 0:


		temp->obj = OBJM->spawn_item(SMALL_WHEEL_T, x, y, z, angle);
		temp->wheel_block_link = Wheels->wheel_blocks[i];
		Wheels->wheels.push_back(temp);
	}

	std::cout << "information about the wheels" << std::endl;
	std::cout << "wheel blocks:" << Wheels->wheel_blocks.size() << std::endl;
	std::cout << "wheels:      " << Wheels->wheels.size() << std::endl;


	input->Wheels = Wheels;
}

//default generation functions

//generates the def for every room
city_gen_sets* city_generator::generate_def_gen_room_info() {

	city_gen_sets* output = new city_gen_sets;
	output->rooms_to_gen.push_back(generate_def_gen_room_engine());
	output->rooms_to_gen.push_back(generate_def_gen_room_stock_pile());
	output->rooms_to_gen.push_back(generate_def_gen_room_crane_col());
	output->rooms_to_gen.push_back(generate_def_gen_room_production());
	output->rooms_to_gen.push_back(generate_def_gen_room_ship_bay());
	output->rooms_to_gen.push_back(generate_def_gen_room_overlook());
	output->rooms_to_gen.push_back(generate_def_gen_room_command());
	output->rooms_to_gen.push_back(generate_def_gen_room_bed_room());
	output->rooms_to_gen.push_back(generate_def_gen_room_barracks());
	output->rooms_to_gen.push_back(generate_def_gen_room_mess_hall());

	return output;
}

gen_room_info* city_generator::generate_def_gen_room_engine() {
	gen_room_info* temp = new gen_room_info;

	temp->type = ENGINE;
	temp->min_x_size = 2;
	temp->min_y_size = 1;
	temp->min_z_size = 2;
	temp->des_x_size = 2;
	temp->des_y_size = 1;
	temp->des_z_size = 2;
	temp->exposed_to_sky = false;
	temp->connected_to_crane = false;
	temp->place_floors = true;
	temp->place_walls = false;
	temp->placement_priority = 0;

	return temp;
}

gen_room_info* city_generator::generate_def_gen_room_stock_pile() {
	return NULL;
}
gen_room_info* city_generator::generate_def_gen_room_crane_col() {
	return NULL;

}
gen_room_info* city_generator::generate_def_gen_room_production() {
	return NULL;

}
gen_room_info* city_generator::generate_def_gen_room_ship_bay() {
	return NULL;

}
gen_room_info* city_generator::generate_def_gen_room_overlook() {
	return NULL;

}
gen_room_info* city_generator::generate_def_gen_room_command() {
	return NULL;

}
gen_room_info* city_generator::generate_def_gen_room_bed_room() {
	return NULL;

}
gen_room_info* city_generator::generate_def_gen_room_barracks() {
	return NULL;

}
gen_room_info* city_generator::generate_def_gen_room_mess_hall() {
	return NULL;

}

int* city_generator::create_prioorty_que_from_settings(city_gen_sets* settings) {

	int* prioorty_que_vaule = NULL;
	int* prioorty_que = NULL;

	int num_diff_rooms = 10;

	prioorty_que_vaule = new int[num_diff_rooms];
	prioorty_que = new int[num_diff_rooms];


	for (int i = 0; i < num_diff_rooms; i++) {
		prioorty_que[i] = -1;
		prioorty_que_vaule[i] = -1;
	}

	for (int i = 0; i < settings->rooms_to_gen.size(); i++) {
		int index = -1;
		switch (settings->rooms_to_gen[i]->type)
		{
		case ENGINE:
			index = 0;
			break;
		case STOCK_PILE:
			index = 1;
			break;
		case CRANE_COL:
			index = 2;
			break;
		case PRODUCTION:
			index = 3;
			break;
		case SHIP_BAY:
			index = 4;
			break;
		case OVERLOOK:
			index = 5;
			break;
		case COMMAND:
			index = 6;
			break;
		case BED_ROOM:
			index = 7;
			break;
		case BARRACKS:
			index = 8;
			break;
		case MESS_HALL:
			index = 9;
			break;
		}
		if (index != -1) {
			prioorty_que[index] = index;
			if (prioorty_que[index] > settings->rooms_to_gen[i]->placement_priority) {
				prioorty_que[index] = settings->rooms_to_gen[i]->placement_priority;
			}
		}
	}


	prioorty_que_vaule = NULL;

	return prioorty_que;
}