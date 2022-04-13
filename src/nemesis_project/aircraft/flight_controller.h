#pragma once

#include "plane_route.hpp"
#include "aircraft_data.hpp"


class flight_controller
{
public:
	flight_controller();
	~flight_controller();

	void update();

	bool fly_plane(plane_data* plane, plane_route* route);

private:

	double get_angle(plane_data* plane, int x_loc, int y_loc, int z_loc);

	//testing the animations of the planes
	bool fly_sim;
	void update_fly_sim();
	void init_fly_sim();


	std::vector< plane_route*> routes;

};

