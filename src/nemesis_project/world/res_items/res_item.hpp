#pragma once

#include <vector>

/* res item description
* these are the data structures for the floor items 
*/

struct interactbility;

struct res_item
{
	int type =-1;
	int amount =-1;
	int max_amount =-1;
	interactbility* interaction = NULL;
};

struct recipe {
	std::vector< res_item*> inputs;
	int res_type_output;
};


//what can interact with the item
struct interactbility {
	bool template_struct = false;
	bool belt = false;
	bool crane = false;
	float lift_speed = 5.0f;
	bool person = false;
	bool creature = false;
	float modified_carry_speed = -1.0f;
};