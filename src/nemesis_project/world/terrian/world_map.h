#pragma once 

#include "local_map.h"

class map_data
{
public:
	map_data();
	~map_data();

	bool has_been_inited();

	int x_size;
	int y_size;
	int z_size;

	local_map_data*** world_map;

	std::pair < loc<int>, loc<int> > get_map_local_cords(const loc<int>& cords);

	bool can_place_ground_obj(const loc<int>& cords, bool requires_floor);
	bool can_place_ground_obj(const loc<int>& chunk_cords,const loc<int>& local_cords, bool requires_floor);

	bool attach_obj(const loc<int>& cords, item_info* obj, bool floor, bool ground);

	//returns the object that replaced
	item_info* replace_obj(const loc<int>& cords, item_info* obj, bool floor, bool ground);

private:
	
	//check for validation
	bool is_valid_chunck(const loc<int>& cords);
	bool is_valid_locaL_cords(const loc<int>& chunk_cords, const loc<int>& local_cords);

	//get map cell information
	bool is_cords_ground_NULL(const loc<int>& chunk_cords, const loc<int>& local_cords);
	bool is_cords_floor_NULL(const loc<int>& chunk_cords, const loc<int>& local_cords);

	//helper functions
	inline void set_floor_obj(const loc<int>& chunk_cords, const loc<int>& local_cords, item_info* obj);
	inline void set_ground_obj(const loc<int>& chunk_cords, const loc<int>& local_cords, item_info* obj);
};

