#include "track_data.h"

#include <iostream>

track::track(int id) :
	ID(id), tracking_model(NULL)
{
}

track::~track(){

}

void track::update(double time_change) {
	if (tracking_model != NULL) {
		angles = tracking_model->angles;

		//calculate the velocity 
		x_velocity = ((location.x - tracking_model->x_m) / time_change);
		y_velocity = ((location.y - tracking_model->y_m) / time_change);
		z_velocity = ((location.z - tracking_model->z_m) / time_change);

		//updated the location
		location.x = tracking_model->x_m;
		location.y = tracking_model->y_m;
		location.z = tracking_model->z_m;
	}
}

void track::set_tracking_model(rendering::item_info* model) {
	if (model == NULL) {
		if (tracking_model != NULL || currently_tracking) {
			track_stale = true;
		}

	}
	else {
		track_stale = false;
		currently_tracking = true;
		tracking_model = model;
		angles = model->angles;
		location.x = tracking_model->x_m;
		location.y = tracking_model->y_m;
		location.z = tracking_model->z_m;
		x_velocity = 0;
		y_velocity = 0;
		z_velocity = 0;
	}
}

void track::update_location(const loc<double>& alocation) {
	location = alocation;
}

void track::update_location(double x, double y, double z) {
	location.x = x;
	location.y = y;
	location.z = z;
}


void track::update_rotation(const rendering::rotation& new_angle) {
	angles = new_angle;
}

bool track::is_tracking() {
	return currently_tracking;
}

bool track::has_track_gone_stale() {
	return track_stale;
}

void track::print_info() {
	std::cout << "track ID: " << ID << std::endl;
	std::cout << (currently_tracking ? ("Currently Track") : ("Not Tracking")) << std::endl;
	std::cout << (track_stale ? ("track is stale") : ("track is not stale")) << std::endl;
	std::cout << "location: " << location.to_string() << std::endl;
	std::cout << "angles: " << angles.to_string() << std::endl;
	std::cout << "x_velocity " << x_velocity << std::endl;
	std::cout << "y_velocity " << y_velocity << std::endl;
	std::cout << "z_velocity " << z_velocity << std::endl;
}

loc<double> track::get_location() {
	return location;
}

rendering::rotation track::get_rotation() {
	return angles;
}

double track::get_x_velocity() {
	return z_velocity;
}

double track::get_y_velocity() {
	return y_velocity;
}

double track::get_z_velocity() {
	return z_velocity;
}

int track::get_ID() {
	return ID;
}

bool track::operator==(const track& other) {
	return ID == other.ID;
}

bool track::operator==(int other_id) {
	return ID == other_id;
}