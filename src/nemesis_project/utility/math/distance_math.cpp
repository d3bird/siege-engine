#include "distance_math.h"

#include <iostream>
#include <cmath>

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