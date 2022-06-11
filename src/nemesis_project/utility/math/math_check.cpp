#include "math_check.h"

#include <iostream>

void mathfunc::check_circle_math() {
	std::cout << std::endl;
	std::cout << "starting math testing code" << std::endl;
	int passsed = 0;
	int failed = 0;

	loc<double> start(0, 0, 0);
	loc<double> other_point(10, 0, 0);
	double output = 0;
	{
		std::cout << "the standered axis" << std::endl;
		other_point = loc<double>(10, 0, 0);
		output = calc_angle(start, other_point, false, false);
		if (double_equals(output, 0)) {
			passsed++;
		}
		else {
			std::cout << "failed 90 degree test gave: " << output << std::endl;
			failed++;
		}

		other_point = loc<double>(0, 0, 10);
		output = calc_angle(start, other_point, false, false);
		if (double_equals(output, 90.0)) {
			passsed++;
		}
		else {
			std::cout << "failed 90 degree test gave: " << output << std::endl;
			failed++;
		}

		other_point = loc<double>(-10, 0, 0);
		output = calc_angle(start, other_point, false, false);
		if (double_equals(output, 180.0)) {
			passsed++;
		}
		else {
			std::cout << "failed 180 degree test gave: " << output << std::endl;
			failed++;
		}

		other_point = loc<double>(0, 0, -10);
		output = calc_angle(start, other_point, false, false);
		if (double_equals(output, 270.0)) {
			passsed++;
		}
		else {
			std::cout << "failed 270 degree test gave: " << output << std::endl;
			failed++;
		}
	}
	{
		std::cout << "inverse x axis" << std::endl;
		other_point = loc<double>(-10, 0, 0);
		output = calc_angle(start, other_point, true, false);
		if (double_equals(output, 0)) {
			passsed++;
		}
		else {
			std::cout << "failed 90 degree test gave: " << output << std::endl;
			failed++;
		}

		other_point = loc<double>(0, 0, 10);
		output = calc_angle(start, other_point, true, false);
		if (double_equals(output, 90.0)) {
			passsed++;
		}
		else {
			std::cout << "failed 90 degree test gave: " << output << std::endl;
			failed++;
		}

		other_point = loc<double>(10, 0, 0);
		output = calc_angle(start, other_point, true, false);
		if (double_equals(output, 180.0)) {
			passsed++;
		}
		else {
			std::cout << "failed 180 degree test gave: " << output << std::endl;
			failed++;
		}

		other_point = loc<double>(0, 0, -10);
		output = calc_angle(start, other_point, true, false);
		if (double_equals(output, 270.0)) {
			passsed++;
		}
		else {
			std::cout << "failed 270 degree test gave: " << output << std::endl;
			failed++;
		}
	}
	{
		std::cout << "inverse z axis" << std::endl;
		other_point = loc<double>(10, 0, 0);
		output = calc_angle(start, other_point, false, true);
		if (double_equals(output, 0)) {
			passsed++;
		}
		else {
			std::cout << "failed 90 degree test gave: " << output << std::endl;
			failed++;
		}

		other_point = loc<double>(0, 0, -10);
		output = calc_angle(start, other_point, false, true);
		if (double_equals(output, 90.0)) {
			passsed++;
		}
		else {
			std::cout << "failed 90 degree test gave: " << output << std::endl;
			failed++;
		}

		other_point = loc<double>(-10, 0, 0);
		output = calc_angle(start, other_point, false, true);
		if (double_equals(output, 180.0)) {
			passsed++;
		}
		else {
			std::cout << "failed 180 degree test gave: " << output << std::endl;
			failed++;
		}

		other_point = loc<double>(0, 0, 10);
		output = calc_angle(start, other_point, false, true);
		if (double_equals(output, 270.0)) {
			passsed++;
		}
		else {
			std::cout << "failed 270 degree test gave: " << output << std::endl;
			failed++;
		}
	}
	{
		std::cout << "inverse x,z axis" << std::endl;
		other_point = loc<double>(-10, 0, 0);
		output = calc_angle(start, other_point, true, true);
		if (double_equals(output, 0)) {
			passsed++;
		}
		else {
			std::cout << "failed 90 degree test gave: " << output << std::endl;
			failed++;
		}

		other_point = loc<double>(0, 0, -10);
		output = calc_angle(start, other_point, true, true);
		if (double_equals(output, 90.0)) {
			passsed++;
		}
		else {
			std::cout << "failed 90 degree test gave: " << output << std::endl;
			failed++;
		}

		other_point = loc<double>(10, 0, 0);
		output = calc_angle(start, other_point, true, true);
		if (double_equals(output, 180.0)) {
			passsed++;
		}
		else {
			std::cout << "failed 180 degree test gave: " << output << std::endl;
			failed++;
		}

		other_point = loc<double>(0, 0, 10);
		output = calc_angle(start, other_point, true, true);
		if (double_equals(output, 270.0)) {
			passsed++;
		}
		else {
			std::cout << "failed 270 degree test gave: " << output << std::endl;
			failed++;
		}
	}

	std::cout << "passed " << passsed << std::endl;
	std::cout << "failed " << failed << std::endl;
	std::cout << "done with angle tests" << std::endl;
	while (true)
	{

	}
}

void mathfunc::check_distance_math() {

}

void mathfunc::check_all_math() {
	std::cout << "running tests on all math sections" << std::endl;
	check_circle_math();
	check_distance_math();

}