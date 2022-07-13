#include "machine_connection.h"

namespace machines {

	machine_connection::machine_connection() :
		type(NONE), belt_connection(NULL), rail_connection(NULL)
	{
	}

	machine_connection::~machine_connection()
	{
	}


	bool machine_connection::has_rail_connection(){
		return rail_connection != NULL;
	}
	bool machine_connection::has_belt_connection() {
		return belt_connection != NULL;

	}

	connection_type machine_connection::get_type() {
		return type;
	}

	bool machine_connection::items_to_intake() {
		return false;
	}

	void machine_connection::retrive_grnd_objs() {

	}

}