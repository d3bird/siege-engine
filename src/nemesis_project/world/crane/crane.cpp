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
	attachment = NULL;
	attachment_move_speed = 5;
}

crane::crane(int heigh, int radiu, loc<int>location, int id){
	ID = id;
	height = heigh;
	radius = radiu;
	running = true;
	aproaching_dest = false;
	current_angle = 0;
	destination_angle = 90;
	rot_speed = 20;
	base_loc = location;
	arm_loc = location;
	arm_loc.y += height;
	attachment_loc.x = arm_loc.x;
	attachment_loc.y = arm_loc.y-1;
	attachment_loc.z = arm_loc.z;

	attachment = NULL;
	attachment_move_speed = 5;
	attachment_rad_pos = radius - 1;
	attachment_rad_pos_dest = attachment_rad_pos;

	update_arm = true;
	update_attach = true;
}

crane::~crane(){

}

#ifndef PI
#define PI 3.14159265
#endif // !PI

void crane::update(double detlaTime) {
	bool updated = false;

	double x_displacement = arm_loc.x;
	double y_displacement = arm_loc.y;
	double z_displacement = arm_loc.z;

	//updated the angle based on change

	double angle_change = (rot_speed * detlaTime);
	bool reached_angle = false;

	if (current_angle < destination_angle) {
		current_angle += angle_change;
		if (current_angle >= destination_angle) {
			current_angle = destination_angle;
			reached_angle = true;
		}
	}
	else if (current_angle > destination_angle) {
		current_angle -= angle_change;
		if (current_angle <= destination_angle) {
			current_angle = destination_angle;
			reached_angle = true;
		}
	}
	else {
		reached_angle = true;
	}


	//if (current_angle >= destination_angle) {
	//	current_angle = destination_angle;
	//	reached_angle = true;
	//}
	//else {
	//	//	std::cout << "current_angle " << current_angle << std::endl;
	//	//	std::cout << "destination_angle " << destination_angle << std::endl;
	//}


	/*if (current_angle >= 360) {
		current_angle -= 360;
	}
	else if (current_angle < 0) {
		current_angle == 360;
	}*/

	double radius;
	double x, y, z;

	//update the arm possition
	for (int i = 0; i < arm.size(); i++) {

		//radius = i - 1;
		radius = i;

		x = sin(current_angle * PI / 180) * radius;
		y = y_displacement;
		z = cos(current_angle * PI / 180) * radius;

		x += x_displacement;
		z += z_displacement;

		arm[i]->x_m = (x * 2);
		arm[i]->y_m = (y * 2);
		arm[i]->z_m = (z * 2);

		arm[i]->angles.set_y_angle(current_angle);

		updated = true;

	}

	//update the atachment possition
	if (update_arm) {
		bool update_atch = false;
		if (attachment_rad_pos < attachment_rad_pos_dest) {
			attachment_rad_pos += (detlaTime * attachment_move_speed);
			if (attachment_rad_pos > attachment_rad_pos_dest) {
				attachment_rad_pos = attachment_rad_pos_dest;
			}
			update_atch = true;
		}
		else if (attachment_rad_pos > attachment_rad_pos_dest) {
			attachment_rad_pos -= (detlaTime * attachment_move_speed);
			if (attachment_rad_pos < attachment_rad_pos_dest) {
				attachment_rad_pos = attachment_rad_pos_dest;
			}
			update_atch = true;
		}

		if (update_atch) {
			radius = attachment_rad_pos;

			x = sin(current_angle * PI / 180) * radius;
			y = y_displacement - 1;
			z = cos(current_angle * PI / 180) * radius;

			x += x_displacement;
			z += z_displacement;

			attachment->x_m = (x * 2);
			attachment->y_m = (y * 2);
			attachment->z_m = (z * 2);

			attachment->angles.set_y_angle(current_angle);

			update_arm = true;
		}
	}


	if (reached_angle) {
		aproaching_dest = false;
		//std::cout << "no longer aproaching the dest" << std::endl;
	}
}

bool crane::set_dest(const loc<int>& aDest) {
	bool output = can_reach_dest(aDest);


	if (output) {
		dest = aDest;
		aproaching_dest = true;
		destination_angle = atan(aDest.z / aDest.x) * 180 / PI;

	}
	else {
	//	std::cout << "can not reach given destination" << std::endl;
	}

	return output;
}

bool crane::can_reach_dest(const loc<int>& aDest) {
	//(x - center_x)² + (y - center_y)² < radius²

	double x_com = aDest.x - base_loc.x;
	double z_com = aDest.z - base_loc.z;

	return ((x_com * x_com) + (z_com * z_com) < (radius * radius));
	/*return (base_loc != aDest)&&((aDest.x - base_loc.x) * (aDest.x - base_loc.x) +
		(aDest.z - base_loc.z) * (aDest.z - base_loc.z) <= radius * radius);*/
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
