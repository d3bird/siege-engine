#pragma once

#include "rendering/object_manger.h"
#include "audio/audio_manger.h"
#include "misc/text_rendering.h"
#include "misc/time.h"
#include "core/camera.h"

enum draw_mode {DRAW_EVERYTHING, ONY_GROUP,LINKED_GROUP,RENDERING_QUE};
enum lighting_mode { LIGH_EVERYTHING, NO_SHADOW, NONE };
enum gui_draw{DRAW_ENGINES_GUI, DRAW_SCENE_GUI, DRAW_BOTH_GUI, DRAW_NONE_GUI};

struct engine_obj {
	object_manger* OBJM =NULL;
	audio_manger* ADM = NULL;
	timing* time = NULL;

	Camera* cam = NULL;

	text_engine* text_render = NULL;

	draw_mode draw_optimize = DRAW_EVERYTHING;
	lighting_mode light_setting = LIGH_EVERYTHING;

	int group_ID =-1;

	gui_draw gui_draw_type = DRAW_ENGINES_GUI;

	void (*keyboard_in)(int key, int scancode, int action, int mods) = NULL;
	void (*def_keyboard_in)(int key, int scancode, int action, int mods) = NULL;

	bool fully_inited() {
		if (OBJM == NULL || ADM == NULL || time == NULL || 
			text_render == NULL) {
			return false;
		}
		else {
			return true;
		}
	}

};


static void print_engine_data(engine_obj* output) {
	std::cout << "" << std::endl;
	std::cout << "printing engine data" << std::endl;

	if (output->OBJM == NULL) {
		std::cout << "OBJM was NULL" << std::endl;
	}
	else {
		std::cout << "OBJM was created and linked" << std::endl;
	}

	if (output->ADM == NULL) {
		std::cout << "ADM was NULL" << std::endl;
	}
	else {
		std::cout << "ADM was created and linked" << std::endl;
	}

	if (output->time == NULL) {
		std::cout << "time was NULL" << std::endl;
	}
	else {
		std::cout << "time was created and linked" << std::endl;
	}

	if (output->cam == NULL) {
		std::cout << "cam was NULL" << std::endl;
	}
	else {
		std::cout << "cam was created and linked" << std::endl;
	}

	if (output->text_render == NULL) {
		std::cout << "text_render was NULL" << std::endl;
	}
	else {
		std::cout << "text_render was created and linked" << std::endl;
	}


	std::cout << "draw mode is set to ";

	switch (output->draw_optimize)
	{
	case DRAW_EVERYTHING:
		std::cout << "DRAW_EVERYTHING" << std::endl;
		break;
	case ONY_GROUP:
		std::cout << "ONY_GROUP" << std::endl;
		break;
	case LINKED_GROUP:
		std::cout << "LINKED_GROUP" << std::endl;
		break;
	case RENDERING_QUE:
		std::cout << "RENDERING_QUE" << std::endl;
		break;
	default:
		std::cout << "UNKOWN" << std::endl;
		break;
	}

	std::cout << "lighting is set to ";

	switch (output->light_setting)
	{
	case LIGH_EVERYTHING:
		std::cout << "LIGH_EVERYTHING" << std::endl;
		break;
	case NO_SHADOW:
		std::cout << "NO_SHADOW" << std::endl;
		break;
	case NONE:
		std::cout << "NONE" << std::endl;
		break;
	default:
		std::cout << "UNKOWN" << std::endl;
		break;
	}

	std::cout << "GUI is set to ";

	switch (output->gui_draw_type)
	{
	case DRAW_ENGINES_GUI:
		std::cout << "DRAW_ENGINES_GUI" << std::endl;
		break;
	case DRAW_SCENE_GUI:
		std::cout << "DRAW_SCENE_GUI" << std::endl;
		break;
	case DRAW_BOTH_GUI:
		std::cout << "DRAW_BOTH_GUI" << std::endl;
		break;
	case DRAW_NONE_GUI:
		std::cout << "DRAW_NONE_GUI" << std::endl;
		break;
	default:
		std::cout << "UNKOWN" << std::endl;
		break;
	}

	std::cout << "overall the engine data was "
		<< (output->fully_inited() ? "fully" : "not fully") << " inited" << std::endl;

	std::cout << "" << std::endl;
}