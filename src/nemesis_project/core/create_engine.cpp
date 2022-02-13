#include "create_engine.h"

create_engine::create_engine(){
	current = NULL;
}

create_engine::~create_engine(){

}

optimized_spawner* create_engine::init(engine_api* API) {
	if (API != NULL) {
		data_ball* data =new  data_ball(API);

		if (data != NULL) {
			std::cout << "data ball was created" << std::endl;
		}

		data->engine_full_inited();

		current = new optimized_spawner();
		current->init(data);
		return current;
	}
	return NULL;
}