#pragma once

struct plane_data {
	//the bounding box of the plane
	int x_size;
	int y_size;
	int z_size;
	//the location of the plan
	double x_loc;
	double y_loc;
	double z_loc;

	int plane_type;
	int flight_type;//0 for fly, 1 for hover

	int turn_radius;

	double fly_speed;
	double hover_speed;

	int* model_index = 0;
	int amount_models;

	int scouting_radius;

	double fuel_max;
	double fuel_left;

	bool working;

};

static void delete_plane(plane_data* del) {
	if (del != 0) {
		if (del->model_index != 0) {
			delete del->model_index;
		}
		delete del;
	}

}