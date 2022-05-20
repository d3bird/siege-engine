#pragma once

#include "crane_manager.h"

class crane_manager_gui {
public:
	crane_manager_gui(crane_manager* acrane_mgr);
	crane_manager_gui();
	~crane_manager_gui();

	void draw();

private:
	crane_manager* crane_mgr;
	bool showing_window;
	int tab = 0;
};