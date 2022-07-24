#pragma once
#include "track_data.h"

#include <vector>

class track_manager {
public:
	track_manager();
	~track_manager();

	void update();

	void init();

private:
	std::vector<track*> active_tracks;
	
};