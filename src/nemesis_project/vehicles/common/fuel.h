#pragma once


class fuel
{
public:
	fuel(double Max_fuel, double Burn_rate);
	~fuel();

	void burn_fuel(double time);
	void add_fuel(double amount);
	bool has_fuel();

	double get_current_fuel();
	double get_max_fuel();
	double get_fuel_until_full();
	double get_burn_rate();
	double get_time_till_empty();

private:

	double current_fuel;
	double max_fuel;

	double burn_rate;

};
