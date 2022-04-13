#pragma once

template<class T>
struct loc_i {
	T x =-1;
	T  y =-1;
	T  z=-1;

	loc_i() {
		x = -1;
		y = -1;
		z = -1;
	}

	loc_i(T  x0, T  y0, T  z0) {
		x = x0;
		y = y0;
		z = z0;
	}

	bool operator==(const loc_i& other) {
		return (x == other.x &&
			y == other.y &&
			z == other.z);
	}

};