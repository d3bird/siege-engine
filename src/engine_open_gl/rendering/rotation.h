#pragma once 

#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

/*
* preforms the rotation matrix calculation for objects that need a complex angle
* 
* x_angle is the angle that deals with the spin of the object
* y_angle is the angle that deals with the x/z axis
* z_angle is the angle that deals with the  y axis
* 
*/

class rotation {
public:
	rotation();
	~rotation();

	glm::mat4 get_matirx(glm::mat4 & inputed);

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

	bool operator==(const rotation& other);
	void operator=(const rotation& other);

private:

	bool double_equals(float a, float b, float epsilon = 0.001);

	void check_angle(float &input);

	float x_angle;
	float y_angle;
	float z_angle;

	glm::quat rotation_quat;

};