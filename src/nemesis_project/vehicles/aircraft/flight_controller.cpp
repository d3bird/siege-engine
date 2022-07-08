#include "flight_controller.h"

#include <iostream>

#include "../../utility/math/circle_math.h"
#include "../../utility/math/distance_math.h"

flight_controller::flight_controller(motion_manger* mm)
{
	updater = mm;

	way_x_size = 1;
	way_y_size = 1;
	way_z_size = 1;
	running_sim = false;
	sim_craft = NULL;
	index = 0;
}

flight_controller::~flight_controller()
{
}

void flight_controller::update(double time) {

	if (running_sim) {
		sim_update(time);
	}
	else {

		for (int i = 0; i < planes.size(); i++) {
			//direct_fly(time, planes[i]);
			turning_fly(time, planes[i]);
		}
	}
}

void flight_controller::direct_fly(double time, aircraft* plane) {

	route* current_route = plane->current_route;
	if (current_route != NULL) {
		double change = time * 20;
		loc<double> location(plane->obj->x_m,
			plane->obj->y_m, plane->obj->z_m);

		if (current_route->starting_waypoints.size() > 0) {
			loc<double> point = current_route->starting_waypoints[0];
			bool changed = false;

			if (location.x < point.x) {
				location.x += change;
				changed = true;
				if (location.x > point.x) {
					location.x = point.x;
				}
			}
			else if (location.x > point.x) {
				location.x -= change;
				changed = true;
				if (location.x < point.x) {
					location.x = point.x;
				}
			}

			if (location.y < point.y) {
				location.y += change;
				changed = true;
				if (location.y > point.y) {
					location.y = point.y;
				}
			}
			else if (location.y > point.y) {
				location.y -= change;
				changed = true;
				if (location.y < point.y) {
					location.y = point.y;
				}
			}

			if (location.z < point.z) {
				location.z += change;
				changed = true;
				if (location.z > point.z) {
					location.z = point.z;
				}
			}
			else if (location.z > point.z) {
				location.z -= change;
				changed = true;
				if (location.z < point.z) {
					location.z = point.z;
				}
			}

			if (!changed) {
				current_route->starting_waypoints.erase(current_route->starting_waypoints.begin());
			}

		}
		else {
			loc<double> point = current_route->waypoints[current_route->index];
			bool changed = false;

			if (location.x < point.x) {
				location.x += change;
				changed = true;
				if (location.x > point.x) {
					location.x = point.x;
				}
			}
			else if (location.x > point.x) {
				location.x -= change;
				changed = true;
				if (location.x < point.x) {
					location.x = point.x;
				}
			}

			if (location.y < point.y) {
				location.y += change;
				changed = true;
				if (location.y > point.y) {
					location.y = point.y;
				}
			}
			else if (location.y > point.y) {
				location.y -= change;
				changed = true;
				if (location.y < point.y) {
					location.y = point.y;
				}
			}

			if (location.z < point.z) {
				location.z += change;
				changed = true;
				if (location.z > point.z) {
					location.z = point.z;
				}
			}
			else if (location.z > point.z) {
				location.z -= change;
				changed = true;
				if (location.z < point.z) {
					location.z = point.z;
				}
			}

			if (!changed) {
				current_route->index += 1;
				if (current_route->index >= current_route->waypoints.size()) {
					current_route->index = 0;
				}
			}
		}


		plane->obj->x_m = location.x;
		plane->obj->y_m = location.y;
		plane->obj->z_m = location.z;
		updater->update_item(plane->obj);
	}

}

