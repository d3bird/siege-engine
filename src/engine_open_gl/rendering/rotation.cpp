#include "rotation.h"

#include <cmath>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace rendering {

	rotation::rotation() :
		x_angle(0.0f), y_angle(0.0f), z_angle(0.0f) {

	}


	rotation::rotation(float aX_angle, float aY_angle, float aZ_angle) {
		x_angle = aX_angle;
		y_angle = aY_angle;
		z_angle = aZ_angle;
	}

	rotation::~rotation() {

	}

	glm::mat4 rotation::get_matirx(glm::mat4& inputed) {

		inputed = inputed * glm::toMat4(glm::quat(
			glm::vec3(glm::radians(x_angle), glm::radians(y_angle), glm::radians(z_angle))));

		//this is the old way of doing roations around a single axis 
		// this however causes gimble lock that dirasticle affects the way the rotation turns out
		//if (!float_equals(x_angle, 0)) {
		//	inputed = glm::rotate(inputed, glm::radians(x_angle), glm::vec3(1, 0, 0));
		//}
		//
		//if (!float_equals(y_angle, 0)) {
		//	inputed = glm::rotate(inputed, glm::radians(y_angle), glm::vec3(0, 1, 0));
		//}

		//if (!float_equals(z_angle, 0)) {
		//	inputed = glm::rotate(inputed, glm::radians(z_angle), glm::vec3(0, 0, 1));
		//}

		return inputed;
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

	void rotation::set_angles(float aX_angle, float aY_angle, float aZ_angle) {
		x_angle = aX_angle;
		y_angle = aY_angle;
		z_angle = aZ_angle;
	}

	bool rotation::rotate_to(double change, float aX_angle, float aY_angle, float aZ_angle) {
		return rotate_angle_to(change, aX_angle, 0) &&
		rotate_angle_to(change, aY_angle, 1) &&
		rotate_angle_to(change, aZ_angle, 2);
	}

	bool rotation::rotate_to(double change, rotation& new_angle) {
		return rotate_to(change,new_angle.get_x_angle(), new_angle.get_y_angle(), new_angle.get_z_angle());
	}

	bool rotation::rotate_angle_to(double change, float target_angle, int which_angle) {

		//correct the target angle 
		check_angle(target_angle);

		//set the working angle
		float angle;
		if (which_angle == 0) {
			angle = x_angle;
		}
		else if (which_angle == 1) {
			angle = y_angle;
		}
		else if (which_angle == 2) {
			angle = z_angle;
		}
		else {
			return true;
		}

		bool output = false;

		//check to makesure the angle has not been reached or is in reach
		bool quick_change = false;

		if (float_equals(angle, target_angle)) {//check for ==
			return true;
		}
		else {

			//check for close change
			if (angle < target_angle) {
				if (angle + change >= target_angle) {
					angle = target_angle;
					quick_change = true;
					output = true;
				}
			}
			else {
				if (angle - change <= target_angle) {
					angle = target_angle;
					quick_change = true;
					output = true;
				}
			}

		}

		if (!quick_change) {

			//calculate the distance for each direction
			double clock_wise = std::abs(target_angle - angle);
			double counter_clock = ((360 - target_angle) + angle);

			if (clock_wise < counter_clock) {
				if (clock_wise < change) {
					angle = target_angle;
					output = true;
				}
				else {
					angle += change;
				}
			}
			else {
				if (counter_clock < change) {
					angle = target_angle;
					output = true;
				}
				else {
					angle -= change;
				}
			}
		}

		//check the angle for errors
		check_angle(angle);

		//update the angle that was being worked on
		if (which_angle == 0) {
			x_angle = angle;
		}
		else if (which_angle == 1) {
			y_angle = angle;
		}
		else if (which_angle == 2) {
			z_angle = angle;
		}
		return output;
	}

	bool  rotation::rotate_angle_clock_wise(double change, float target_angle, int which_angle) {
		bool output = false;
		if (which_angle == 0) {
			if (!float_equals(x_angle, target_angle)) {

			 x_angle -= change;
			}
			else {
				output = true;
			}
		}
		else if (which_angle == 1) {
			if (!float_equals(y_angle, target_angle)) {
				y_angle -= change;
			}
			else {
				output = true;
			}
		}
		else if (which_angle == 2) {
			if (!float_equals(z_angle, target_angle)) {
				z_angle -= change;
			}
			else {
				output = true;
			}
		}
		return output;
	}

	bool rotation::rotate_angle_counter_clock_wise(double change, float target_angle, int which_angle) {
		bool output = false;
		if (which_angle == 0) {
			if (!float_equals(x_angle, target_angle)) {
				x_angle += change;
			}
			else {
				output = true;
			}
		}
		else if (which_angle == 1) {
			if (!float_equals(y_angle, target_angle)) {
				y_angle += change;
			}
			else {
				output = true;
			}
		}
		else if (which_angle == 2) {
			if (!float_equals(z_angle, target_angle)) {
				z_angle += change;
			}
			else {
				output = true;
			}
		}
		return output;
	}

	bool rotation::float_equals(float a, float b, float epsilon)
	{
		return std::abs(a - b) < epsilon;
	}

	bool rotation::operator==(const rotation& other) {
		return (float_equals(x_angle, other.x_angle) &&
			float_equals(y_angle, other.y_angle) &&
			float_equals(z_angle, other.z_angle));
	}

	void rotation::operator=(const rotation& other) {
		x_angle = other.x_angle;
		y_angle = other.y_angle;
		z_angle = other.z_angle;
	}

	std::string rotation::to_string() {
		return ("x angle: " + std::to_string(x_angle) + ", y angle: " + std::to_string(y_angle)+
			", z angle: " + std::to_string(z_angle));
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

	bool rotation::rotate_angle(float& input, float change, float target, bool clock_wise) {
		bool reached_target = false;
		if (!float_equals(input, target)) {
			bool less_that = input < target;

			if (clock_wise) {
				input -= change;
			}
			else {
				input += change;
			}


			if (less_that) {
				if (input > target) {
					input = target;
					reached_target = true;
				}
			}
			else {

				if (input >= 360) {
					target += 360;
				}

				if (input < target) {
					input = target;
					reached_target = true;
				}
			}

			check_angle(input);
		
		}
		else {
			input = target;
			reached_target = true;
		}
		return reached_target;
	}
}