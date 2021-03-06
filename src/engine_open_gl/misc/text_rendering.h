#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "../rendering/model.h"
#include "../rendering/shader.h"
#include "external_files.hpp"
#include "time.h"


struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};


class text_engine{
public:
	text_engine();
	~text_engine();

	void draw();
	void update();
	void init();

	void RenderText(rendering::Shader* shader, std::string text, float x, float y, float scale, glm::vec3 color);

	void set_projection(glm::mat4 i) { projection = i; update_projection = true; }
	void set_cam(glm::mat4 i) { view = i; update_cam = true; }

	void set_time(timing* i) { Time = i; }

	void set_typing(bool i) { typing = i; }

	void add_char_to_message(char *i, bool remove = false);

	void send_meeage();
	void recive_message(std::string in);

	std::queue<std::string>* get_messages_to_send() { return messages_to_send; }

	void set_height_screen(unsigned int h) { SCR_HEIGHT = h; }
	void set_width_screen(unsigned int h) { SCR_WIDTH = h; }

private:

	void add_message_to_history(std::string in);

	external_paths paths;

	glm::mat4 view;
	glm::mat4 projection;
	bool update_projection;
	bool update_cam;

	bool typing;

	std::string message;
	std::string *message_history;
	std::queue<std::string>* messages_to_send;

	int max_history;

	timing* Time;
	float* deltatime;

	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;

	//text rendering data
	std::map<GLchar, Character> Characters;
	unsigned int VAO, VBO;
	FT_Library ft;
	rendering::Shader* shader;
};

