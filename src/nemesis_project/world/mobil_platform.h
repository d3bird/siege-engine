#pragma once

#include <vector>

#include "terrian_data.hpp"

#include "../core/optimized_spawner.h"

class mobil_platform{
public:
	mobil_platform(local_map_data* map_in);
	~mobil_platform();

	
	void set_init_pos(int x_star, int y_star, int z_star) {
		x_start = x_star;
		y_start = y_star;
		z_start = z_star;
	}

//	void create_route_for_person(person* per, int dest_x, int dest_y, int dest_z);
//
	//void add_person_to_crew(person* per) { crew.push_back(per); }

	//work_task* place_obj_on_spot(int x, int y, int z, item_info* obj);
	//work_task* remove_obj_on_spot(int x, int y, int z);

	//work_task* replace_floor(int x, int y, int z, item_info* obj);
	//work_task* remove_floor(int x, int y, int z);
	//work_task* place_floor(int x, int y, int z, item_info* obj);

	//work_task* replace_wall(int x, int y, int z, item_info* obj);
	//work_task* mine_wall(int x, int y, int z, item_info* obj);
	//work_task* place_wall(int x, int y, int z, item_info* obj);

	//work_task* place_zone(int x, int y, int z, zone* zon);
	//work_task* remove_zone(int x, int y, int z, zone* zon);

	//void complete_task(work_task* task);

	//std::vector< person*> get_crew() { return crew; }
	//std::vector< work_task*> get_tasks() { return tasks; }


	//getters
	int get_x_size() { return x_size; }
	int get_y_size() { return y_size; }
	int get_z_size() { return z_size; }

	map_cell*** get_platform_map() { return platform_map; }
	local_map_data* get_map_info() { return map_info; }


private:
	//creates the basic map
	void init(int x_siz, int y_siz, int z_siz, optimized_spawner* OBJM = NULL);

	bool is_loc_valid(int x, int y, int z);

	void load_path_test_city(optimized_spawner* OBJM);
	void create_city_base(optimized_spawner* OBJM);

	//std::vector< work_task*> tasks;
	//std::vector< person*> crew;

	//pathing* paths;

	map_cell*** platform_map;
	local_map_data* map_info;

	int total_spaces;
	int x_size;
	int y_size;
	int z_size;

	int x_start;
	int y_start;
	int z_start;
};

