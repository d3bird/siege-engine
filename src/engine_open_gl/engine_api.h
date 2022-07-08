#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "rendering/shader.h"
#include "core/camera.h"
#include "rendering/model.h"
#include "engine.h"
#include "misc/time.h"
#include "core/keyboard_manger.h"
#include "misc/text_rendering.h"
#include "core/skymap.h"


#include "engine_obj.hpp"

#include "gui/GUI.h"

/* This is starting point of the engine
* The engine will create the window context
* It will also init the singleton controllers for each substystem
* 
* the main api will init/modify the window context, update systems accordingly
*
* The draw function updates the window with the given state of its objects 
* 
* The API can can also be inited from a API settings struct that will handle alot of the 
* manual setup, then grab one of the objects for the sub modules
*/
class engine_api {
public:

	engine_api();
	~engine_api();

	//basic functions

	//this function draws and updates the engine
	void draw();

	//creates a window and the objects that will interact with it
	GLFWwindow* init(int width, int height, std::string title = "engine test");

	//checks to see if the windiow is open
	bool is_window_open() { return !glfwWindowShouldClose(window); }

	//getters

	Camera* get_camera() { return camera; }
	keyboard_manger* get_keyboard() { return keys; }
	timing* get_timing() { return Time; }
	text_engine* get_text_render() { return text_render; }
	skymap* get_skybox() { return sky; }
	engine_obj* get_all_engine_componets() { return engine_data; }
	engine* get_engine() { return Engine; }
	GUI* get_engine_gui() { return gui; }
	rendering::object_manger* get_OBJM() { return OBJM; }
	rendering::model_animation::animation_manager* get_ANIM() { return ANIM; }
	audio_syst::audio_manger* get_AM() { return AM; }

	

	//window callback setters

	void set_key_callback(GLFWkeyfun callback);
	void set_unicode_callback(GLFWcharfun callback);
	void set_mouse_button_callback(GLFWmousebuttonfun callback);
	void set_cursor_pos_callback(GLFWcursorposfun callback);
	void set_enter_window_callback(GLFWcursorenterfun callback);
	void set_scroll_callback(GLFWscrollfun callback);
	void set_frame_buffer_callback(GLFWframebuffersizefun callback);

private:

	//core functions
	void update();

	//helper functions

	//init functions
	void init_objects();
	void update_objects_from_engine();

	void start_networking();

	unsigned int SCR_WIDTH = 960;
	unsigned int SCR_HEIGHT = 720;
	std::string win_title;

	glm::mat4 view;
	glm::mat4 projection;
	//window inforamtion

	GLFWwindow* window;

	GLFWkeyfun key_callback;
	GLFWcharfun unicode_callback;
	GLFWmousebuttonfun mouse_callback;
	GLFWcursorposfun cursor_pos_callback;
	GLFWcursorenterfun enter_window_callback;
	GLFWscrollfun scroll_callback;
	GLFWframebuffersizefun frame_buffer_callback;

	void set_saved_callbacks();

	//subsystem objects
	text_engine* text_render;
	keyboard_manger* keys;
	engine* Engine;
	engine_obj* engine_data;
	timing* Time;
	skymap* sky;
	GUI* gui;
	Camera* camera;
	rendering::object_manger* OBJM;
	rendering::model_animation::animation_manager* ANIM;
	audio_syst::audio_manger *AM;
};