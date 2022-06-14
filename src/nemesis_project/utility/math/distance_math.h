#pragma once

#include "../../common_obj/location.h"
#include "utility_math.h"

namespace mathfunc {

	double calc_distance(loc<double> start, loc<double> dest);
	double calc_time_until_dest(loc<double> start, loc<double> dest, double rate);
	double calc_time_until_dest(double distance, double rate);

	bool move_plane_forward(loc<double>& start, double change, double angle, const loc<double>& point);

}