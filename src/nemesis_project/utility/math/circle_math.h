#pragma once

#include "utility_math.h"

/* THINGS TO NOTE:
* these functions work under the assumtion of a couple differnt rules that apply only to this application
*
* 1. the axis for the world map is set up as such, and the functions are made to work in this envirment
*
*                      ^ Z+
*                      |
*                      |
*                      |
*                      |
* <===================0,0
* X+
*
*/

namespace mathfunc {

	double calc_angle(loc<double> start, loc<double> dest, bool inverse_x_axis = true, bool inverse_z_axis = false);

	bool is_point_in_circle(loc<double> center, loc<double>& point, double radius);

}