#include "generation_pipeline.h"

generation_pipeline::generation_pipeline(optimized_spawner* objm) {
	OBJM = objm;
	def_settings = NULL;
	given_settings = NULL;
	using_def = false;

	world_gen = new world_generator(OBJM);
	city_gen = new city_generator(OBJM);
}

generation_pipeline::~generation_pipeline() {
	delete_settings(def_settings);
	delete_settings(given_settings);

	delete world_gen;
	delete city_gen;
}

void generation_pipeline::set_to_def_settings() {
	if (def_settings == NULL) {
		def_settings = new gen_setttings;

		def_settings->spawn_items = false;
		def_settings->create_thermal_system = false;
		def_settings->create_motion_system = false;
		def_settings->check_for_errors = false;

		def_settings->city_settings = new city_gen_settings;
		def_settings->world_settings = new world_gen_settings;

		def_settings->city_settings->x_size = 16;
		def_settings->city_settings->y_size = 10;
		def_settings->city_settings->z_size = 16;

		def_settings->world_settings->x_size = 20;
		def_settings->world_settings->y_size = 10;
		def_settings->world_settings->z_size = 20;

		def_settings->world_settings->ground_level = 4;

		def_settings->world_settings->cells_wide = 5;
		def_settings->world_settings->cells_long = 7;

		def_settings->world_settings->use_mix_of_biomes = true;
		def_settings->world_settings->specific_biome = PLANE;

		def_settings->world_settings->biome_size_range = false;
		def_settings->world_settings->biome_size =2;
		def_settings->world_settings->biome_min_size = 1;
		def_settings->world_settings->biome_max_size = 5;

		def_settings->world_settings->encluded_bioms.push_back(FOREST);
		def_settings->world_settings->encluded_bioms.push_back(PLANE);
		def_settings->world_settings->encluded_bioms.push_back(VALLEY);
		def_settings->world_settings->encluded_bioms.push_back(HILLS);
	}

	given_settings = def_settings;
	using_def = true;
}

void generation_pipeline::set_gen_settings(gen_setttings* input) {
		given_settings = input;
		using_def = false;
}

void generation_pipeline::set_city_gen_settings(city_gen_settings* input) {
	if (given_settings == NULL) {
		return;
	}
	given_settings->city_settings = input;
}

void generation_pipeline::set_world_gen_settings(world_gen_settings* input) {
	if (given_settings == NULL) {
		return;
	}
	given_settings->world_settings = input;
}

mobil_platform* generation_pipeline::create_mobil_city() {

	if (given_settings == NULL) {
		set_to_def_settings();
	}

	int x_size_city = given_settings->city_settings->x_size;
	int y_size_city = given_settings->city_settings->y_size;
	int z_size_city = given_settings->city_settings->z_size;

	local_map_data* temp = city_gen->create_platform(x_size_city, y_size_city, z_size_city);

	temp = city_gen->turn_platform_into_factory(temp);

	mobil_platform* mobil_city = NULL;// new mobil_platform(temp);
	//mobil_city->init(x_size_city, y_size_city, z_size_city, OBJM);
	return mobil_city;
}

world* generation_pipeline::create_world() {

	if (given_settings == NULL) {
		set_to_def_settings();
	}

	//generates the map and the objects
	local_map_data*** map_info= world_gen->create_full_world_map(given_settings->world_settings);

	//creates the details in the map
	create_motion_systems(map_info);
	create_thermal_systems(map_info);

	//makesure that the objects will not overlap
	offset_world_map(map_info);

	//check to make sure that the map genorated correctly
	check(map_info);

	int rendering_que = create_optimised_rendering_que(map_info[0][0]);

	world* World = NULL;// new world(map_info);

	//if (World->generated_correctly()) {
	//	std::cout << "this world was generated correctly" << std::endl;
	//}
	//else {
	//	std::cout << "this world was not generated correctly" << std::endl;
	//}

	//World->init(x_size_world, y_size_world, z_size_world, OBJM);
	return World;
}

world* generation_pipeline::create_world_single_cell() {

	if (given_settings == NULL) {
		set_to_def_settings();
	}

	int x_size_world = given_settings->world_settings->x_size;
	int y_size_world = given_settings->world_settings->y_size;
	int z_size_world = given_settings->world_settings->z_size;

	local_map_data* map_info;

	map_info = world_gen->create_blank_world_cell(x_size_world, y_size_world, z_size_world);
	//world_gen->generate_room_test(map_info);
	//world_gen->generate_hill_world(map_info);
	world_gen->generate_valley_world(map_info);
	//world_gen->generate_test_world(map_info);

	world* World = NULL;// new world(map_info);

	/*if (World->generated_correctly()) {
		std::cout << "this world was generated correctly" << std::endl;
	}
	else {
		std::cout << "this world was not generated correctly" << std::endl;
	}*/

	//World->init(x_size_world, y_size_world, z_size_world, OBJM);
	return World;
}


