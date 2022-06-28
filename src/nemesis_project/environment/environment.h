#pragma once

#include "../core/optimized_spawner.h"
#include "../utility/motion_manager.h"

#include "../world/crane/crane_manager.h"
#include "../world/rail/rail_manager.h"

#include "../world/furnace/furnace_manager.h"
#include "../world/liquid/liquid_manager.h"

#include "../vehicles/ground/vehicle_manager.h"
#include "../world/terrian/world_map.h"

#include "../vehicles/aircraft/aircraft_manager.h"
#include "../world/decoration/decor_manager.h"

#include "../vehicles/missiles/missile_manager.h"
#include "../vehicles/missiles/missile_test_sim.h"

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

	//everything needed for the crane system
	int place_crane(const loc<int>& location, int height, int radius);
	void toggle_crane(int id);
	crane* get_crane(int id);

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


	//map related information
	map_data* world_map;
};

