#include "missile_test_sim.h"

#include <iostream>
#include <random>

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
	clean_targets();
}

void missile_sim::update(double time) {
	if (sim_started) {

	}
}

void missile_sim::set_bounds(loc<int> atopleft, loc<int> abotright) {
	topleft = atopleft;
	botright = abotright;
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
			rendering::item_info* miss_obj = spawner->spawn_item(MISSILE3X1, lan_loc.x, lan_loc.y, lan_loc.z);
			missiles_obj.push_back(miss_obj);
			int mis_spawn = mis_manager->spawn_missile_in_launcher(lan_IDs[i], miss_obj);
			missiles.push_back(mis_spawn);
		}
	}

	std::cout << "there are " << launchers.size() << " empty launchers"<<std::endl;

	std::cout << std::endl;

	//generate_targets();

	sim_started = true;

}


void missile_sim::generate_targets() {
	clean_targets();

	std::default_random_engine generator;
	
	std::uniform_int_distribution<int> x_distribution(botright.x, topleft.x);
	std::uniform_int_distribution<int> y_distribution(botright.y, topleft.y);
	std::uniform_int_distribution<int> z_distribution(botright.z, topleft.z);
	for (int i = 0; i < target_generate; i++) {

		int x = x_distribution(generator);
		int y = y_distribution(generator);
		int z = z_distribution(generator);

		target* temp = new target;
		temp->map_loc = loc<int>(x, y, z);
		temp->real_space = loc<double>(x*2, y*2, z*2);
		temp->target_model = spawner->spawn_item(MOON_T, x, y, z);
		targets.push_back(temp); 
	}

}

void missile_sim::clean_targets() {
	for (int i = 0; i < targets.size(); i++) {
		//clean up the waypoints
		if (targets[i]->target_model != NULL) {
			spawner->delete_item_from_buffer(targets[i]->target_model);
		}
	}
	//clear the inforamtion
	targets.clear();
}

void missile_sim::pop_front() {
	if (!targets.empty()) {
		if (targets[0]->target_model != NULL) {
			spawner->delete_item_from_buffer(targets[0]->target_model);
		}
		targets.erase(targets.begin());
	}
}