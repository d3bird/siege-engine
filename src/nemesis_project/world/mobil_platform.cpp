#include "mobil_platform.h"


mobil_platform::mobil_platform(local_map_data* map_in) {
	map_info = NULL;

	map_info = map_in;
}

mobil_platform::~mobil_platform() {

}

//void mobil_platform::complete_task(work_task* task) {
//
//
//}


void mobil_platform::init(int x_siz, int y_siz, int z_siz, optimized_spawner* OBJM) {
	x_size = x_siz;
	y_size = y_siz;
	z_size = z_siz;

	std::cout << "creating the blank map" << std::endl;
	std::cout << "x_size: " << x_size << std::endl;
	std::cout << "y_size: " << y_size << std::endl;
	std::cout << "z_size: " << z_size << std::endl;

	platform_map = new map_cell * *[y_size];

	for (int y = 0; y < y_size; y++) {
		platform_map[y] = new   map_cell * [x_size];
		for (int x = 0; x < x_size; x++) {
			platform_map[y][x] = new map_cell[z_size];
		}
	}

	map_info = new local_map_data;
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
	create_city_base(OBJM);

	std::cout << "creating pathing system" << std::endl;
	std::cout << "syncing with mobil city" << std::endl;
	

	//paths->set_cell_info(0, 0, 0, false, 0, 1);
	//paths->set_cell_info(1, 0, 0, true, 0, 1);

	std::cout << "done with pathing" << std::endl;
	std::cout << "adding test person" << std::endl;

	//body* b = new body;
	//head* h = new head;
	//arm* left = new arm;
	//arm* right = new arm;
	//leg* righ_l = new leg;
	//leg* left_l = new leg;
	////b = build_a_person(b, h, left, right, left_l, righ_l);
	//person* input = new person(b, NULL, -2);

	//input->set_loc(0, 1, 0);

	//crew.push_back(input);

	std::cout << "done adding test person" << std::endl;
}
//
//void mobil_platform::create_route_for_person(person* per, int dest_x, int dest_y, int dest_z) {
//
//	int start_x = per->get_x();
//	int start_y = per->get_y();
//	int start_z = per->get_z();
//
//	
//}
//
//work_task* mobil_platform::place_obj_on_spot(int x, int y, int z, item_info* obj) {
//
//	work_task* output =NULL;
//
//	if(is_loc_valid(x, y, z) && obj != NULL){
//		output = new work_task;
//		output->dest_x = x;
//		output->dest_y = y;
//		output->dest_z = z;
//
//		output->act = CONSTRUCT;
//		output->sub_con = CONSTRUCT_OBJ;
//
//		output->obj_interaction = obj;
//	}
//
//	return output;
//}
//
//work_task* mobil_platform::remove_obj_on_spot(int x, int y, int z) {
//	return NULL;
//}
//
//work_task* mobil_platform::replace_floor(int x, int y, int z, item_info* obj) {
//	return NULL;
//}
//
//work_task* mobil_platform::remove_floor(int x, int y, int z) {
//	return NULL;
//}
//
//work_task* mobil_platform::place_floor(int x, int y, int z, item_info* obj) {
//	return NULL;
//}
//
//work_task* mobil_platform::replace_wall(int x, int y, int z, item_info* obj) {
//	return NULL;
//}
//
//work_task* mobil_platform::mine_wall(int x, int y, int z, item_info* obj) {
//	return NULL;
//}
//
//work_task* mobil_platform::place_wall(int x, int y, int z, item_info* obj) {
//	return NULL;
//}
//
//work_task* mobil_platform::place_zone(int x, int y, int z, zone* zon) {
//	return NULL;
//}
//
//work_task* mobil_platform::remove_zone(int x, int y, int z, zone* zon) {
//	return NULL;
//}

bool mobil_platform::is_loc_valid(int x, int y, int z) {
	return (x >= 0 && x < x_size) &&
		(y >= 0 && y < y_size) &&
		(z >= 0 && z < z_size);
}

