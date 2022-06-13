#include "circle_math.h"

#ifndef PI
#define PI 3.14159265
#endif // !PI

double mathfunc::calc_angle(loc<double> start, loc<double> dest,
	bool inverse_x_axis, bool inverse_z_axis) {

	double x;
	double z;

	if (inverse_x_axis) {
		x = start.x -dest.x ;
	}
	else {
		x = dest.x - start.x;
	}

	if (inverse_z_axis) {
		z = start.z - dest.z;
	}
	else {
		z = dest.z - start.z;
	}

	double return_angle = atan2(z, x) * 180 / PI;
	return return_angle;
}

bool mathfunc::is_point_in_circle(loc<double> center, loc<double>& point, double radius) {
	return false;
}