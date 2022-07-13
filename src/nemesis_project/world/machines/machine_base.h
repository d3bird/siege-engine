#pragma	once

#include "machine_connection.h"

namespace machines {

	class machine_base
	{
	public:
		machine_base(int ID,int aconnections);
		~machine_base();

		virtual void update() = 0;

		bool is_output_ready();
		bool is_recipe_selected();

		int get_ID();

	protected:

		bool output_ready;
		bool recipe_selected;
		
		machine_connection* connections;
		int num_connections;

	private:
		int ID;
	};
}
