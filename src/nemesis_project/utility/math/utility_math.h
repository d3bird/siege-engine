#pragma once

#include "../../common_obj/location.h"

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

	double calc_angle(loc<double> start, loc<double> dest);

	double calc_distance(loc<double> start, loc<double> dest);
	double calc_time_until_dest(loc<double> start, loc<double> dest, double rate);
	double calc_time_until_dest(double distance, double rate);

	void move_plane_forward(loc<double>& start, double change, double angle, const loc<double>& point);

	bool is_point_in_circle(loc<double> center, loc<double>& point, double radius);

	//helper functions
	bool double_equals(double a, double b, double epsilon = 0.001);

	//functions to check the math of these functions
	void check_math();

}