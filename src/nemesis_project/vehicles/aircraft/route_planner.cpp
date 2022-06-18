#include "route_planner.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "../../utility/math/circle_math.h"
#include "../../utility/math/distance_math.h"


route_planner::route_planner() {
	run_sim = false;
}

route_planner::~route_planner() {

}

void route_planner::generate_route(aircraft* plane) {

}

void route_planner::active_sim(aircraft* plane, int points) {
	run_sim = true;
	generate_waypoints(plane, points);
}


void route_planner::generate_waypoints(aircraft* plane, int points) {

	loc<int> last_loc = plane->get_location();
	loc<int> new_loc = last_loc;

	if (plane->current_route == NULL) {
		plane->current_route = new route;
	}

	//rest the current route
	plane->current_route->waypoints.clear();
	plane->current_route->repeat = true;
	plane->current_route->done = false;
	plane->current_route->found_angle = false;
	plane->current_route->has_point_moved = false;
	plane->current_route->index = 0;


	for (int i = 0; i < points; i++) {

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
		/*waypoints[i]->x_m = new_loc.x * 2;
		waypoints[i]->y_m = new_loc.y * 2;
		waypoints[i]->z_m = new_loc.z * 2;*/

		//add to the route
		plane->current_route->waypoints.push_back(loc<double>(new_loc.x * 2, new_loc.y * 2, new_loc.z * 2));

		//update the model
		//updater->update_item(waypoints[i]);
		last_loc = new_loc;
	}

	//waypoint_reset = false;

}
