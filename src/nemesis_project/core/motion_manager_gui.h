#pragma once


#include <gui/GUI.h>

#include "../common_obj/track_data/track_able.h"

#include <unordered_map>

class motion_manager_gui
{
public:
	motion_manager_gui(std::unordered_map< std::string, track_data*>* input);
	~motion_manager_gui();

	void draw_gui_window();
	void draw_gui_pannel();

	void show();
	void hide();

private:
	bool show_window;

	std::unordered_map< std::string, track_data*>* input_stream;
};

