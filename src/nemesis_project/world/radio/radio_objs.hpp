#pragma once

#include <string>
#include <vector>

#include "../../common_obj/location.h"


//news increase productivity
//music reduces stress
//propiganda makes them more loyal to the city
//talkshow increases happyness
enum broadcast_type{NOTHING =0, NEWS, MUSIC, PROPIGANDA, TALK_SHOW};

struct radio_tower {

	int broadcasting_distance;
	loc<int> location;

	bool bradcasting;
	bool linked_to_station;

	//if not exposed to the sky then 
	bool obstructed;

};

struct radio_station;

struct radio_speakers {
	loc<int> location;
	radio_station* playing;

	bool wall_speaker;
	int broadcasting_distance;

};

struct console {
	loc<int> location;
	radio_station* controlling;
};

struct radio_station {

	std::string station_name;
	std::string frequency;

	broadcast_type schedule[24];

	bool live_broadcast;

	std::vector< radio_speakers*>speakers;
	std::vector< radio_tower*>towers;

	bool broadcasting;//if the station is playing
	bool towers_broadcasting;//if the towers are broadcasting

	bool broadcasting_recived_station;
	radio_station* recived_station;
};

