#include "furnace_manager.h"

#include <iostream>

furnace_manager::furnace_manager(){
	ID_MAX = 0;
}

furnace_manager::~furnace_manager(){
	furnaces.clear();
}

void furnace_manager::update(double time) {

	for (int i = 0; i < furnaces.size(); i++) {
		furnaces[i].update(time);
	}

}


int furnace_manager::create_furnace(const std::vector<loc<int> >& spots) {
	int output = ID_MAX;
	ID_MAX++;
	furnace temp(output);

	return output;
}

void  furnace_manager::add_mass_to_furnace(int id, double mass) {
	for (size_t i = 0; i < furnaces.size(); i++) {
		if (furnaces[i] == id) {
			furnaces[i].add_mass(mass);
		}
	}
}

void  furnace_manager::print_furnace_info(int id) {

	if (id < 0) {
		for (size_t i = 0; i < furnaces.size(); i++){
			furnaces[i].print_info();
		}
	}
	else {
		for (size_t i = 0; i < furnaces.size(); i++){
			if (furnaces[i] == id) {
				furnaces[i].print_info();
			}
		}
	}
}