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

	void set_bounds(loc<int> atopleft, loc<int> abotright);

	void start_sim();

private:

	void generate_targets();
	void clean_targets();
	void pop_front();
	bool sim_started;

	missile_manager* mis_manager;
	optimized_spawner* spawner;
	bool restock_lanchers;
	bool use_fuel;
	bool random_targets;

	std::vector<rendering::item_info*>missiles_obj;
	std::vector<int>missiles;
	std::vector<int >launchers;


	struct target {
		loc<int> map_loc;
		loc<double> real_space;
		rendering::item_info* target_model = NULL;
		double blink_time = 0;
	};

	//bounds to test fire on
	loc<int>topleft;
	loc<int>botright;

	double time_blink_max;
	int target_generate;
	std::vector< target*>targets;

};
