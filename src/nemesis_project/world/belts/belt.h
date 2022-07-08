#pragma once

#include "../../common_obj/location.h"
#include <rendering/rendering_object_data.hpp>

class belt
{
public:
	belt(int id, loc<int> aLocation, int aOutDirection);
	~belt();

	bool can_connect(bool connect);
	
	bool operator ==(const belt& other);
	bool operator ==(int aID);

	int get_num_connections();

	loc<int> get_location(){ return location; }
	int get_ID() { return ID; }

	bool open_connections();

	void set_obj(rendering::item_info* new_obj);
	rendering::item_info* get_obj() { return object; }

private:

	int ID;
	loc<int> location;
	rendering::item_info* object;

	//0 x+
	//1 z+
	//2 x-
	//3 z-
	int outDirection;

	belt* north_connection;
	belt* south_connection;
	belt* east_connection;
	belt* west_connection;
};
