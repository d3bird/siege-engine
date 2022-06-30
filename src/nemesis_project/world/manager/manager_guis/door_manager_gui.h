#include "../door_manager_old.h"


class door_manager_gui {
public:
	door_manager_gui(door_data::door_manager_old* doors);
	~door_manager_gui();

	void display();

private:
	door_data::door_manager_old* door_man;

};