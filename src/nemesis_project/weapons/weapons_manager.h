#pragma once

#include "weapons/weapon_base.h"
#include "weapons/cannon.h"
#include "turret.h"

#include <vector>

namespace weapons {

	class weapons_manager {
	public:

		weapons_manager();
		~weapons_manager();

		int spawn_turret(const loc<double>& location);
		void delete_weapon(int ID);

	private:
		int weapons_ids;

		std::vector<weapons::weapon*> all_weapons;

	};

}