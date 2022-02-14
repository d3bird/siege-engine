#ifndef optimized_spawner_H
#define optimized_spawner_H

#include "API_data_ball.hpp"

#include "spawning_enums.hpp"

class optimized_spawner
{
public:
	optimized_spawner();
	~optimized_spawner();

	
	item_info* spawn_item(item_type type, int x, int y, int z, glm::mat4* given_mat = NULL);
	item_info* spawn_item(item_type type, int x, int y, int z, float angle );

	void update_item_matrix(update_pak* up);

	void delete_item_from_buffer(item_info* obj);
	
	void init(data_ball* objs);

private:

	data_ball* objs;

	object_manger* OBJM;
	timing* time;

	void import_models();

};

#endif // optimized_spawner_H