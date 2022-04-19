#pragma once
#include "radio_manager.h"

/*radio_manager_global object
* This object connects all of the other radio managers together 
* also determins what towers are in range of other towers that constructed in differnt sectors
*/

class radio_manager_global
{
public:
	radio_manager_global();
	~radio_manager_global();

	std::vector<radio_station*>* get_radio_stations_inrange(int x, int y, int z);

private:
	std::vector<radio_station*>* stations_in_range;

	std::vector<radio_station*> moving_stations;
	std::vector<radio_station*> satatic_satations;
};

