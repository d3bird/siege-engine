#include "rotation.h"

#include <cmath>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace rendering {

	rotation::rotation() :
		x_angle(0.0f), y_angle(0.0f), z_angle(0.0f) {

	}

	rotation::~rotation() {

	}

	glm::mat4 rotation::get_matirx(glm::mat4& inputed) {

		rotation_quat = glm::quat(glm::vec3(glm::radians(x_angle), glm::radians(y_angle), glm::radians(z_angle)));

		inputed = inputed * glm::toMat4(rotation_quat);

		//this is the old way of doing roations around a single axis 
		// this however causes gimble lock that dirasticle affects the way the rotation turns out
		//if (!double_equals(x_angle, 0)) {
		//	inputed = glm::rotate(inputed, glm::radians(x_angle), glm::vec3(1, 0, 0));
		//}
		//
		//if (!double_equals(y_angle, 0)) {
		//	inputed = glm::rotate(inputed, glm::radians(y_angle), glm::vec3(0, 1, 0));
		//}

		//if (!double_equals(z_angle, 0)) {
		//	inputed = glm::rotate(inputed, glm::radians(z_angle), glm::vec3(0, 0, 1));
		//}

		return inputed;
	}

	void rotation::check_angle(float& input) {
		//check angles 
		if (input < 0) {
			float temp = std::floor(input / 360) * -1;
			input = input + (360 * temp);
			input = 360 + input;
			input = 0;
		}
		else if (input > 360) {
			float temp = std::floor(input / 360);
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

	bool rotation::operator==(const rotation& other) {
		return (double_equals(x_angle, other.x_angle) &&
			double_equals(y_angle, other.y_angle) &&
			double_equals(z_angle, other.z_angle));
	}

	void rotation::operator=(const rotation& other) {
		x_angle = other.x_angle;
		y_angle = other.y_angle;
		z_angle = other.z_angle;
	}
}