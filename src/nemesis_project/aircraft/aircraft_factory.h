#pragma once

#include "aircraft_data.hpp"

#include <vector>

class aircraft_factory
{
public:
	aircraft_factory(int model);
	~aircraft_factory();

	plane_data* spawn_plane(int x, int y, int z, int plane_template);

	//this adds planes from outside the inted template planes 
	//returns the spawn int
	int add_template_plane(plane_data* new_plane_type);

private:

	//creates the templates that the factory pulls from
	void init(int model);

	std::vector<plane_data*>planes;

};

