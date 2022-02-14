#include "zone.h"

zone::zone(std::string n, zone_type t) {
	type = t;
	zone_name = n;
	x_size = -1;
	y_size = -1;
	z_size = -1;
	current_ID = 0;
}

zone::~zone() {
	for (int i = 0; i < all_spots.size(); i++) {
		delete all_spots[i];
	}
}

int zone::add_spot_to_zone(int x, int y, int z) {
	if ((x >= 0 && x < x_size) &&
		(y >= 0 && y < y_size) &&
		(z >= 0 && z < z_size)) {

		zone_cell* temp = new zone_cell;
		temp->x = x;
		temp->y = y;
		temp->z = z;
		temp->type = type;
		temp->obj_on_top = NULL;
		temp->ID = current_ID;
		current_ID++;
		update_conections(temp);

		all_spots.push_back(temp);
		temp->buffer_index = (unsigned int) all_spots.size() - 1;

		return temp->buffer_index;
	}
	else {
		std::cout << "spot was out of bounds" << std::endl;
		return -1;
	}
}

void zone::remove_spot_from_zone(int x, int y, int z) {

	if ((x >= 0 && x < x_size) &&
		(y >= 0 && y < y_size) &&
		(z >= 0 && z < z_size)) {

		int found = -1;
		zone_cell* cell = NULL;
		for (int i = 0; i < all_spots.size(); i++) {
			if (all_spots[i]->x == x &&
				all_spots[i]->y == y &&
				all_spots[i]->z == z) {
				found = i;
				cell = all_spots[i];
				break;
			}
		}

		if (found == -1 || cell == NULL) {
			std::cout << "could not find zone cell" << std::endl;
		}
		else {

			if (cell->east != NULL) {
				cell->east->west = NULL;
			}
			if (cell->west != NULL) {
				cell->west->east = NULL;
			}
			if (cell->north != NULL) {
				cell->north->south = NULL;
			}
			if (cell->south != NULL) {
				cell->south->north = NULL;
			}

			delete cell;
			all_spots[found] = NULL;

			all_spots[found] = all_spots[all_spots.size() - 1];
			all_spots.pop_back();

			bool done = false;
			for (int i = 0; i < unsued_spots.size(); i++) {
				if (unsued_spots[i] == found) {
					unsued_spots[i] = unsued_spots[unsued_spots.size() - 1];
					unsued_spots.pop_back();
					done = true;
				}
			}

			if (!done) {
				for (int i = 0; i < update_spots.size(); i++) {
					if (update_spots[i] == found) {
						update_spots[i] = update_spots[update_spots.size() - 1];
						update_spots.pop_back();
						done = true;
					}
				}
			}
		}

	}
	else {
		std::cout << "could not remove, not in bounds" << std::endl;

	}
}

void zone::update_conections(zone_cell* in) {

	if (in == NULL) {
		return;
	}
	std::cout << std::endl;
	int x = in->x;
	int y = in->y;
	int z = in->z;

	std::cout << "finding connections for (" << in->x << "," << in->y << "," << in->z << ")" << std::endl;

	if (inbounds(in)) {

	}
	else {
		std::cout << "out of bounds" << std::endl;
		return;
	}

	bool  west = false;
	bool east = false;
	bool south = false;
	bool north = false;

	if (in->west != NULL) { west = true; }
	if (in->east != NULL) { east = true; }
	if (in->south != NULL) { south = true; }
	if (in->north != NULL) { north = true; }

	if (x == 0) {
		north = true;
	}
	else if (x == x_size - 1) {
		south = true;
	}

	if (z == 0) {
		west = true;
	}
	else if (z == z_size - 1) {
		east = true;
	}

	int connections = 0;

	zone_cell* test;
	for (int i = 0; i < all_spots.size(); i++) {
		test = all_spots[i];
		if (inbounds(test) && y == test->y) {
			if (!west) {
				if (test->z == z - 1 && test->x == x) {
					std::cout << "west connection: (" << test->x << "," << test->y << "," << test->z << ")" << std::endl;
					west = true;
					in->west = test;
					test->east = in;
					connections++;
				}
			}
			if (!east) {
				if (test->z == z + 1 && test->x == x) {
					std::cout << "east connection: (" << test->x << "," << test->y << "," << test->z << ")" << std::endl;
					east = true;
					in->east = test;
					test->west = in;
					connections++;
				}
			}
			if (!south) {
				if (test->x == x + 1 && test->z == z) {
					std::cout << "south connection: (" << test->x << "," << test->y << "," << test->z << ")" << std::endl;
					south = true;
					in->south = test;
					test->north = in;
					connections++;
				}
			}
			if (!north) {
				if (test->x == x - 1 && test->z == z) {
					std::cout << "north connection: (" << test->x << "," << test->y << "," << test->z << ")" << std::endl;
					south = true;
					in->north = test;
					test->south = in;
					connections++;
				}
			}
		}
	}

	std::cout << "found " << connections << " connections" << std::endl;
	std::cout << std::endl;

}

void zone::debug_print() {
	zone_cell* temp;
	for (int i = 0; i < all_spots.size(); i++) {
		temp = all_spots[i];
		std::cout << "spot at(" << temp->x << ", " << temp->y << ", " << temp->z << ")" << std::endl;
		if (temp->east != NULL) {
			std::cout << "east: (" << temp->east->x << ", " << temp->east->y << ", " << temp->east->z << ")" << std::endl;
		}
		if (temp->west != NULL) {
			std::cout << "west: (" << temp->west->x << ", " << temp->west->y << ", " << temp->west->z << ")" << std::endl;
		}
		if (temp->north != NULL) {
			std::cout << "north: (" << temp->north->x << ", " << temp->north->y << ", " << temp->north->z << ")" << std::endl;
		}
		if (temp->south != NULL) {
			std::cout << "south: (" << temp->south->x << ", " << temp->south->y << ", " << temp->south->z << ")" << std::endl;
		}
		std::cout << std::endl;
	}

}
