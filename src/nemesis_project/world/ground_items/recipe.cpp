#include "recipe.h"

namespace grnd_items {

	recipe::recipe(const std::unordered_map<grnd_obj_type, int>& aOutput,
		const std::unordered_map<grnd_obj_type, int>& aIngredients):
		ingredients(aIngredients), output(aOutput)
	{
	}

	recipe::~recipe()
	{
	}

	int recipe::get_output_amount(grnd_obj_type ingredient) {
		int output_amount = -1;
		auto search = output.find(ingredient);
		if (search != output.end()) {
			output_amount = search->second;
		}
		return output_amount;
	}

	int recipe::get_input_amount(grnd_obj_type ingredient) {
		int input_amount = -1;
		auto search = ingredients.find(ingredient);
		if (search != ingredients.end()) {
			input_amount = search->second;
		}
		return input_amount;
	}

	std::vector<std::pair< grnd_obj_type, int> >  recipe::get_outputs() {
		std::vector<std::pair< grnd_obj_type, int> > output_vec;

		for (auto &it : output){
			output_vec.push_back(std::pair< grnd_obj_type, int>(it.first, it.second));
		}

		return output_vec;
	}

	std::vector<std::pair< grnd_obj_type, int> >  recipe::get_inputs() {
		std::vector<std::pair< grnd_obj_type, int> > output_vec;

		for (auto& it : ingredients) {
			output_vec.push_back(std::pair< grnd_obj_type, int>(it.first, it.second));
		}

		return output_vec;
	}
}