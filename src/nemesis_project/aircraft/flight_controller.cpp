#include "flight_controller.h"

#include <iostream>

flight_controller::flight_controller()
{
}

flight_controller::~flight_controller()
{
}

//upate the plane on route
void flight_controller::update() {
	for (int i = 0; i < routes.size(); i++) {

	}
}

//check to makesure that the plane can fly this route and  return a bool that it started
//fill out the points for the route and add it to the update queue
bool flight_controller::fly_plane(plane_data *plane, plane_route* route) {
	bool added_to_updates = false;
	if (plane != NULL && route != NULL) {
		std::cout << "creating a route for given plane" << std::endl;
		route->plane = plane;

	}
	else {
		std::cout << "failed to create a route for NULL aircraft || route" << std::endl;
	}

	return added_to_updates;
}