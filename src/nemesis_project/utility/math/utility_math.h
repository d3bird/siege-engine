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

	//helper functions
	bool double_equals(double a, double b, double epsilon = 0.001);


}