#include "fuel.h"

fuel::fuel(double Max_fuel, double Burn_rate):
	current_fuel(0), max_fuel(Max_fuel), burn_rate(Burn_rate)
{
}

fuel::~fuel()
{
}

void fuel::burn_fuel(double time) {
	current_fuel -= (time * burn_rate);
}

bool fuel::has_fuel() {
	return current_fuel > 0;
}

double fuel::get_current_fuel() {
	return current_fuel;
}

double fuel::get_max_fuel() {
	return max_fuel;
}

double fuel::get_fuel_until_full() {
	return max_fuel - current_fuel;
}

double fuel::get_burn_rate() {
	return burn_rate;
}

double fuel::get_time_till_empty() {
	return (current_fuel / burn_rate);
}

void fuel::add_fuel(double amount) {
	current_fuel += amount;
	if (current_fuel > max_fuel) {
		current_fuel = max_fuel;
	}
}
