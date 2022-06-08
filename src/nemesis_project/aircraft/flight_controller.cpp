#include "flight_controller.h"

#include <iostream>

flight_controller::flight_controller(motion_manger* mm)
{
	updater = mm;
}

flight_controller::~flight_controller()
{
}

void flight_controller::update(double time) {

	for (int i = 0; i < planes.size(); i++) {
		route* current_route = planes[i]->current_route;
		if (current_route != NULL) {
			double change = time * 20;
			loc<double> location(planes[i]->obj->x_m, 
				planes[i]->obj->y_m, planes[i]->obj->z_m);

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


			planes[i]->obj->x_m = location.x;
			planes[i]->obj->y_m = location.y;
			planes[i]->obj->z_m = location.z;
			updater->update_item(planes[i]->obj);
		}
	}

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
			if (orbit_check(new_dest, center, raduis)) {
				loc<double> waypoint(new_dest.x * 2, new_dest.y * 2, new_dest.z * 2);
				plane->current_route->waypoints.push_back(waypoint);
			}
		}
	}

}


bool flight_controller::orbit_check(const loc<int>& aDest, const loc<int>& aCenter, int radius){
	//(x - center_x)² + (y - center_y)² < radius²

	double x_com = aDest.x - aCenter.x;
	double z_com = aDest.z - aCenter.z;

	return ((x_com * x_com) + (z_com * z_com) == (radius * radius));
	/*return (base_loc != aDest)&&((aDest.x - base_loc.x) * (aDest.x - base_loc.x) +
		(aDest.z - base_loc.z) * (aDest.z - base_loc.z) <= radius * radius);*/
}