#pragma once 

#include "missile.h"
#include "missile _launcher.h"
#include "missile_flight.h"


#include "../../common_obj/location.h"
#include "../../core/motion_manager.h"

#include <vector>

class missile_manager
{
public:
	missile_manager(motion_manger* mm);
	~missile_manager();

	void update(double time);

	int spawn_missile(const loc<int>& location, rendering::item_info* model);
	int spawn_missile_in_launcher(int launcher_ID, rendering::item_info* model);
	int spawn_launcher(const loc<int>& location, rendering::item_info* model);

	bool move_missile_to_launcher(int amissile, int alauncher);

	bool fire_launcher(int alauncher, const loc<int>& target);

	rendering::item_info* explode_missile(int ID);

	//lancher information
	bool is_launcher_empty(int alauncher);
	int get_launcher_id(const loc<int>& location);

	int get_lancher_num();
	std::vector<int> get_launcher_IDs();
	loc<int> get_lancher_loc(int ID);
	bool lancher_exists(int ID);

private:

	missile* get_missile(int id);
	launcher* get_launcher(int id);

	motion_manger* updater;


	std::vector<missile*>missiles;
	std::vector<launcher*>launchers;

	int missile_id;
	int launcher_id;
};

