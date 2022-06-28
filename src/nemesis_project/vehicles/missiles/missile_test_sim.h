#include "missile.h"
#include "missile _launcher.h"
#include "missile_flight.h"
#include "missile_manager.h"
#include <vector>

#include "../../core/optimized_spawner.h"

class missile_sim
{
public:
	missile_sim(missile_manager* man, optimized_spawner *spawn);
	~missile_sim();

	void update(double time);
	void start_sim();

private:

	bool sim_started;

	missile_manager* mis_manager;
	optimized_spawner* spawner;
	bool restock_lanchers;
	bool use_fuel;
	bool random_targets;

	std::vector<item_info*>missiles_obj;
	std::vector<int>missiles;
	std::vector<int >launchers;

};
