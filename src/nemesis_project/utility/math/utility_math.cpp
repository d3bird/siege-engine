#include "utility_math.h"

#include <iostream>
#include <cmath>

#ifndef PI
#define PI 3.14159265
#endif // !PI

double mathfunc::calc_angle(loc<double> start, loc<double> dest) {
	double return_angle = atan2(dest.z - start.z, dest.x - start.x) * 180 / PI;
	return return_angle;
}

double mathfunc::calc_distance(loc<double> start, loc<double> dest) {
	double x = (start.x - dest.x) * (start.x - dest.x);
	double y = (start.y - dest.y) * (start.y - dest.y);
	double z = (start.z - dest.z) * (start.z - dest.z);
	return std::sqrt(x + y + z);
}

double mathfunc::calc_time_until_dest(loc<double> start, loc<double> dest, double rate) {
	return mathfunc::calc_time_until_dest(calc_distance(start, dest), rate);
}

double mathfunc::calc_time_until_dest(double distance, double rate) {
	return distance / rate;
}

void mathfunc::move_plane_forward(loc<double>& start, double change, double angle, const loc<double>& point) {

}

bool mathfunc::is_point_in_circle(loc<double> center, loc<double>& point, double radius) {
	return false;
}

//helper functions
bool mathfunc::double_equals(double a, double b, double epsilon)
{
	return std::abs(a - b) < epsilon;
}

void mathfunc::check_math() {
	std::cout << std::endl;
	std::cout << "starting math testing code" << std::endl;
	int passsed = 0;
	int failed = 0;

	loc<double> start(0, 0, 0);
	loc<double> other_point(10, 0, 0);
	double output = 0;

	output = calc_angle(start, other_point);
	if (double_equals(output, 0)) {
		passsed++;
	}
	else {
		std::cout << "failed 90 degree test gave: " << output << std::endl;
		failed++;
	}

	other_point = loc<double>(0, 0, 10);
	output = calc_angle(start, other_point);
	if (double_equals(output, 90.0)) {
		passsed++;
	}
	else {
		std::cout << "failed 90 degree test gave: " << output << std::endl;
		failed++;
	}

	other_point = loc<double>(-10, 0, 0);
	output = calc_angle(start, other_point);
	if (double_equals(output, 180.0)) {
		passsed++;
	}
	else {
		std::cout << "failed 180 degree test gave: " << output << std::endl;
		failed++;
	}

	other_point = loc<double>(0, 0, -10);
	output = calc_angle(start, other_point);
	if (double_equals(output, 270.0)) {
		passsed++;
	}
	else {
		std::cout << "failed 270 degree test gave: " << output << std::endl;
		failed++;
	}

	std::cout << "passed " << passsed << std::endl;
	std::cout << "failed " << failed << std::endl;
	std::cout << "done with angle tests" << std::endl;
	while (true)
	{

	}
}
