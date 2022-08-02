#include "weapons_manager.h"

namespace weapons {

	weapons_manager::weapons_manager():
		weapons_ids(0)
	{

	}

	weapons_manager::~weapons_manager() {

	}

	int weapons_manager::spawn_turret(const loc<double>& location) {
		return -1;
	}

	void weapons_manager::delete_weapon(int ID) {

	}
}