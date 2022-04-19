#pragma once
#include "radio_factory.h"

/*radio_manager object
* this object holds/mods the radio information for a city or a chunk of land
* the globle manager will connect all of the smaller mangers otogether if one of the towers
* comes into range of your radio equipment.
* this class will determin if the speakers are in range of towers 
*/

class radio_manager
{
public:
	radio_manager(optimized_spawner* objm, bool move);
	~radio_manager();

	//creates the base objects at the target locations and returns them so they can be hooked 
	//to other objects
	radio_tower* create_broadcast_tower(int x, int y, int z);
	radio_speakers* create_speaker_tower(int x, int y, int z, int height);
	console* create_broadcast_console(int x, int y, int z, float angle);
	radio_speakers* create_wall_speaker(int x, int y, int z, float angle);
	radio_station* create_radio_station(broadcast_type type);

	//conection functions
	void hook_station_to_speaker(radio_station* station, radio_speakers* speaker);
	void hook_station_to_console(radio_station* station, radio_speakers* speaker);
	void hook_station_to_tower(radio_station* station, radio_speakers *speaker);

	//setters

	void set_broadcasting_recived_station(radio_station* host_station, radio_station* forwared_station);

	//getters
	radio_tower* get_broadcast_tower(int x, int y, int z);
	radio_speakers* get_speaker_tower(int x, int y, int z, int height);
	console* get_broadcast_console(int x, int y, int z);
	radio_speakers* get_wall_speaker(int x, int y, int z);
	radio_station* get_radio_station(broadcast_type type);

private:

	radio_factory* factory;

	bool moving;

	radio_station* current_station;

	//these should be replace with a map to increase preformance in the future
	std::vector<radio_speakers*> speakers;
	std::vector<console*> consoles;
	std::vector<radio_tower*> towers;
	std::vector<radio_station*> stations;
};
