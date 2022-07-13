
#include "random_gen.h"

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <random>

namespace mathfunc {


	int get_random_num(int lower_bound, int upper_bound) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> distribution(lower_bound, upper_bound);
		return int(distribution(mt));

	}

	std::vector<double> get_numbers_between_bounds(int amount, int lower_bound, int upper_bound) {
		double temp = 0;
		std::vector<double> output;

		if (lower_bound == upper_bound) {
			while (output.size() < amount)
			{
				output.push_back(lower_bound);
			}
		}
		else {
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<double> distribution(lower_bound, upper_bound);

			while (output.size() < amount)
			{
				temp = distribution(mt);
				output.push_back(temp);
			}
		}
		
		return output;
	}

}