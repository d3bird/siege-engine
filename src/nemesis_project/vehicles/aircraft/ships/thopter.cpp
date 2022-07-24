#include "thopter.h"

thopter::thopter(int id) : fuel(10, 1),
	ID(id),
	base(NULL), fl_wing(NULL), fr_wing(NULL), bl_wing(NULL), br_wing(NULL),
	current_route(NULL),
	angle_speed(30),
	move_speed(5),
	angle(),
	wing_speed(50)
{

}

thopter::~thopter() {

}

void thopter::update(double time) {
//	calc_wing_possition(time);
}

bool thopter::operator==(const int& id) {
	return ID == id;
}

int thopter::get_ID() { 
	return ID; 
}

loc<int> thopter::get_location() {
	return location;
}

double thopter::get_move_speed_static() { 
	return move_speed;
}

double thopter::get_angle_speed_static() {
	return angle_speed;
}

void thopter::set_location(loc<int> alocation) {
	location = alocation;
	current_location = location;
	
	update_model_loc_from_saved();
}

double thopter::get_move_speed(double distance, double angle_change_req) {
	double output = move_speed;

	if(angle_change_req >=120){
		output /= 2;
	}
	else if (angle_change_req >= 90) {
		output /= 2;

	}
	else if (angle_change_req >= 60) {
		output /= 2;

	}
	else if (angle_change_req >= 30) {
		//output /= 4;

	}
	/*else if(distance >= 10) {
		output *= 1.5;
	}*/

	return output;
}


double thopter::get_angle_speed(double distance, double angle_change_req) {
	double output = angle_speed;

	if (angle_change_req >= 120) {
		output *= 5;
	}
	else if (angle_change_req >= 90) {
		output *= 4;

	}
	else if (angle_change_req >= 60) {
		output *= 3;

	}
	else if (angle_change_req >= 30) {
		output *= 2;

	}

	return output;
}

void thopter::update_model_loc(const loc<double>& alocation,const rendering::rotation& asangle) {
	current_location = alocation;
	angle = asangle;

	update_model_loc_from_saved();
}

void thopter::update_model_loc_from_saved() {

	if (base != NULL) {
		base->x_m = current_location.x;
		base->y_m = current_location.y;
		base->z_m = current_location.z;
		base->angles = angle;
	}

	if (fl_wing != NULL) {
		fl_wing->x_m = current_location.x;
		fl_wing->y_m = current_location.y;
		fl_wing->z_m = current_location.z;
		fl_wing->angles = angle;
	}

	if (fr_wing != NULL) {
		fr_wing->x_m = current_location.x;
		fr_wing->y_m = current_location.y;
		fr_wing->z_m = current_location.z;
		fr_wing->angles = angle;
	}

	if (bl_wing != NULL) {
		bl_wing->x_m = current_location.x;
		bl_wing->y_m = current_location.y;
		bl_wing->z_m = current_location.z;
		bl_wing->angles = angle;
	}

	if (br_wing != NULL) {
		br_wing->x_m = current_location.x;
		br_wing->y_m = current_location.y;
		br_wing->z_m = current_location.z;
		br_wing->angles = angle;
	}

	set_wing_location();
}

void thopter::start_landing_animation() {
	taking_off = false;
	landing = true;
	flying = false;

	//set to match the body
	fl_wing_angle = angle;
	fr_wing_angle = angle;
	bl_wing_angle = angle;
	br_wing_angle = angle;

	//set angle in the reverse possition
	fl_wing_angle.inc_z_angle(80);
	fl_wing_angle.inc_x_angle(80);
	fl_wing_angle.dec_y_angle(25);




}

void thopter::start_take_off_animation() {
	taking_off = true;
	landing = false;
	flying = false;

	//set to match the body rotation
	fl_wing_angle = angle;
	fr_wing_angle = angle;
	bl_wing_angle = angle;
	br_wing_angle = angle;
}

void thopter::start_flying() {
	taking_off = false;
	landing = false;
	flying = true;

	//set to match the body rotation
	fl_wing_angle = angle;
	fl_pos_dir = true;
	fr_wing_angle = angle;
	fr_pos_dir = true;
	bl_wing_angle = angle;
	bl_pos_dir = true;
	br_wing_angle = angle;
	br_pos_dir = true;
}

bool thopter::is_landing() {
	return landing;
}

bool thopter::is_taking_off() {
	return taking_off;
}

bool thopter::is_flying() {
	return flying;
}

void thopter::calc_wing_possition(double time) {
	double change = time * wing_speed;

	if (flying) {
		if (fl_pos_dir) {
			fl_wing_angle.inc_x_angle(change);
			if (fl_wing_angle.get_x_angle() > angle.get_x_angle() + 40) {
				fl_pos_dir = false;
			}
		}
		else {
			fl_wing_angle.dec_x_angle(change);
			if (fl_wing_angle.get_x_angle() < angle.get_x_angle() - 40) {
				fl_pos_dir = true;
			}
		}
		fl_wing->angles.set_x_angle(fl_wing_angle.get_x_angle());

		if (fr_pos_dir) {
			fr_wing_angle.inc_x_angle(change);
			if (fr_wing_angle.get_x_angle() > angle.get_x_angle() + 220) {
				fr_pos_dir = false;
			}
		}
		else {
			fr_wing_angle.dec_x_angle(change);
			if (fr_wing_angle.get_x_angle() < angle.get_x_angle() - 220) {
				fr_pos_dir = true;
			}
		}
		fr_wing->angles.set_x_angle(fr_wing_angle.get_x_angle());

		if (bl_pos_dir) {
			bl_wing_angle.inc_x_angle(change);
			if (bl_wing_angle.get_x_angle() > angle.get_x_angle() + 40) {
				bl_pos_dir = false;
			}
		}
		else {
			bl_wing_angle.dec_x_angle(change);
			if (bl_wing_angle.get_x_angle() < angle.get_x_angle() - 40) {
				bl_pos_dir = true;
			}
		}
		bl_wing->angles.set_x_angle(bl_wing_angle.get_x_angle());

		if (br_pos_dir) {
			br_wing_angle.inc_x_angle(change);
			if (br_wing_angle.get_x_angle() > angle.get_x_angle() + 220) {
				br_pos_dir = false;
			}
		}
		else {
			br_wing_angle.dec_x_angle(change);
			if (br_wing_angle.get_x_angle() < angle.get_x_angle() - 220) {
				br_pos_dir = true;
			}
		}
		br_wing->angles.set_x_angle(br_wing_angle.get_x_angle());

	}


}

void thopter::set_wing_location() {
	if (fl_wing != NULL) {
		fl_wing->x_m = current_location.x - 1.2;
		fl_wing->y_m = current_location.y + 1.5;
		fl_wing->z_m = current_location.z + 0.9;

	}

	if (fr_wing != NULL) {
		fr_wing->x_m = current_location.x - 1.2;
		fr_wing->y_m = current_location.y + 1.5;
		fr_wing->z_m = current_location.z - 0.9;
		fr_wing->angles.set_x_angle(180);
	}

	if (bl_wing != NULL) {
		bl_wing->x_m = current_location.x + 2.5;
		bl_wing->y_m = current_location.y + 1.5;
		bl_wing->z_m = current_location.z + 0.9;
	}

	if (br_wing != NULL) {
		br_wing->x_m = current_location.x + 2.5;
		br_wing->y_m = current_location.y + 1.5;
		br_wing->z_m = current_location.z - 0.9;
		br_wing->angles.set_x_angle(180);
	}
}