int generation_pipeline::create_optimised_rendering_que(local_map_data* input, bool set_primary) {
	//int output =-1;

	//if (input == NULL) {
	//	return -2;
	//}

	//std::cout << "creating the optimised que from input" << std::endl;
	////rending_cell* objm_input = new rending_cell;


	//input->map;
	//int ground_objs = 0;
	//int floor_objs = 0;
	//for (int y = 0; y < input->y_size; y++) {
	//	for (int x = 0; x < input->x_size; x++) {
	//		for (int z = 0; z < input->z_size; z++) {
	//			if (input->map[y][x][z].ground != NULL) {
	//				redner_que->objects_to_add.push_back(input->map[y][x][z].ground);
	//				ground_objs++;
	//			}
	//			if (input->map[y][x][z].floor != NULL) {
	//				redner_que->objects_to_add.push_back(input->map[y][x][z].floor);
	//				floor_objs++;
	//			}
	//		}
	//	}
	//}
	//std::cout << "there are " << ground_objs << " ground_objs"<< std::endl;
	//std::cout << "there are " << floor_objs << " floor_objs"<< std::endl;
	//std::cout << "there are " << redner_que->objects_to_add.size() << " items to add to the que" << std::endl;;
	////rendering_que* rendering_que_obj = OBJM->create_que_from_cell(objm_input);


	//OPTM->create_rendering_que(redner_que);


	//if (set_primary) {
	//	if (output >= 0) {

	//	}
	//	else {
	//		std::cout << "can not set as primary rendering que, recived " << output <<
	//			" from object manager" << std::endl;
	//	}
	//}

	//std::cout << "done creating the optimised que from input" << std::endl;

	return -1;
}

//helper functions

//moves the objects to their respective spots
void generation_pipeline::offset_world_map(local_map_data*** input) {
	if (input == NULL) {
		return;
	}
	int cells_wide = given_settings->world_settings->cells_wide;
	int cells_long = given_settings->world_settings->cells_long;

	for (int i = 0; i < cells_wide; i++) {
		for (int q = 0; q < cells_long; q++) {
			input[i][q]->x_off_set = (input[i][q]->x_size * i);
			input[i][q]->z_off_set = (input[i][q]->z_size * q);
			/*if (q % 2 == 0 || i % 2 ==0) {
				input[i][q]->y_off_set = 4;
			}*/
			offset_world_map(input[i][q]);
		}
	}

}

void generation_pipeline::offset_world_map(local_map_data* input){//moves the objects to their respective spots
	if (input == NULL) {
		return;
	}

	map_cell*** grid = input->map;

	//offset values
	int new_x = input->x_off_set;
	int new_y = input->y_off_set ;
	int new_z = input->z_off_set ;

	for (int y = 0; y < input->y_size; y++) {
		for (int x = 0; x < input->x_size; x++) {
			for (int z = 0; z < input->z_size; z++) {
				
				if (grid[y][x][z].floor != NULL) {
					grid[y][x][z].floor->x = (x + new_x);
					grid[y][x][z].floor->y = (y + new_y);
					grid[y][x][z].floor->z = (z + new_z);

					grid[y][x][z].floor->x_m = (float)(x + new_x) * 2.0f;
					grid[y][x][z].floor->y_m = (float)(y + new_y) * 2.0f;
					grid[y][x][z].floor->z_m = (float)(z + new_z) * 2.0f;

					update_obj_angle(grid[y][x][z].floor, grid[y][x][z].floor->angle);

				}
				if (grid[y][x][z].ground != NULL) {
					grid[y][x][z].ground->x = (x + new_x);
					grid[y][x][z].ground->y = (y + new_y);
					grid[y][x][z].ground->z = (z + new_z);

					grid[y][x][z].ground->x_m = (float)(x + new_x) * 2.0f;
					grid[y][x][z].ground->y_m = (float)(y + new_y) * 2.0f;
					grid[y][x][z].ground->z_m = (float)(z + new_z) * 2.0f;

					update_obj_angle(grid[y][x][z].ground, grid[y][x][z].ground->angle);

				}

				grid[y][x][z].x = (x + new_x);
				grid[y][x][z].y = (y + new_y);
				grid[y][x][z].z = (z + new_z);

			}
		}
	}

}

void generation_pipeline::create_motion_systems(local_map_data*** input){// creates the motion systems for the maps
	if (input == NULL) {
		return;
	}
}

void  generation_pipeline::create_motion_systems(local_map_data* input){
	if (input == NULL) {
		return;
	}
}

void  generation_pipeline::create_thermal_systems(local_map_data*** input){// creates the thernak systems for the maps
	if (input == NULL) {
		return;
	}
}

void  generation_pipeline::create_thermal_systems(local_map_data* input) {
	if (input == NULL) {
		return;
	}
}

bool  generation_pipeline::check(local_map_data*** input) {// checks the generated maps for errors
	return true;
}

bool  generation_pipeline::check(local_map_data* input) {
	return true;
}


void generation_pipeline::update_obj_angle(item_info* obj, float angle) {

	update_pak update_pac;

	update_pac.x = obj->x_m;
	update_pac.y = obj->y_m;
	update_pac.z = obj->z_m;

	update_pac.x_scale = 1;
	update_pac.y_scale = 1;
	update_pac.z_scale = 1;

	update_pac.angle = angle;

	update_pac.buffer_loc = obj->buffer_loc;
	update_pac.item_id = obj->item_id;

	OBJM->update_item_matrix(&update_pac);

}