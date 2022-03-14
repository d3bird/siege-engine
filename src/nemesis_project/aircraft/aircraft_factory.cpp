#include "aircraft_factory.h"

#include <iostream>

aircraft_factory::aircraft_factory(int model){

	init(model);
}

aircraft_factory::~aircraft_factory(){

	for (int i = 0; i < planes.size(); i++) {
		delete_plane(planes[i]);
	}
	planes.clear();
}


plane_data* aircraft_factory::spawn_plane(int x, int y, int z, int plane_template) {
	plane_data* output = NULL;
	if (plane_template >= 0 && plane_template < planes.size()) {
		output = new plane_data;
		output->x_size = planes[plane_template]->x_size;
		output->y_size = planes[plane_template]->y_size;
		output->z_size = planes[plane_template]->z_size;

		output->x_loc = x;
		output->y_loc = y;
		output->z_loc = z;

		output->plane_type = planes[plane_template]->plane_type;
		output->flight_type = planes[plane_template]->flight_type;

		output->turn_radius = planes[plane_template]->turn_radius;

		output->fly_speed = planes[plane_template]->fly_speed;
		output->hover_speed = planes[plane_template]->hover_speed;

		output->model_index = planes[plane_template]->model_index;
		output->amount_models = planes[plane_template]->amount_models;

		output->scouting_radius = planes[plane_template]->scouting_radius;

		output->fuel_max = planes[plane_template]->fuel_max;
		output->fuel_left = planes[plane_template]->fuel_left;

		output->working = planes[plane_template]->working;

	}
	else {
		std::cout << "the plane_template does not exist" << std::endl;
	}

	return output;
}


int aircraft_factory::add_template_plane(plane_data* new_plane_type) {
	planes.push_back(new_plane_type);
	return planes.size() - 1;
}


void aircraft_factory::init(int model) {

	plane_data* example = new plane_data();

	example->x_size = 3;
	example->y_size = 2;
	example->z_size = 3;
	//the location of the plan
	example->x_loc = -1;
	example->y_loc = -1;
	example->z_loc = -1;

	example->plane_type = planes.size();
	example->flight_type = 2;

	example->turn_radius = 4;

	example->fly_speed = 5;
	example->hover_speed = 3;

	example->amount_models = 1;
	example->model_index =  new int[example->amount_models];
	example->model_index[0] = model;

	example->scouting_radius = 10;

	example->fuel_max = 10;
	example->fuel_left = 10;

	example->working = false;

	planes.push_back(example);
}
