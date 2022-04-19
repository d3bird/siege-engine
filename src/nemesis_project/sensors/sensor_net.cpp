#include "sensor_net.h"

sensor_net::sensor_net(){

}

sensor_net::~sensor_net(){

}

void sensor_net::place_radar(int x, int y, int z) {
	radar* output = new radar;
	output->base_sats = create_sensor_base();


	radars.push_back(output);
}

void sensor_net::place_radio_tower(int x, int y, int z) {
	radio* output = new radio;
	output->base_sats = create_sensor_base();
	output->x = x;
	output->y = y;
	output->z = z;


	radios.push_back(output);
}

void sensor_net::place_cable(int x, int y, int z) {

}

sensor_base* sensor_net::create_sensor_base() {
	sensor_base* output = new sensor_base;

	output->running = false;
	output->jammed = false;
	output->noise_tollerece = 5;
	
	output->wired = false;
	output->wired = false;
	output->radio = false;
	output->connected = false;
	return output;
}

bool sensor_net::in_range_of_radar(int x, int y, int z) {

	return false;
}