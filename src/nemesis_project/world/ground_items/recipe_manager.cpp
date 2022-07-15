#include "recipe_manager.h"


const recipe_manager&  recipe_manager::get_instance() {
	const recipe_manager instance;
	return instance;
}


recipe_manager::recipe_manager()
{
}

recipe_manager::~recipe_manager()
{
}