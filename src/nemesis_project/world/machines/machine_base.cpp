#include "machine_base.h"

namespace machines {

	machine_base::machine_base(int id, int aconnections) :
		ID(id), num_connections(aconnections), connections(new machine_connection[aconnections])
	{
	}

	machine_base::~machine_base()
	{
	}

	bool machine_base::is_output_ready() {
		return output_ready;
	}

	bool machine_base::is_recipe_selected() {
		return recipe_selected;
	}

	int machine_base::get_ID() {
		return ID;
	}
}