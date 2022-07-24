#include "distance_math.h"

#include <iostream>
#include <cmath>


namespace mathfunc {

#ifndef PI2
#define PI2 3.14159265
#endif // !PI

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

	//only moves in the x/z direction
	bool mathfunc::move_plane_forward(loc<double>& start, double change, double angle, const loc<double>& point) {

		bool passed_through = false;

		double	z = sin(angle * PI2 / 180) * change;
		double	y = start.y;
		double	x = cos(angle * PI2 / 180) * change;

		start.x -= x;//that a axises is inveted in this app
		start.z += z;

		double distance = calc_distance(start, point);

		if (distance - .5 <= change + .5) {
			passed_through = true;
		}

		return passed_through;
	}

	double calc_velocity(double delta_time, loc<double> start, loc<double> dest) {
		calc_velocity(delta_time, calc_distance(start, dest));
	}

	double calc_velocity(double delta_time, double distance) {
		return distance / delta_time;
	}

	double calc_acceleration(double start_vel, double end_vel, double delta_time) {
		return ((end_vel - start_vel) / delta_time);
	}

	void calc_new_pos(loc<double>& pos, loc<double>& acc, loc<double>& vel, double delta_time) {
		pos.x = (pos.x + (vel.x * delta_time) + (0.5 * acc.x * delta_time * delta_time));
		pos.y = (pos.y + (vel.y * delta_time) + (0.5 * acc.y * delta_time * delta_time));
		pos.z = (pos.z + (vel.z * delta_time) + (0.5 * acc.z * delta_time * delta_time));

		vel.x = (vel.x + (acc.x * delta_time));
		vel.y = (vel.y + (acc.y * delta_time));
		vel.z = (vel.z + (acc.z * delta_time));
	}

	void calc_new_pos(loc<double>& pos, const loc<double>& vel, double delta_time) {
		pos.x = (pos.x + (vel.x * delta_time));
		pos.y = (pos.y + (vel.y * delta_time));
		pos.z = (pos.z + (vel.z * delta_time));
	}

}