void flight_controller::turning_fly(double time, aircraft* plane) {
	route* current_route = plane->current_route;
	if (current_route != NULL) {

		double dist_change = time * 5;
		double angle_change = time * 20;

		loc<double> location(plane->obj->x_m,
			plane->obj->y_m, plane->obj->z_m);

		loc<double> point;

		bool used_start_point = false;
		if (current_route->starting_waypoints.size() > 0) {
			point = current_route->starting_waypoints[0];
			used_start_point = true;
		}
		else {
			point = current_route->get_current_waypoint();
		}

		bool changed = false;

		double current_angle = plane->obj->angles.get_y_angle();

		//if (!current_route->found_angle) {
		//	double needed_angle = calc_angle(location, point);
		//	bool found = false;

		//	if (needed_angle != current_angle) {
		//		//std::cout << "needed_angle " << needed_angle << std::endl;
		//		//std::cout << "current_angle " << current_angle << std::endl;

		//		//update the angle 
		//		if (current_angle > needed_angle) {
		//			current_angle -= angle_change;
		//			if (current_angle < needed_angle) {
		//				current_angle = needed_angle;
		//				found = true;
		//			}
		//			changed = true;
		//		}
		//		else if (current_angle < needed_angle) {
		//			current_angle += angle_change;
		//			if (current_angle > needed_angle) {
		//				current_angle = needed_angle;
		//				found = true;
		//			}
		//			changed = true;
		//		}
		//	}
		//	else {
		//		found = true;
		//	}

		//	if (found) {
		//		current_route->found_angle = true;
		//	}

		//}
		//if (current_route->found_angle) {
			 {

			std::cout << "moving the plane" << std::endl;
			//move plane
			changed = false;
			mathfunc::move_plane_forward(location, dist_change, current_angle, point);
		}
		plane->obj->x_m = location.x;
		plane->obj->y_m = location.y;
		plane->obj->z_m = location.z;
		plane->obj->angles.set_y_angle(current_angle);
		updater->update_item(plane->obj);

		if (!changed) {
			if (used_start_point) {
				current_route->starting_waypoints.erase(current_route->starting_waypoints.begin());
				current_route->found_angle = false;
			}
			else {
				current_route->increment_index();
				current_route->found_angle = false;
			}
		}
	}
}

bool flight_controller::is_point_in_wayarea(const double x, const double z, const loc<double>& point) {

	return ((x > point.x - way_x_size && x < point.x + way_x_size) &&
			(z > point.z - way_z_size && z < point.z + way_z_size));

}

void flight_controller::send_craft_patrol(aircraft* plane, loc<int> location) {
	if (plane == NULL) {
		std::cout << "not route for null plane" << std::endl;
		return;
	}


	route* new_route = new route;
	new_route->repeat = true;
	new_route->start_loc.x = plane->get_location().x;
	new_route->start_loc.y = plane->get_location().y;
	new_route->start_loc.z = plane->get_location().z;

	new_route->orbit_loc = location;

	plane->current_route = new_route;

	new_route->starting_waypoints.push_back(loc<double>(
		new_route->start_loc.x * 2, new_route->start_loc.y * 2, new_route->start_loc.z * 2));

	new_route->starting_waypoints.push_back(loc<double>(
		new_route->start_loc.x * 2, location.y * 2, new_route->start_loc.z * 2));

	create_orbit_patrol(plane);

	if (new_route->waypoints.size() != 0) {
		std::cout << "created orbit patrol with " << new_route->waypoints.size() << " points" << std::endl;
	}
	else {
		std::cout << "there where nmo waypopints generated" << std::endl;
	}

	planes.push_back(plane);
}

void flight_controller::create_orbit_patrol(aircraft* plane) {
	//plane->current_route->waypoints.push_back()
	loc<int> center = plane->current_route->orbit_loc;
	int raduis = 10;
	int y = plane->current_route->orbit_loc.y;
	for (int x = 0; x <40; x++) {
		for (int z = 0; z < 40; z++) {
			loc<int> new_dest(x, y, z);
			///*if (orbit_check(new_dest, center, raduis)) {
			//	loc<double> waypoint(new_dest.x * 2, new_dest.y * 2, new_dest.z * 2);
			//	plane->current_route->waypoints.push_back(waypoint);
			//}*/
		}
	}

}


 
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void flight_controller::start_sim(aircraft* craft, aircraft* craft2,  std::vector<rendering::item_info*> awaypoints) {
	//std::cout << "awaypoints" << awaypoints.size() << std::endl;
	//while (true);


	if (craft != NULL && awaypoints.size() > 0) {
		running_sim = true;
		sim_craft = craft;
		sim_craft2 = craft2;
		waypoints = awaypoints;
		sim_craft->set_location(loc<int>(10, 10, 10));
		updater->update_item(sim_craft->obj);

		int crafr_num = 1;
		if (sim_craft2 != NULL) {
			crafr_num++;
			sim_craft2->set_location(loc<int>(0, 10, 0));
		}

		srand(time(NULL));

		set_waypoints();

		std::cout << "starting flight simulation with: " << std::endl;
		std::cout << crafr_num<<" aircraft " << std::endl;
		std::cout << waypoints.size() << " waypoints" << std::endl;
	}
	else {
		std::cout << "sim failed to start" << std::endl;
		if (craft == NULL) {
			std::cout << "the airplane was null" << std::endl;
		}
		if (waypoints.empty()) {
			std::cout << "the waypoints where empty" << std::endl;
		}
	}

	//while (true);
}

