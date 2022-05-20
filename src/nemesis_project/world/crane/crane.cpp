#include "crane.h"

#include <iostream>

crane::crane() {
	ID = -1;
	height = -1;
	radius = -1;
	running = false;
	aproaching_dest = false;
}

crane::crane(int heigh, int radiu, int id){
	ID = id;
	height = heigh;
	radius = radiu;
	running = true;
	aproaching_dest = false;
}

crane::~crane(){

}

void crane::update(double detlaTime) {
	bool updated = false;
	for (int i = 0; i < arm.size(); i++) {
		if (arm[i].moving) {
			
			if (arm[i].current_loc.x != arm[i].end_loc.x) {
				updated = true;
			}


		}
	}

	if (!updated) {
		aproaching_dest = false;
	}
}

void crane::set_dest(const loc<int>& aDest) {
	dest = aDest;  
	aproaching_dest = true; 
}

void crane::print_info() {
	std::cout << std::endl;
	std::cout << "crane info: " << ID << std::endl;
	std::cout << "height: " << height << std::endl;
	std::cout << "radius: " << radius << std::endl;
	std::cout << "base amount: " << base.size() << std::endl;
	std::cout << "arm amount: " << arm.size() << std::endl;
	std::cout << "running: " << running << std::endl;
	std::cout << "aproaching_dest: " << aproaching_dest << std::endl;
	std::cout << "dest: " << dest.x<<","<< dest.y<<","<< dest.z << std::endl;
	std::cout << std::endl;
}
