#pragma once

#include "ships/aircraft_base.h"
#include "ships/drop_ship.h"

#include "air_route.hpp"
#include "../../core/motion_manager.h"

#include <vector>

/*flight_controller
* this manager managers the flying animation and how the plane moves between the given points
*/
class flight_controller
{
public:
	flight_controller(motion_manger* mm);
	~flight_controller();

	void update(double time);

	void send_craft_patrol(aircraft* plane, loc<int> location);

	void start_sim(aircraft* craft, aircraft* craft2, std::vector<rendering::item_info*> awaypoints);
private:
	std::vector<aircraft*> planes;
	motion_manger* updater;

	void create_orbit_patrol(aircraft* plane);
	bool orbit_check(const loc<int>& aDest, const loc<int>& aCenter, int radius);

	bool pos_angle_change(double current_angle, double needed_angle);
	double get_new_angle(double current_angle, double needed_angle, double change, bool pos);

	//flight functions
	void direct_fly(double time, aircraft* plane);
	void turning_fly(double time, aircraft* plane);
	void rotate_then_fly(double time, aircraft* plane);;

	//this just test the core flying of the ship to predefined waypoints
	void test_fly(double time, aircraft* plane);

	bool is_point_in_wayarea(const double x, const double z, const loc<double>& point);

	// the size of the waypoint the aircraft must hit
	double way_x_size;
	double way_y_size;
	double way_z_size;

	//stuff needed for the simulation

	void sim_update(double time);
	void angle_update(double time);

	void set_waypoints();
	bool waypoint_reset = true;
	bool running_sim;
	aircraft* sim_craft;
	aircraft* sim_craft2;
	std::vector<rendering::item_info*> waypoints;
	int index;
};

