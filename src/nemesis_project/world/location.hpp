#pragma once

struct loc {
	int x =-1;
	int y =-1;
	int z=-1;

	loc() {
		x = -1;
		y = -1;
		z = -1;
	}

	loc(int x0, int y0, int z0) {
		x = x0;
		y = y0;
		z = z0;
	}

	bool operator==(const loc& other) {
		return (x == other.x &&
			y == other.y &&
			z == other.z);
	}

};