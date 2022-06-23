#include "rotation.h"

#include <cmath>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

rotation::rotation():
	x_angle(0), y_angle(0), z_angle(0) {

}

rotation::~rotation() {

}

glm::mat4 rotation::get_matirx(glm::mat4& inputed) {

	if (!double_equals(x_angle, 0)) {
		inputed = glm::rotate(inputed, glm::radians(x_angle), glm::vec3(1, 0, 0));
	}
	if (!double_equals(y_angle, 0)) {
		inputed = glm::rotate(inputed, glm::radians(y_angle), glm::vec3(0, 1, 0));
	}
	if (!double_equals(z_angle, 0)) {
		inputed = glm::rotate(inputed, glm::radians(z_angle), glm::vec3(0, 0, 1));
	}

	return inputed;
}

void rotation::check_angle(float &input) {
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
}


void rotation::inc_x_angle(float amount) {
	x_angle += amount;
}

void rotation::inc_y_angle(float amount) {
	y_angle += amount;
}

void rotation::inc_z_angle(float amount) {
	z_angle += amount;
}

void rotation::dec_x_angle(float amount) {
	x_angle -= amount;
}

void rotation::dec_y_angle(float amount) {
	y_angle -= amount;
}

void rotation::dec_z_angle(float amount) {
	z_angle -= amount;
}

void rotation::set_x_angle(float anagle) {
	x_angle = anagle;
}

void rotation::set_y_angle(float anagle) {
	y_angle = anagle;
}

void rotation::set_z_angle(float anagle) {
	z_angle = anagle;
}

bool rotation::double_equals(float a, float b, float epsilon)
{
	return std::abs(a - b) < epsilon;
}