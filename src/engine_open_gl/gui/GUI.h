#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

#include "../core/camera.h"
#include "../rendering/shader.h"
#include "../misc/time.h"
#include "../misc/text_rendering.h"
#include "../rendering/object_manger.h"

#include "../lighting/lighting_manager.h"

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

class GUI{
public:
	GUI();
	~GUI();

	void draw();

	void init();

	void set_projection(glm::mat4 i) { projection = i; }
	void set_cam(glm::mat4 i) { view = i; }
	void set_time(timing* i) { Time = i; }

	void set_text_engine(text_engine* txt) { text_render = txt; }
	void set_online(bool i) { online = i; }

	void set_OBJM(rendering::object_manger* i) { OBJM = i; }
	void set_LM(light_mgr* lm) { LM = lm; }
	void set_draw_debug_info(bool i) { draw_debug_info = i; }
	void toggle_draw_debug_info() { draw_debug_info = !draw_debug_info; }

	void set_cam(Camera* c) { cam = c; }

	void send_message();

private:

	void spawn_object();
	void update_values();

	void draw_rendering_module();
	void draw_rendering_bottom_module();
	void draw_server_window();

	bool draw_server_windows;
	bool chat;
	bool command_history;
	bool server_info;
	bool commands;
	std::vector<std::string>* recived_chat_messages;
	std::string chat_input;
	int buffer_length = 100;
	char buffer[100] = { 0 };
	bool clear_message; 

	void draw_model_window();
	bool draw_model_windows;
	bool spawn_item;
	bool edit_cell;
	bool show_item_stats;
	bool show_animation_stats;
	bool edit_routine;
	bool edit_rendering;
	std::vector< rendering::item*>* item_data;
	float* item_amounts;
	int routines_edit_index;
	int show_actors_that_follow_routine;
	void debug_info();
	//debug_info vars
	int tab;
	bool debug_info_draw;
	//ImVec4 my_color;
	float* my_color;
	float* my_values;

	float* overal;
	float* effect;
	float* effects_3D;

	float spawn_x;
	float spawn_y;
	float spawn_z;

	float spawn_rot_x;
	float spawn_rot_y;
	float spawn_rot_z;

	float angle;

	bool is_actor;
	bool select_routine;
	bool spawned;
	rendering::item_info* fresh_item;
	int type;
	bool clear_on_spawn;

	std::vector<float> last_frames;
	int number_of_values;
	float passed_time;
	float record_check_point;

	bool draw_debug_info;

	glm::mat4 view;
	glm::mat4 projection;
	glm::vec3 cam_pos;

	timing* Time;
	float* deltatime;

	bool show_demo_window;
	bool show_another_window;
	ImVec4 clear_color;

	bool online;
	bool server;
	text_engine* text_render;
	rendering::object_manger* OBJM;
	unsigned int VBO, VAO;
	rendering::Shader* gui_window;
	Camera* cam;

	int x_start_off;
	int x_start_off_t;
	int z_start_off;
	int x_end_off;
	int z_end_off;

	bool x_start;
	bool z_start;
	bool x_end;
	bool z_end;

	int dir_selection;
	bool dir_changed;

	void draw_frustum_win();
	bool frustum_win;
	int veiw_disance;
	int veiw_width;

	bool show_computer;

	void draw_lighting_window();
	bool draw_lighting = false;
	light_mgr* LM;
	bool light_scene = false;
	bool create_light = false;
	bool ligh_info = true;
	int light_c_sub = 0;
};

