#pragma once

#include "../core/optimized_spawner.h"
#include "../core/motion_manager.h"

#include "crane/crane_manager.h"
#include "rail/rail_manager.h"

#include "furnace/furnace_manager.h"
#include "liquid/liquid_manager.h"

#include "../vehicles/ground/vehicle_manager.h"
#include "terrian/world_map.h"

#include "../vehicles/aircraft/aircraft_manager.h"
#include "decoration/decor_manager.h"

#include "../vehicles/missiles/missile_manager.h"
#include "../vehicles/missiles/missile_test_sim.h"

#include "doors/door_manager.h"
#include "belts/belt_manager.h"

#include "ground_items/grnd_obj_manager.h"

#include "../weapons/weapons_manager.h"
#include "../weapons/projectile_manager.h"

class environment
{
public:
	environment(optimized_spawner *os, motion_manger* mm);
	~environment();

	void set_map_data(map_data* map) { world_map = map; }

	void update(double time_change);

	//misc functions
	bool spawn_ground_item(item_type type, const loc<int>& location);
	bool spawn_floor_item(item_type type, const loc<int>& location);

	void replace_ground_item(item_type type, const loc<int>& location);
	void replace_floor_item(item_type type, const loc<int>& location);

	void delete_grnd_obj(const loc<int>& location);
	void delete_floor_obj(const loc<int>& location);

	void spawn_person(const loc<int>& location);

	//everything needed for the crane system
	int place_crane(const loc<int>& location, int height, int radius);
	void toggle_crane(int id);
	crane* get_crane(int id);
	void show_crane_area(int id);

	//everything needd to run the rail system
	bool place_rail(loc<int>& location, bool x_axis, railRoad::rail_type aType);
	bool can_place_rail(loc<int>& location);
	int place_cart(loc<int>& location);//returns the id of the cart
	int can_place_cart(loc<int>& location);
	void toggle_cart(int id, double velocity);
	void prin_rail_info();

	//everything to do with the furnace system
	int create_furnace(const std::vector<loc<int> > &spots);
	void add_mass_to_furnace(int id, double mass);
	void print_furnace_info(int id = -1);

	//everything to do with the belts
	int spawn_belt(loc<int> location, int output_dir);

	//everything to do with doors

	int spawn_bulk_head_door(loc<int> start, loc<int> end, bool y_axis, bool dir1);
	int get_door_at_loc(loc<int> location);
	void open_door(int ID);
	void close_door(int ID);

	//everything to do with the liquid system


	//everything to do with the ground vehicle system
	int place_truck(loc<int>& spawn);
	bool set_truck_dest(int id, loc<int>& spawn);

	int place_car_worksation(loc<int>& spawn);
	void spawn_car_on_station(int id);

	//everything to do with the aircraft
	int spawn_landing_pad(loc<int> location);
	int spawn_landing_strip(loc<int> location);
	int spawn_plane(int landing_pad);

	int spawn_drop_ship(loc<int> location);
	int spawn_thopter(loc<int> location);

	void send_craft_to_site(int plane, loc<int> location);
	void send_craft_to_land_site(int plane, int land_pad);
	void send_craft_patrol(int plane, loc<int> location);

	void draw_plane_route(int id);

	void run_air_sim();

	//everything to do with the missile system

	int spawn_missile(const loc<int>& spawn);
	int spawn_missile_lancher(const loc<int>& spawn);
	int spawn_missile_w_lancher(const loc<int>& spawn);

	bool fire_launcher(int launcher_id, const loc<int>& target);
	
	void start_missile_sim();

	// everything to do with the decoration

	void place_fanx3x3(const loc<int>& location);

	//everything to do with ground objects

	void place_ground_object(grnd_items::grnd_obj_type type, const loc<int>& location);
	void remove_ground_object(const loc<int>& location);
	void remove_ground_object(int ID);

	//everything to do with weapons
	int spawn_turret(loc<double> location);
	void delete_weapon(int ID);

private:

	//engine related objects
	optimized_spawner* spawner;
	motion_manger* updater;

	//managers
	crane_manager crane_mgr;
	railRoad::rail_manager rail_mgr;
	furnace_manager furnace_mgr;
	vehicle_manager vehicle_mgr;
	aircraft_manager aircraft_mgr;
	decor::decor_mgr decor_manager;
	missile_manager missile_mgr;
	missile_sim* mis_sim;
	belt_manager belt_mgr;
	door_manager door_mgr;
	grnd_items::grnd_obj_mgr grnd_objs_man;
	weapons::projectile_manager projectiles;
	weapons::weapons_manager weapons;

	//map related information
	map_data* world_map;
};

