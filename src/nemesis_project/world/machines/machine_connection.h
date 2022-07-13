#pragma	once

#include "../belts/belt.h"
#include "../rail/rail.h"

#include "../../common_obj/location.h"

namespace machines {

	enum connection_type
	{
		MIXED, NONE, RAIL, BELT
	};

	class machine_connection
	{
	public:
		machine_connection();
		~machine_connection();

		bool has_rail_connection();
		bool has_belt_connection();

		connection_type get_type();

		bool items_to_intake();

		void retrive_grnd_objs();

	protected:
		


	private:

		connection_type type;
		belt* belt_connection;
		railRoad::rail* rail_connection;

	};
}
