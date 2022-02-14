#include "world.h"


world::world(map_data* map) {
	//OBJM = objm;
	world_map = NULL;
	map_info = NULL;

	if (map != NULL) {
		map_info = map;
		world_map = map->map;
		x_size = map->x_size;
		y_size = map->y_size;
		z_size = map->z_size;
		inited = true;
	}

}
world::world(map_data*** map) {
	//OBJM = objm;
	world_map = NULL;
	map_info = NULL;

	if (map != NULL) {
		large_map = map;
		large_map = map;
		
		inited = true;
	}

}

world::~world() {
}

void world::update() {
	//Thermal->update();
}

void world::spawn_object(int x, int y, int z, int object, float angle) {

}
void world::place_heat_source(int x, int y, int z) {

}

void world::find_pathing(int x_s, int y_s, int z_s, int x_e, int y_e, int z_e) {

}

void world::init(int x_siz, int y_siz, int z_siz, optimized_spawner* OBJM) {
	std::cout << "initing world" << std::endl;

	x_size = x_siz;
	y_size= y_siz;
	z_size= z_siz;

	world_gen = new world_generator(OBJM);
	map_info = world_gen->create_blank_world_cell(x_siz, y_siz, z_siz);
	//world_gen->generate_room_test(map_info);
	//world_gen->generate_hill_world(map_info);
	world_gen->generate_valley_world(map_info);
	//world_gen->generate_test_world(map_info);

	/*if (OBJM == NULL) {
		std::cout << "OBJM was NULL" << std::endl;
		return;
	}*/
	//Thermal->set_time(time);
	//Thermal->init(x_size, y_size, z_size, OBJM);
	//Thermal->place_heat_source(0, 0, 0, 80, 5);


	//zone* temp_zone = new farm_zone("farm zone");
	//temp_zone->set_bounds(x_size, y_size, z_size);
	//
	//temp_zone->add_spot_to_zone(1, 0, 0);
	//temp_zone->add_spot_to_zone(0, 0, 1);
	//temp_zone->add_spot_to_zone(0, 0, 0);
	//temp_zone->add_spot_to_zone(1, 0, 1);
	//temp_zone->add_spot_to_zone(-1, 0, 1);
	//temp_zone->add_spot_to_zone(1, 0, -1);
	//temp_zone->add_spot_to_zone(1, -1, 1);

	////temp_zone->remove_spot_from_zone(0, 0, 0);
	////temp_zone->get_interaction_spot(PICKUP);
	////temp_zone->update();
	//temp_zone->debug_print();

	//temp_zone->remove_spot_from_zone(0, 0, 0);

	//temp_zone->debug_print();


	//body* b = new body;
	//head* h = new head;
	//arm* left = new arm;
	//arm* right = new arm;
	//leg* left_l = new leg;
	//leg* right_l = new leg;
	//build_a_person(b, h, left, right, left_l, right_l);

	//print_body_strcuture(b);
}

bool world::is_valid_loc(int x, int y, int z) {
	return (x >= 0 && x < x_size&&
		z >= 0 && z < z_size&&
		y >= 0 && y < y_size);
}

void world::update_obj_angle(item_info* obj, optimized_spawner* OBJM, float angle) {

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