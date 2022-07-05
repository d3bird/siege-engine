#pragma	once
#include "../world/terrian_data.hpp"

namespace testing {

	class world_test {
	public:
		world_test();
		~world_test();

		std::pair<int, int> test_cords_world_map(map_data* testing);

	private:


	};

}