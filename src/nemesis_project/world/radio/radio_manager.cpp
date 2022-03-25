#include "radio_manager.h"


radio_manager::radio_manager(optimized_spawner* objm, bool move){
	factory = new radio_factory(objm);
	moving = move;
}

radio_manager::~radio_manager(){
	delete factory;
}


radio_tower* radio_manager::create_broadcast_tower(int x, int y, int z) {
	radio_tower* output = factory->place_radio_tower(x, y, z);
	towers.push_back(output);
	return output;
}

radio_speakers* radio_manager::create_speaker_tower(int x, int y, int z, int height) {
	radio_speakers* output = factory->place_speaker_tower(x, y, z, height);
	speakers.push_back(output);
	return output;

}

console* radio_manager::create_broadcast_console(int x, int y, int z) {
	console* output = factory->place_console(x, y, z);
	consoles.push_back(output);
	return output;

}

radio_speakers* radio_manager::create_wall_speaker(int x, int y, int z, float angle) {
	radio_speakers* output = factory->place_speaker(x, y, z, angle);
	speakers.push_back(output);

	return output;
}

radio_station* radio_manager::create_radio_station(broadcast_type type) {
	radio_station* output = factory->create_radio_station(type);
	stations.push_back(output);
	return output;
}

void radio_manager::hook_station_to_speaker(radio_station* station, radio_speakers* speaker) {

}

void radio_manager::hook_station_to_console(radio_station* station, radio_speakers* speaker) {

}

void radio_manager::hook_station_to_tower(radio_station* station, radio_speakers* speaker) {

}

void radio_manager::set_broadcasting_recived_station(radio_station* host_station, radio_station* forwared_station) {

}

radio_tower* radio_manager::get_broadcast_tower(int x, int y, int z) {
	return NULL;
}

radio_speakers* radio_manager::get_speaker_tower(int x, int y, int z, int height) {
	return NULL;
}

console* radio_manager::get_broadcast_console(int x, int y, int z) {
	return NULL;
}

radio_speakers* radio_manager::get_wall_speaker(int x, int y, int z) {
	return NULL;
}

radio_station* radio_manager::get_radio_station(broadcast_type type) {
	return NULL;
}
