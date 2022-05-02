#include "radio_factory.h"

radio_factory::radio_factory(optimized_spawner* objm){
	OBJM = objm;

	//these numbers will have to be changed latter
	braodcast_distance_tower = 50;
	braodcast_distance_speaker = 10;
	if (OBJM != NULL) {
		spawn_objs = true;
	}
	else {
		spawn_objs = false;
	}
}

radio_factory::~radio_factory(){

}

radio_speakers* radio_factory::place_speaker(int x, int y, int z, float angle, radio_station* station) {
	radio_speakers* output = new radio_speakers;
	output->location = loc<int>(x, y, z);
	output->playing = station;
	output->broadcasting_distance = braodcast_distance_speaker;
	output->wall_speaker = true;
	if (spawn_objs) {
		OBJM->spawn_item(WALL_SPEAKER, x, y, z, angle);
	}
	return output;
}

console* radio_factory::place_console(int x, int y, int z, radio_station* station) {
	console* output = new console;
	output->location = loc<int>(x, y, z);
	output->controlling = station;
	if (spawn_objs) {
		OBJM->spawn_item(RADIO_CONSOLE, x, y, z);
	}
	return output;
}
radio_tower* radio_factory::place_radio_tower(int x, int y, int z) {
	radio_tower* output = new radio_tower;
	output->location = loc<int>(x, y, z);
	output->bradcasting = false;
	output->linked_to_station = false;
	output->obstructed = false;
	output->broadcasting_distance = braodcast_distance_tower;
	if (spawn_objs) {
		OBJM->spawn_item(BROADCAST_TOWER, x, y, z);
	}
	return output;
}

radio_speakers* radio_factory::place_speaker_tower(int x, int y, int z, int height, radio_station* station) {

	if (height <= 0) {
		return NULL;
	}

	radio_speakers* output = new radio_speakers;
	output->location = loc<int>(x, y, z);
	output->playing = station;

	if (height > 6) {
		height = 6;
	}

	output->broadcasting_distance = height*2;
	output->wall_speaker = false;

	if (spawn_objs) {
		for (int i = 0; i < height; i++) {
			OBJM->spawn_item(WALL_SPEAKER, x, y+i, z);
		}
		OBJM->spawn_item(SPEAKER_TOP, x, y + height, z);
	}
	return output;
}

radio_station* radio_factory::create_radio_station(broadcast_type type) {
	radio_station* output = new radio_station;

	for (int i = 0; i < 24; i++) {
		output->schedule[i] = type;
	}

	output->broadcasting = false;
	output->towers_broadcasting = false;
	output->live_broadcast = false;
	output->broadcasting_recived_station = false;
	output->recived_station = NULL;

	return output;
}