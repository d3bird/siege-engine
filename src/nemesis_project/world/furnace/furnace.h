#pragma once

#include "../../common_obj/location.h"

#include "../liquid/liquid_storage.h"

class furnace
{
public:
	furnace(int id);
	~furnace();

	void add_mass(double mass);

	bool need_update;
	void update(double time);

	void print_info();

	int get_ID() { return ID; }

	bool operator==(const furnace& other);
	bool operator==(int id);

private:

	int ID;

	double current_mass;
	double max_mass;

	double mass_burn_rate;

	double current_fuel;
	double max_fuel;

	double max_combined;

};

