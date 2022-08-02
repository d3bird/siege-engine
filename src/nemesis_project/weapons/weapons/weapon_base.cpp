#include "weapon_base.h"

#include "../../utility/math/random_gen.h"
#include "../../utility/math/utility_math.h"

namespace weapons {

	weapon::weapon(int id, loc <double> alocation):
		cool_down(0), fire_cool_down(.1), chance_to_jam(0),
		jammed(false), shots_left(0), max_shots(30), ID(id),
		location(alocation)
	{
	}

	weapon::~weapon()
	{
	}


	bool weapon::can_fire() {
		return !jammed &&
			shots_left > 0 &&
			mathfunc::double_equals(0, fire_cool_down);
	}

	bool weapon::is_jammed() {
		return jammed;
	}

	void weapon::unjam() {
		if (shots_left > 0) {
			shots_left--;
		}
		jammed = false;
	}

	bool weapon::is_ammo_left() {
		return shots_left > 0;
	}

	int weapon::add_ammo(int amount) {
		int output = 0;
		shots_left += amount;
		if (shots_left < 0) {
			output = shots_left * -1;
			shots_left = 0;
		}
		else if(shots_left > max_shots) {
			output = shots_left - max_shots;
			shots_left = max_shots;
		}

		return output;
	}

	int weapon::get_ID() {
		return ID;
	}

	loc <double> weapon::get_location() {
		return location;
	}

	inline bool weapon::did_weapon_jam() {
		int odds = mathfunc::get_random_num(0, 100);
		return odds <= chance_to_jam;
	}

}