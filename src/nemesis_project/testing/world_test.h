#pragma	once

#include "../world/world.h"
#include "../world/terrian_data.hpp"

namespace testing {

	class world_test {
	public:
		world_test();
		~world_test();

		std::pair<int, int> test_cords_world_map(world* testing);

	private:


	};

}