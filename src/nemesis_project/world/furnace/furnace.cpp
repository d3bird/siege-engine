#include "furnace.h"

#include <iostream>

furnace::furnace(int id){
	ID = id;
	current_mass = 0;
	max_mass =10;

	mass_burn_rate = 1;

	current_fuel = 0;
	max_fuel = 100;
	max_combined = max_fuel + max_mass;
	need_update = false;
}

furnace::~furnace()
{
}

void furnace::update(double time) {
	bool changed = false;

	if (current_mass > 0) {
	
	}

	if (!changed) {
		need_update = false;
	}

}

void furnace::add_mass(double mass) {
	current_mass += mass;
}

void furnace::print_info() {
	std::cout << "furnace: " << ID << std::endl;
	std::cout << "current_mass: " << current_mass << std::endl;
	std::cout << "max_mass: " << max_mass << std::endl;
	std::cout << "mass_burn_rate: " << mass_burn_rate << std::endl;
	std::cout << "current_fuel: " << current_fuel << std::endl;
	std::cout << "max_fuel: " << max_fuel << std::endl;
	std::cout << "max_combined: " << max_combined << std::endl;
}

bool furnace::operator==(const furnace& other) {

	return ID == other.ID;
}

bool furnace::operator==(int id) {
	return ID == id;
}