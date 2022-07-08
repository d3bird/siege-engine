#ifndef optimized_spawner_H
#define optimized_spawner_H

#include "API_data_ball.hpp"

#include "spawning_enums.hpp"
#include "../common_obj/location.h"

class optimized_spawner
{
public:
	optimized_spawner();
	~optimized_spawner();

	
	rendering::item_info* spawn_item(item_type type, int x, int y, int z, glm::mat4* given_mat = NULL);
	rendering::item_info* spawn_item(item_type type, const loc<int>& location, glm::mat4* given_mat = NULL);
	rendering::item_info* spawn_item(item_type type, int x, int y, int z, float angle);
	rendering::item_info* spawn_item(item_type type, const loc<int>& location, float angle );

	void update_item_matrix(rendering::update_pak* up, const glm::mat4 &mat);
	void update_item_matrix(rendering::update_pak* up);

	void delete_item_from_buffer(rendering::item_info* obj);
	
	void init(data_ball* objs);

private:

	data_ball* objs;

	rendering::object_manger* OBJM;
	timing* time;

	void import_models();

};

#endif // optimized_spawner_H