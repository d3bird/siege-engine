#pragma	once
#include "liquid_types.hpp"

/*
* This is the class that declares the 
*/
namespace Liquids {


	class liquid
	{
	public:
		liquid();
		~liquid();

		double get_flow_rate() { return flow_rate; }
		double get_amount_per_cell() { return amount_per_cell; }
		Liquids::liquid_type get_type() { return type; }

	private:

		double flow_rate;
		double amount_per_cell;

		liquid_type type;
	};
}