void mobil_platform::load_path_test_city(optimized_spawner* OBJM) {

	bool load_refernce_cubes = false;
	bool load_pathing_test2d = false;
	bool load_pathing_test2d2 = false;
	bool load_pathing_test3d = true;
	bool load_test_city = false;
	if (OBJM != NULL) {
		std::cout << "OBJM was not null, creating a blank platform" << std::endl;

		if (load_refernce_cubes) {
			OBJM->spawn_item(CUBE_T, -1, 0, -1);
			OBJM->spawn_item(CUBE_T, 0, 0, -1);
			OBJM->spawn_item(CUBE_T, 1, 0, -1);
			OBJM->spawn_item(CUBE_T, 2, 0, -1);
			OBJM->spawn_item(CUBE_T, -1, 0, 0);
			OBJM->spawn_item(CUBE_T, -1, 0, 1);
			OBJM->spawn_item(CUBE_T, -1, 0, 2);
		}

		int pathing2d_x_size = 9;
		int pathing2d_z_size = 10;
		int pathing2d[9][10] =
		{
			{ 1, 0, 1, 1, 1, 2, 0, 1, 1, 1 },
			{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
			{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
			{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
			{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
			{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
			{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
			{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
			{ 1, 1, 1, 0, 0, 4, 1, 0, 0, 1 }
		};

		int pathing2d_level2[9][10] =
		{
			{ -1, -1, -1, -1, -1, -3, 0, 1, 1, 1 },
			{ -1, -1, -1, -1, -1, 1, 1, 0, 1, 1 },
			{ -1, -1, -1, -1, -1, 1, 0, 1, 0, 1 },
			{ -1, -1, -1, -1, -1, 0, 0, 0, 0, 1 },
			{ -1, -1, -1, -1, -1, 1, 1, 0, 1, 0 },
			{ -1, -1, -1, -1, -1, 1, 0, 1, 0, 0 },
			{ -1, -1, -1, -1, -1, 1, 0, 0, 0, 1 },
			{ -1, -1, -1, -1, -1, 1, 0, 1, 1, 1 },
			{ -1, -1, -1, -1, -1, -3, 1, 0, 0, 1 }
		};

		for (int y = 0; y < y_size; y++) {
			for (int x = 0; x < x_size; x++) {
				for (int z = 0; z < z_size; z++) {
					glm::mat4 temp = glm::mat4(1.0f);

					//temp = glm::translate(temp, glm::vec3(x * 2, y, z * 2));
					platform_map[y][x][z].x = x;
					platform_map[y][x][z].y = y;
					platform_map[y][x][z].z = z;

					//platform_map[y][x][z].ground = OBJM->spawn_item(CUBE_T, x, y, z, &temp);
					
					if (load_test_city) {
						if (y == 0) {
							if (x != 0) {
								platform_map[y][x][z].ground = OBJM->spawn_item(WALL_TEMP, x, y, z);
							}
						}
						platform_map[y][x][z].floor = OBJM->spawn_item(FLOOR_TEMP, x, y, z);
						platform_map[y][x][z].zone_on_top = NULL;
						platform_map[y][x][z].link_to_platform = NULL;
					}
					else if (load_pathing_test2d) {
						if (y == 0) {
							if (pathing2d_x_size <= x || pathing2d_z_size <= z) {
								platform_map[y][x][z].ground = OBJM->spawn_item(WALL_TEMP, x, y, z);
							}
							else if (pathing2d[x][z] == 0) {
								platform_map[y][x][z].ground = OBJM->spawn_item(WALL_TEMP, x, y, z);
							}


							platform_map[y][x][z].floor = OBJM->spawn_item(FLOOR_TEMP, x, y, z);
							platform_map[y][x][z].zone_on_top = NULL;
							platform_map[y][x][z].link_to_platform = NULL;
						}
					}
					else if (load_pathing_test2d2) {
						int y = 0;


						platform_map[y][x][z].floor = OBJM->spawn_item(FLOOR_TEMP, x, y, z);
						platform_map[y][x][z].zone_on_top = NULL;
						platform_map[y][x][z].link_to_platform = NULL;
					}
					else if (load_pathing_test3d) {
						if (y == 0) {
							if (pathing2d_x_size <= x || pathing2d_z_size <= z) {
								platform_map[y][x][z].ground = OBJM->spawn_item(WALL_TEMP, x, y, z);
							}
							else if (pathing2d[x][z] == 0) {
								platform_map[y][x][z].ground = OBJM->spawn_item(WALL_TEMP, x, y, z);
							}
							else if (pathing2d[x][z] == 2) {
								platform_map[y][x][z].ground = OBJM->spawn_item(CORNOR_RAMP_T, x, y, z);
							}
							else if (pathing2d[x][z] == 4) {
								platform_map[y][x][z].ground = OBJM->spawn_item(RAMP_T, x, y, z);
							}



							platform_map[y][x][z].floor = OBJM->spawn_item(FLOOR_TEMP, x, y, z);
							platform_map[y][x][z].zone_on_top = NULL;
							platform_map[y][x][z].link_to_platform = NULL;
						}
						else {

							if (pathing2d_level2[x][z] == 0) {
								platform_map[y][x][z].ground = OBJM->spawn_item(WALL_TEMP, x, y, z);
							}
							else if (pathing2d_level2[x][z] == 0) {

							}
							if (pathing2d_level2[x][z] >= 0) {
								platform_map[y][x][z].floor = OBJM->spawn_item(FLOOR_TEMP, x, y, z);
								platform_map[y][x][z].zone_on_top = NULL;
								platform_map[y][x][z].link_to_platform = NULL;
							}
						}
					}

				}
			}
		}
		
		if (load_pathing_test2d2) {
			int x = 0;
			int y = 0;
			int z = 1;
			platform_map[y][x][z].ground = OBJM->spawn_item(WALL_TEMP, x, y, z);

		}
		
		std::cout << "done creating a blank platform" << std::endl;

	}

}

void mobil_platform::create_city_base(optimized_spawner* OBJM) {

	std::cout << "create_city_base" << std::endl;

	if (OBJM == NULL) {
		std::cout << "OBJM was  null" << std::endl;
		return;
	}

	//clear the map
	for (int y = 0; y < y_size; y++) {
		for (int x = 0; x < x_size; x++) {
			for (int z = 0; z < z_size; z++) {
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

	wheels* Wheels = new wheels;

	int wheel_type = 0; //0 = small, 1 = med, 2 = large

	//place the baselayer and wall around the ground
	int y = 0;
	for (int x = 0; x < x_size; x++) {
		for (int z = 0; z < z_size; z++) {
			
			//generate the wheel holes
			if ((x == 0 && z == z_size - 2) ||
				(x == 0 && z == 1)) {
				platform_map[y][x][z].ground = OBJM->spawn_item(WHEEL_BLOCK_T, x, y, z, 180);
				Wheels->wheel_blocks.push_back(platform_map[y][x][z].ground);
			}
			else if ((x == x_size - 1 && z == z_size - 2) ||
				(x == x_size - 1 && z == 1)) {
				platform_map[y][x][z].ground = OBJM->spawn_item(WHEEL_BLOCK_T, x, y, z);
				Wheels->wheel_blocks.push_back(platform_map[y][x][z].ground);
			}
			//generate the rest of the base
			else {

				//place the base frame
				platform_map[y][x][z].floor = OBJM->spawn_item(FLOOR_TEMP, x, y, z);
				if (x == 0 || x == x_size - 1 || z == 0 || z == z_size - 1) {
					platform_map[y][x][z].ground = OBJM->spawn_item(WALL_TEMP, x, y, z);
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

		float angle =0;

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
	std::cout << "wheels:      " << Wheels->wheels.size()<< std::endl;


	map_info->Wheels = Wheels;
}