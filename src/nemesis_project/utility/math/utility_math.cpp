#include "utility_math.h"


//helper functions
bool mathfunc::double_equals(double a, double b, double epsilon)
{
	return std::abs(a - b) < epsilon;
}