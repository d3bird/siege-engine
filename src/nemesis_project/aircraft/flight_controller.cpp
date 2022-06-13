#include "flight_controller.h"

#include <iostream>

#include "../utility/math/circle_math.h"
#include "../utility/math/distance_math.h"

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

		double current_angle = plane->obj->angle;

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
		plane->obj->angle = current_angle;
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

void flight_controller::start_sim(aircraft* craft, std::vector<item_info*> awaypoints) {
	//std::cout << "awaypoints" << awaypoints.size() << std::endl;
	//while (true);


	if (craft != NULL && awaypoints.size()>0) {
		running_sim = true;
sim_craft = craft;
waypoints = awaypoints;
sim_craft->set_location(loc<int>(10, 10, 10));
updater->update_item(sim_craft->obj);

srand(time(NULL));

set_waypoints();

std::cout << "starting flight simulation with: " << std::endl;
std::cout << "1 aircraft " << std::endl;
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


	for (int i = 0; i < waypoints.size(); i++) {

		//randomly move the waypoint
		//new_loc.x += rand() % 20 - 10;
		//new_loc.z += rand() % 20 - 10;
		if (i == -1) {
			new_loc.z += 10;
		}
		else {
			new_loc.x += rand() % 10;
			new_loc.z += rand() % 10;
		}

		//update the waypooint
		waypoints[i]->x_m = new_loc.x * 2;
		waypoints[i]->y_m = new_loc.y * 2;
		waypoints[i]->z_m = new_loc.z * 2;
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
}

void flight_controller::test_fly(double time, aircraft* plane) {
	loc<double> next_point(waypoints[index]->x_m, waypoints[index]->y_m, waypoints[index]->z_m);
	loc<double> location(plane->obj->x_m, plane->obj->y_m, plane->obj->z_m);

	double dist_change = time * 5;
	double angle_change = time * 20;

	float needed_angle = mathfunc::calc_angle(location, next_point);
	float current_angle = plane->obj->angle;

	//needed_angle = 90;

	std::cout << "needed_angle " << needed_angle << std::endl;
	std::cout << "current_angle " << current_angle << std::endl;
	std::cout << "dest " << next_point.to_string() << std::endl;

	bool readed_point = false;
	bool reached_angle = false;
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
	plane->obj->angle = current_angle;
	updater->update_item(plane->obj);

	if (readed_point) {
		index++;
		if (index >= waypoints.size()) {
			//running_sim = false;
			index = 0;// go back to the start
		}
	}
}