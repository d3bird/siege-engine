#pragma once

#include "vehicle.h"
#include <vector>
#include "../utility/motion_manager.h"

class vehicle_manager
{
public:
	vehicle_manager(motion_manger* mm);
	~vehicle_manager();

	void update(double deltTime);

	int create_truck(const loc<int>& location);
	bool drive_truck(int id, const loc<int>& location);
	bool set_truck_loc(int id, const loc<int>& location);

	std::vector< grnd_vehicle* > all_vehicles;

private:
	motion_manger* motion_updater;
};

