#pragma once

#include "../core/optimized_spawner.h"
#include "../sensors/sensor_net.h"

#include "../common_obj/track_data/track_able.h"

#include "motion_manager_gui.h"
#include <unordered_map>

class motion_manger{
public:
	motion_manger();
	motion_manger(optimized_spawner* objm);
	~motion_manger();

	void update_track(track_data* data);

	void update_item(rendering::item_info* obj);
	void update_item_matrix(rendering::update_pak& up);

	void push_updates();
	void regester_sensor_net(sensor_net& net);

	//gui code
	void show_gui();
	void hide_gui();
	void draw_gui_window();
	void draw_gui_pannel();

private:

	bool is_data_tracked(track_data* data);

	optimized_spawner* OBJM;
	static motion_manger* instance;

	struct update {
		rendering::update_pak up;
		glm::mat4 mat;
		bool use_mat;
	};

	std::vector< update> updates;

	std::unordered_map< std::string, track_data*> track_stream;

	motion_manager_gui* motion_gui;
};

