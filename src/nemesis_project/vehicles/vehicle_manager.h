#pragma once

#include "vehicle.h"
#include <vector>
#include "../utility/motion_manager.h"
#include "car_workstation.h"

class vehicle_manager
{
public:
	vehicle_manager(motion_manger* mm);
	~vehicle_manager();

	void update(double deltTime);

	int create_truck(const loc<int>& location);
	bool drive_truck(int id, const loc<int>& location);
	bool set_truck_loc(int id, const loc<int>& location);

	int create_truck_workstation(const loc<int>& location);
	car_workstation* get_station(int ID);
	void spawn_car_on_station(int id);

	std::vector< grnd_vehicle* > all_vehicles;

private:
	motion_manger* motion_updater;

	std::vector< car_workstation* > workstations;
	int station_ID;
};

