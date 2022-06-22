#pragma once 

#include "missile.h"
#include "missile _launcher.h"
#include "missile_flight.h"

#include "../../common_obj/location.h"
#include "../../utility/motion_manager.h"

#include <vector>

class missile_manager
{
public:
	missile_manager(motion_manger* mm);
	~missile_manager();

	void update(double time);

	int spawn_missile(const loc<int>& location, item_info* model);
	int spawn_launcher(const loc<int>& location, item_info* model);

	bool move_missile_to_launcher(int amissile, int alauncher);

	bool fire_launcher(int alauncher, const loc<int>& target);
	bool is_launcher_empty(int alauncher);
	int get_launcher_id(const loc<int>& location);

private:

	missile* get_missile(int id);
	launcher* get_launcher(int id);

	motion_manger* updater;

	std::vector<missile*>missiles;
	std::vector<launcher*>launchers;

	int missile_id;
	int launcher_id;
};

