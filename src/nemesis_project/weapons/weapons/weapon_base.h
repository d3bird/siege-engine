#pragma once

#include "../../common_obj/location.h"
#include "../../common_obj/track_data/track_weapon_data.h"

#include <rendering/rendering_object_data.hpp>
#include "../../core/spawning_enums.hpp"

namespace weapons {
	class weapon
	{
	public:
		weapon(int id, loc <double> alocation);
		~weapon();

		virtual void fire() = 0;
		virtual void get_track_weapon_data()=0;

		bool can_fire();
		bool is_jammed();
		void unjam();

		bool is_ammo_left();
		
		//returns the extra
		int add_ammo(int amount);

		int get_ID();
		loc <double> get_location();

	protected:

		inline bool did_weapon_jam();

		//time between shots
		double cool_down;
		double fire_cool_down;

		int chance_to_jam;//scale of 0 to 100
		bool jammed;

		int shots_left;
		int max_shots;

	private:

		int ID;
		loc <double> location;
	

	};

}