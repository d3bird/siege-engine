#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "../rendering/model.h"
#include "../rendering/shader.h"
#include "../misc/time.h"

class lighting{
public:
	lighting();
	~lighting();

	void preform_lighting_calcs();

	void update();

	void init();

	//setters
	void set_projection(glm::mat4 i) { projection = i; }
	void set_cam(glm::mat4 i) { view = i; }
	void set_time(timing* i) { Time = i; }

	void set_cam_pos(glm::vec3 i) { cam_pos = i; }

	//getters
	rendering::Shader* get_gem_shader() { return shaderGeometryPass; }
	rendering::Shader* get_lighting_shader() { return shaderLightingPass; }

	void set_height_screen(unsigned int h) { SCR_HEIGHT = h; }
	void set_width_screen(unsigned int h) { SCR_WIDTH = h; }

private:

	glm::mat4 view;
	glm::mat4 projection;
	glm::vec3 cam_pos;
	timing* Time;

	bool draw_light_cubes;//the possition of the light sources

	bool update_light_info;

	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;


	//deffered lighting vars
	rendering::Shader* shaderGeometryPass;
	rendering::Shader* shaderLightingPass;
	rendering::Shader* shaderLightBox;

	std::vector<glm::mat4> objectPositions;
	glm::mat4* modelMatrices;
	glm::mat4 model;
	rendering::Model* backpack;
	unsigned int mod_buffer;
	unsigned int gBuffer;
	unsigned int gPosition, gNormal, gAlbedoSpec;
	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	unsigned int rboDepth;
	const unsigned int NR_LIGHTS = 32;
	std::vector<glm::vec3> lightPositions;
	std::vector<glm::vec3> lightColors;

	unsigned int quadVAO = 0;
	unsigned int quadVBO;
	unsigned int cubeVAO = 0;
	unsigned int cubeVBO = 0;

	void renderCube();
	void renderQuad();

};