void flight_controller::set_waypoints() {
	loc<int> last_loc = sim_craft->get_location();
	loc<int> new_loc = last_loc;

	if (sim_craft->current_route == NULL) {
		sim_craft->current_route = new route;
	}

	//rest the current route
	sim_craft->current_route->waypoints.clear();
	sim_craft->current_route->repeat = true;
	sim_craft->current_route->done = false;
	sim_craft->current_route->found_angle = false;
	sim_craft->current_route->has_point_moved = false;
	sim_craft->current_route->index = 0;


	for (int i = 0; i < waypoints.size(); i++) {

		//randomly move the waypoint
		//new_loc.x += rand() % 20 - 10;
		//new_loc.z += rand() % 20 - 10;
		if (i == -1) {
			new_loc.z += 10;
		}
		else {
			bool found_good_value = false;
			double new_x;
			double new_z;
			while (!found_good_value) {
				new_x = new_loc.x + rand() % 15;
				new_z = new_loc.z + rand() % 15;

				double dist = mathfunc::calc_distance(
					loc<double>(last_loc.x, last_loc.y, last_loc.z),
					loc<double>(new_x, last_loc.y, new_z));

				if (dist > 4) {
					found_good_value = true;
				}
			}
			new_loc.x = new_x;
			new_loc.z = new_z;
		}

		//update the waypooint
		waypoints[i]->x_m = new_loc.x * 2;
		waypoints[i]->y_m = new_loc.y * 2;
		waypoints[i]->z_m = new_loc.z * 2;

		//add to the route
		sim_craft->current_route->waypoints.push_back(loc<double>(waypoints[i]->x_m, waypoints[i]->y_m, waypoints[i]->z_m));

		//update the model
		updater->update_item(waypoints[i]);
		last_loc = new_loc;
	}

	waypoint_reset = false;
}

void flight_controller::sim_update(double time) {
	//	if (waypoint_reset) {
		//	set_waypoints();
		//}

	test_fly(time, sim_craft);
		if (sim_craft2 != NULL) {
			angle_update(time);
		}
}

void flight_controller::rotate_then_fly(double time, aircraft* plane) {
	if (plane->current_route == NULL) {
		set_waypoints();
	}
	loc<double> next_point = plane->current_route->get_current_waypoint();
	loc<double> location(plane->obj->x_m, plane->obj->y_m, plane->obj->z_m);


	bool readed_point = false;
	bool reached_angle = false;

	float needed_angle = mathfunc::calc_angle(location, next_point);
	float current_angle = plane->obj->angles.get_y_angle();

	if (needed_angle < 0) {
		needed_angle = 360 + needed_angle;
	}

	double distance = mathfunc::calc_distance(location, next_point);
	double angle_change_amount;

	if (current_angle < needed_angle) {
		angle_change_amount = needed_angle - current_angle;
	}
	else {
		angle_change_amount = current_angle - needed_angle;
	}

	double dist_change = time * (plane->get_move_speed(distance, angle_change_amount));  //* 5;
	double angle_change = time * (plane->get_angle_speed(distance, angle_change_amount));  //* 20;

	//needed_angle = 90;

	std::cout << "needed_angle " << needed_angle << std::endl;
	std::cout << "current_angle " << current_angle << std::endl;
	std::cout << "dest " << next_point.to_string() << std::endl;


	if (current_angle < needed_angle) {
		current_angle += angle_change;
		if (current_angle > needed_angle) {
			current_angle = needed_angle;
		}
	}
	else if (current_angle > needed_angle) {
		current_angle -= angle_change;
		if (current_angle < needed_angle) {
			current_angle = needed_angle;
		}
	}
	else {
		reached_angle = true;
	}


	double apx = 1;
	if (reached_angle || (current_angle <= needed_angle - apx &&
		current_angle >= needed_angle + apx)) {
		std::cout << "arrived at angle" << std::endl;

		if (mathfunc::move_plane_forward(location, dist_change, current_angle, next_point)) {
			readed_point = true;
		}
	}

	plane->obj->x_m = location.x;
	plane->obj->y_m = location.y;
	plane->obj->z_m = location.z;
	plane->obj->angles.set_y_angle(current_angle);
	updater->update_item(plane->obj);

	if (readed_point) {
		plane->current_route->increment_index();
	}
}

