#pragma once

#include <engine_api.h>

#include <iostream>

struct data_ball {
	rendering::object_manger* OBJM = NULL;
	audio_syst::audio_manger* AM = NULL;
	light_mgr* LM = NULL;
	GUI* gui = NULL;
	timing* time = NULL;
	Camera* camera = NULL;

	data_ball(engine_api* API) {
		data_ball* output = NULL;

		if (API != NULL) {
			OBJM = API->get_OBJM();
			AM = API->get_AM();
			//LM = API->get_LM();
			gui = API->get_engine_gui();
			time = API->get_timing();
			camera = API->get_camera();

		}
	}

	bool engine_full_inited() {
		bool output = false;


		if (OBJM == NULL) {
			output = false;
			std::cout << "databall OBJM is NULL" << std::endl;
		}
		if (AM == NULL) {
			std::cout << "databall AM is NULL" << std::endl;
			output = false;
		}
		if (LM == NULL) {
			std::cout << "databall LM is NULL" << std::endl;
			output = false;
		}
		if (gui == NULL) {
			std::cout << "databall gui is NULL" << std::endl;
			output = false;
		}
		if (camera == NULL) {
			std::cout << "databall camera is NULL" << std::endl;
			output = false;
		}
		if (time == NULL) {
			std::cout << "databall time is NULL" << std::endl;
			output = false;
		}
		if (camera == NULL) {
			std::cout << "databall camera is NULL" << std::endl;
			output = false;
		}
		if (output) {
			std::cout << "databall was fully inited" << std::endl;

		}
		return output;
	}



};


