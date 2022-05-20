#include "rotation.h"

#include <cmath>

rotation::rotation() {
	current_anlge = glm::mat4(0);
	x_angle = 0;
	y_angle = 0;
	z_angle = 0;

}

rotation::~rotation() {

}

void rotation::calc_new_matirix() {

	bool changed = false;
	float temp;

	//check angles 
	temp = check_angle(x_angle);
	if (temp != x_angle) {
		changed = true;
		x_angle = temp;
	}

	temp = check_angle(y_angle);
	if (temp != y_angle) {
		changed = true;
		y_angle = temp;
	}

	temp = check_angle(z_angle);
	if (temp != y_angle) {
		changed = true;
		y_angle = temp;
	}

	if (changed) {
		
		current_anlge = glm::mat4(0);

		if (x_angle != 0) {
		
		}

		if (y_angle != 0) {

		}

		if (z_angle != 0) {

		}


	}
}

float rotation::check_angle(float input) {
	//check angles 
	if (input < 0) {
		int temp = std::floor(input / 360) * -1;
		input = input + (360 * temp);
		input = 360 + input;
		input = 0;
	}
	else if (input > 360) {
		int temp = std::floor(input / 360);
		input = input - (360 * temp);
	}
	return input;
}

glm::mat4 rotation::get_matirx() {
	return current_anlge;
}

void rotation::inc_x_angle(float amount) {
	x_angle += amount;
	calc_new_matirix();
}

void rotation::inc_y_angle(float amount) {
	y_angle += amount;
	calc_new_matirix();
}

void rotation::inc_z_angle(float amount) {
	z_angle += amount;
	calc_new_matirix();
}

void rotation::dec_x_angle(float amount) {
	x_angle -= amount;
	calc_new_matirix();
}

void rotation::dec_y_angle(float amount) {
	y_angle -= amount;
	calc_new_matirix();
}

void rotation::dec_z_angle(float amount) {
	z_angle -= amount;
	calc_new_matirix();
}

void rotation::set_x_angle(float anagle) {
	x_angle = anagle;
	calc_new_matirix();
}

void rotation::set_y_angle(float anagle) {
	y_angle = anagle;
	calc_new_matirix();
}

void rotation::set_z_angle(float anagle) {
	z_angle = anagle;
	calc_new_matirix();
}