void flight_controller::test_fly(double time, aircraft* plane) {
	if (plane->current_route == NULL) {
		set_waypoints();
	}
	loc<double> next_point = plane->current_route->get_current_waypoint();
	loc<double> location(plane->obj->x_m, plane->obj->y_m, plane->obj->z_m);


	bool readed_point = false;
	bool reached_angle = false;

	float needed_angle = mathfunc::calc_angle(location, next_point);
	float current_angle_y = plane->obj->angles.get_y_angle();
	float current_angle_x = plane->obj->angles.get_x_angle();
	float current_angle_z = plane->obj->angles.get_z_angle();

	rendering::rotation rot_output = plane->obj->angles;


	if (needed_angle < 0) {
		needed_angle = 360 + needed_angle;
	}

	double distance = mathfunc::calc_distance(location, next_point);
	double angle_change_amount;

	if (current_angle_y < needed_angle) {
		angle_change_amount = needed_angle - current_angle_y;
	}
	else {
		angle_change_amount = current_angle_y - needed_angle;
	}

	double dist_change = time * (plane->get_move_speed(distance, angle_change_amount));  //* 5;
	double angle_change = time * (plane->get_angle_speed(distance, angle_change_amount));  //* 20;

	//needed_angle = 90;

	//std::cout << "needed_angle " << needed_angle << std::endl;
	//std::cout << "current_angle " << current_angle << std::endl;

	if (current_angle_y < needed_angle) {
		current_angle_y += angle_change;
		if (current_angle_y > needed_angle) {
			current_angle_y = needed_angle;
		}
	}
	else if (current_angle_y > needed_angle) {
		current_angle_y -= angle_change;
		if (current_angle_y < needed_angle) {
			current_angle_y = needed_angle;
		}
	}
	else {
		reached_angle = true;
	}

	/*if (mathfunc::double_equals(current_angle, needed_angle)) {
		reached_angle = true;
	}
	else {
		bool pos_change = pos_angle_change(current_angle, needed_angle);
		current_angle = get_new_angle(current_angle, needed_angle, angle_change, pos_change);
	}*/

	double apx = 1;
	if (reached_angle || (current_angle_y <= needed_angle - apx &&
		current_angle_y >= needed_angle + apx)) {
		//std::cout << "arrived at angle" << std::endl;

	}
	if (mathfunc::move_plane_forward(location, dist_change, current_angle_y, next_point)) {
		readed_point = true;
	}

	//std::cout << "dest " << next_point.to_string() << std::endl;
	//std::cout << "location " << location.to_string() << std::endl;

	current_angle_x += 50*time;
	//current_angle_z += 10*time;

	rot_output.set_x_angle(current_angle_x);
	rot_output.set_y_angle(current_angle_y);
	rot_output.set_z_angle(current_angle_z);

	plane->update_model_loc(location, rot_output);
	updater->update_item(plane->obj);

	if (readed_point) {
		plane->current_route->increment_index();

	}
}

void flight_controller::angle_update(double time) {

	double x_angle = sim_craft2->obj->angles.get_x_angle();
	double y_angle = sim_craft2->obj->angles.get_y_angle();
	double z_angle = sim_craft2->obj->angles.get_z_angle();

	x_angle += time * 20;
	y_angle += time * 20;

	rendering::rotation rot_output;

	rot_output.set_x_angle(x_angle);
	rot_output.set_y_angle(y_angle);
	rot_output.set_z_angle(z_angle);

	loc<double> location(sim_craft2->get_location().x * 2,
		sim_craft2->get_location().y * 2, sim_craft2->get_location().z * 2);

	sim_craft2->update_model_loc(location, rot_output);
	updater->update_item(sim_craft2->obj);
}

bool flight_controller::pos_angle_change(double current_angle, double needed_angle) {
	bool output = true;


	return output;
}

double flight_controller::get_new_angle(double current_angle, double needed_angle, double change, bool pos) {
	double output = current_angle;

	bool looped = false;

	if (pos) {
		output += change;
		if (output > 360) {
			output -= 360;
			looped = true;
		}
		

	}
	else {
		output -= change;
		if (output < 0) {
			output += 360;
			looped = true;
		}
	}

	return output;
}
