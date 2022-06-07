#include "vehicle_manager.h"

#include <iostream>

vehicle_manager::vehicle_manager(motion_manger* mm){
	motion_updater = mm;
	station_ID = 0;
}

vehicle_manager::~vehicle_manager(){

}

void vehicle_manager::update(double deltTime) {

	//update the workstations
	for (int i = 0; i < workstations.size(); i++) {
		workstations[i]->update(deltTime);
		motion_updater->update_item(workstations[i]->lift);
		if (workstations[i]->mounted_vehicle != NULL) {
			motion_updater->update_item(workstations[i]->mounted_vehicle->body);
			motion_updater->update_item(workstations[i]->mounted_vehicle->BLW);
			motion_updater->update_item(workstations[i]->mounted_vehicle->BRW);
			motion_updater->update_item(workstations[i]->mounted_vehicle->FLW);
			motion_updater->update_item(workstations[i]->mounted_vehicle->FRW);
			motion_updater->update_item(workstations[i]->mounted_vehicle->headlights);

		}
	}

	//update the vehicles

}

int vehicle_manager::create_truck(const loc<int>& location) {
	int output_id = all_vehicles.size();
	grnd_vehicle* temp = new grnd_vehicle(location);
	all_vehicles.push_back(temp);

	return output_id;
}

bool vehicle_manager::drive_truck(int id, const loc<int>& location){
	bool output = false;

	return output;
}

bool vehicle_manager::set_truck_loc(int id, const loc<int>& location) {
	loc<double> temp(location.x, location.y, location.z);
	all_vehicles[id]->update(temp);
	return true;
}

int vehicle_manager::create_truck_workstation(const loc<int>& location) {
	car_workstation* temp = new car_workstation(station_ID);
	int output = station_ID;
	station_ID++;
	workstations.push_back(temp);
	return output;
}

car_workstation* vehicle_manager::get_station(int ID) {
	car_workstation* output = NULL;

	for (size_t i = 0; i < workstations.size(); i++)
	{
		if (workstations[i]->get_ID() == ID) {
			output = workstations[i];
			break;
		}
	}

	return output;
}

void vehicle_manager::spawn_car_on_station(int id) {

	for (size_t i = 0; i < workstations.size(); i++)
	{
		if (workstations[i]->get_ID() == id) {
			workstations[i]->location.x = workstations[i]->lift->x_m;
			workstations[i]->location.y = workstations[i]->lift->y_m;
			workstations[i]->location.z = workstations[i]->lift->z_m;
			workstations[i]->mounted_vehicle = all_vehicles[0];
			all_vehicles[0]->update(workstations[i]->location, false);
			break;
		}
	}

}