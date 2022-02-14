#include "res_item_factory.h"

res_item_factory::res_item_factory() {

}

res_item_factory::~res_item_factory() {

}

res_item* res_item_factory::spawn_res_item(int type, int x, int y, int z) {
	res_item* output = NULL;
	interactbility* interaction = NULL;
	int amount = -1;
	int max_amount = -1;
	switch (type) {
	case 1:
		interaction = table["crane_only"];
		break;
	case 2:
		interaction = table["belt_only"];
		break;
	case 3:
		interaction = table["person_only"];
		break;
	case 4:
		interaction = table["creature_only"];
		break;
	case 5:
		interaction = table["none"];
		break;
	case 0:
	default:
		interaction = table["all"];
		break;
	}

	if (interaction != NULL) {
		output = new res_item;
		output->type = type;
		output->amount = 0;
		output->max_amount = def_stack_size;
		output->interaction = interaction;
	}

	return output;
}


//unused for now
//item_type res_item_factory::convert_res_obj(int type) {
//
//
//	return CUBE_T;
//}

void res_item_factory::init() {

	create_template_res();

}

void res_item_factory::create_template_res() {
	interactbility* crane = new interactbility;
	crane-> template_struct = true;
	crane->belt = false;
	crane->crane = true;
	crane->lift_speed = 5.0f;
	crane->person = false;
	crane->creature = false;
	crane->modified_carry_speed = -1.0f;
	table["crane_only"] = crane;

	interactbility* belt = new interactbility;
	belt->template_struct = true;
	belt->belt = true;
	belt->crane = false;
	belt->lift_speed = 0.0f;
	belt->person = false;
	belt->creature = false;
	belt->modified_carry_speed = -1.0f;
	table["belt_only"] = belt;

	interactbility* pers = new interactbility;
	pers->template_struct = true;
	pers->belt = false;
	pers->crane = false;
	pers->lift_speed = 5.0f;
	pers->person = false;
	pers->creature = false;
	pers->modified_carry_speed = -1.0f;
	table["person_only"] = pers;

	interactbility* creature = new interactbility;
	creature->template_struct = true;
	creature->belt = false;
	creature->crane = false;
	creature->lift_speed = 5.0f;
	creature->person = false;
	creature->creature = true;
	creature->modified_carry_speed = -1.0f;
	table["creature_only"] = creature;

	interactbility* all = new interactbility;
	all->template_struct = true;
	all->belt = true;
	all->crane = true;
	all->lift_speed = 5.0f;
	all->person = true;
	all->creature = true;
	all->modified_carry_speed = -1.0f;
	table["all"] = all;

	interactbility* none = new interactbility;
	none->template_struct = true;
	none->belt = false;
	none->crane = false;
	none->lift_speed = 5.0f;
	none->person = false;
	none->creature = false;
	none->modified_carry_speed = -1.0f;
	table["none"] = none;

	//any other custom item types
}