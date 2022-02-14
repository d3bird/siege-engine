#pragma once

#include "res_item.hpp"
#include <unordered_map>

class res_item_factory {
public:
	res_item_factory();
	~res_item_factory();

	//creates a res_item representaion that can be linked to object
	res_item* spawn_res_item(int type, int x, int y, int z);

private:

	void init();
	void create_template_res();
	//item_type convert_res_obj(int type);

	int def_stack_size = 10;

	//table for the template interactbilitys
	std::unordered_map<std::string, interactbility*> table;

};