#include "../door_manager.h"


class door_manager_gui {
public:
	door_manager_gui(door_data::door_manager* doors);
	~door_manager_gui();

	void display();

private:
	door_data::door_manager* door_man;

};