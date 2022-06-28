#include "missile_test_sim.h"

#include <iostream>

missile_sim::missile_sim(missile_manager* man, optimized_spawner* spawn) :
	mis_manager(man), spawner(spawn)
{
	restock_lanchers = true;
	use_fuel = false;
	random_targets = false;
	sim_started = false;
}

missile_sim::~missile_sim()
{
}

void missile_sim::update(double time) {
	if (sim_started) {

	}
}

void missile_sim::start_sim() {
	if (sim_started) {
		std::cout << "missile sim has already been started" << std::endl;
		return;
	}
	std::cout << std::endl;
	std::cout << "starting missile sim" << std::endl;
	std::cout << "grabbing empty launchers" << std::endl;
	
	std::vector<int> lan_IDs = mis_manager->get_launcher_IDs();
	int lan_amount = mis_manager->get_lancher_num();

	if (lan_amount <= 0) {
		std::cout << "sim start failed, there was no launchers" << std::endl;
		return;
	}

	for (int i = 0; i < lan_amount; i++) {
		if (mis_manager->is_launcher_empty(lan_IDs[i])) {
			launchers.push_back(lan_IDs[i]);
			loc<int> lan_loc = mis_manager->get_lancher_loc(lan_IDs[i]);
			item_info* miss_obj = spawner->spawn_item(MISSILE3X1, lan_loc.x, lan_loc.y, lan_loc.z);
			missiles_obj.push_back(miss_obj);
			int mis_spawn = mis_manager->spawn_missile_in_launcher(lan_IDs[i], miss_obj);
			missiles.push_back(mis_spawn);
		}
	}

	std::cout << "there are " << launchers.size() << " empty launchers"<<std::endl;

	std::cout << std::endl;



	sim_started = true;

}
