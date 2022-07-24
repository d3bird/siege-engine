#pragma once

#include "../../common_obj/location.h"
#include "utility_math.h"

namespace mathfunc {

	double calc_distance(loc<double> start, loc<double> dest);
	double calc_time_until_dest(loc<double> start, loc<double> dest, double rate);
	double calc_time_until_dest(double distance, double rate);

	bool move_plane_forward(loc<double>& start, double change, double angle, const loc<double>& point);

	inline double calc_velocity(double delta_time, loc<double> start, loc<double> dest);
	double calc_velocity(double delta_time, double distance);
	double calc_acceleration(double start_vel, double end_vel, double delta_time);

	void calc_new_pos(loc<double>& pos, const loc<double>& vel, double delta_time);
	void calc_new_pos(loc<double>& pos, loc<double>& acc, loc<double>& vel, double delta_time);

}