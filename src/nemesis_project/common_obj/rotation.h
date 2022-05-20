#pragma once 

#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

/*
* preforms the rotation matrix calculation for objects that need a complex angle
*/

class rotation {
public:
	rotation();
	~rotation();

	glm::mat4 get_matirx();

	void inc_x_angle(float amount);
	void inc_y_angle(float amount);
	void inc_z_angle(float amount);

	void dec_x_angle(float amount);
	void dec_y_angle(float amount);
	void dec_z_angle(float amount);

	void set_x_angle(float anagle);
	void set_y_angle(float anagle);
	void set_z_angle(float anagle);

	float get_x_angle() { return x_angle; }
	float get_y_angle() { return y_angle; }
	float get_z_angle() { return z_angle; }

private:

	void calc_new_matirix();
	float check_angle(float input);

	glm::mat4 current_anlge;

	float x_angle;
	float y_angle;
	float z_angle;

};