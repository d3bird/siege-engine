#pragma once

#include <unordered_map>
#include <vector>

#include "../../common_obj/location.h"

#include "crane.h"

class crane_manager {
	public:
	crane_manager();
	~crane_manager();

	void update(double detlaTime);

	private:
	//	std::unordered_map<loc<int>, crane> cranes;


};