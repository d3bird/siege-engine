#pragma once

#include "recipe_type.hpp"
#include "recipe.h"

class recipe_manager{
public:

	static const recipe_manager& get_instance();
	~recipe_manager();




private:

	recipe_manager();


};
