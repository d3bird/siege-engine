#pragma once

#include "machine_base.h"

#include <vector>

class machine_manager
{
public:
	machine_manager();
	~machine_manager();

private:


	std::vector<machines::machine_base*> all_machines;
};

