#pragma once

#include "air_route.hpp"
#include "ships/aircraft_base.h"

class route_planner {
public:
	route_planner();
	~route_planner();

	void generate_route(aircraft* plane);

	void active_sim(aircraft* plane, int points);

private:
	
	void generate_waypoints(aircraft* plane, int points);
	
	bool run_sim;

};