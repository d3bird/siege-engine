#include "crane.h"

#include <iostream>

crane::crane() {
	ID = -1;
	height = -1;
	radius = -1;
	running = false;
	aproaching_dest = false;
	current_angle = 0;
	destination_angle = 10;
	rot_speed = 1;
}

crane::crane(int heigh, int radiu, loc<int>location, int id){
	ID = id;
	height = heigh;
	radius = radiu;
	running = true;
	aproaching_dest = false;
	current_angle = 0;
	destination_angle = 10;
	rot_speed = 10;
	base_loc = location;
	arm_loc = location;
	arm_loc.y += height;

}

crane::~crane(){

}

void crane::update(double detlaTime) {
	bool updated = false;
	
	double x_displacement = arm_loc.x;
	double y_displacement = arm_loc.y;
	double z_displacement = arm_loc.z;

	current_angle += (rot_speed * detlaTime);

	double radius;

	for (int i = 0; i < arm.size(); i++) {

		radius = i;

		double x = sin(current_angle) * radius;
		double y = y_displacement; 
		double z = cos(current_angle) * radius;

		x += x_displacement;
		z += z_displacement;

		arm[i]->x_m = (x*2);
		arm[i]->y_m = (y * 2);
		arm[i]->z_m = (z*2);

		updated = true;

	}
	if (!updated) {
		aproaching_dest = false;
	}
}

void crane::set_dest(const loc<int>& aDest) {
	//dest = aDest;  
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
//	std::cout << "dest: " << dest.x<<","<< dest.y<<","<< dest.z << std::endl;
	std::cout << std::endl;
}
