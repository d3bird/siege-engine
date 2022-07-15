#pragma once

#include "grnd_obj_type.hpp"
#include "recipe_type.hpp"

#include <unordered_map>
#include <vector>

namespace grnd_items {

	class recipe {
	public:
		recipe(const std::unordered_map<grnd_obj_type, int>& aOutput,
			const std::unordered_map<grnd_obj_type, int>& aIngredients);
		~recipe();

		int get_output_amount(grnd_obj_type ingredient);
		int get_input_amount(grnd_obj_type ingredient);

		std::vector<std::pair< grnd_obj_type, int> >  get_outputs();
		std::vector<std::pair< grnd_obj_type, int> >  get_inputs();

	private:

		std::unordered_map<grnd_obj_type, int> ingredients;
		std::unordered_map<grnd_obj_type, int> output;

	};

}