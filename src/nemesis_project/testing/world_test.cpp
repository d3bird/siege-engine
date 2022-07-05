#include "world_test.h"


testing::world_test::world_test() {

}

testing::world_test::~world_test() {

}

std::pair<int, int> testing::world_test::test_cords_world_map(map_data* testing) {

	std::pair<int, int> output;

	output.first = 0;//tests run 
	output.second = 0;//tests passed

	int world_x = testing->x_size;
	int world_y = testing->y_size;
	int world_z = testing->z_size;

	int chunk_x = testing->world_map[0][0][0].x_size;
	int chunk_y = testing->world_map[0][0][0].y_size;
	int chunk_z = testing->world_map[0][0][0].z_size;

	int test_run = 0;
	int test_passed = 0;

	//every chunk in the world
	for (int wx = 0; wx < world_x; wx++) {
		for (int wy = 0; wy < world_y; wy++) {
			for (int wz = 0; wz < world_z; wz++) {
				//every cell in the chunk
				for (int x = 0; x < chunk_x; x++) {
					for (int y = 0; y < chunk_y; y++) {
						for (int z = 0; z < chunk_z; z++) {

							int x_cord = x + (wx * chunk_x);
							int y_cord = y + (wy * chunk_y);
							int z_cord = z + (wz * chunk_z);
							std::pair < loc<int>, loc<int> >output = testing->get_map_local_cords(
								loc<int>(x_cord, y_cord, z_cord));

							test_run++;

							if (output.first.x != -1 && output.first.y != -1 && output.first.z != -1 &&
								output.second.x != -1 && output.second.y != -1 && output.second.z != -1) {
								test_passed++;
							}

						}
					}
				}

			}
		}
	}

	output.first = test_run;
	output.second = test_passed;

	return output;

}