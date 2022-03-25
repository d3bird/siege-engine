#pragma once

#include "radio_objs.hpp"
#include "../../core/optimized_spawner.h"

class radio_factory
{
public:
	radio_factory(optimized_spawner* objm);
	~radio_factory();

	radio_speakers* place_speaker(int x, int y, int z, float angle, radio_station* station = NULL);
	console* place_console(int x, int y, int z, radio_station* station = NULL);
	radio_tower* place_radio_tower(int x, int y, int z);

	radio_speakers* place_speaker_tower(int x, int y, int z,int height, radio_station* station = NULL);

	radio_station* create_radio_station(broadcast_type type);

	
private:
	optimized_spawner* OBJM;

	//def values for the objects
	int braodcast_distance_speaker;
	int braodcast_distance_tower;

	bool spawn_objs;

};
