#pragma once

#include "furnace.h"
#include <vector>

class furnace_manager
{
public:
	furnace_manager();
	~furnace_manager();

	void update(double time);

	int create_furnace(const std::vector<loc<int> >& spots);
	void add_mass_to_furnace(int id, double mass);
	void print_furnace_info(int id = -1);

private:
	std::vector<furnace> furnaces;
	int ID_MAX;
};
