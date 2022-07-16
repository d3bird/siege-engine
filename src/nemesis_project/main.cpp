#include "scene.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void process_movement(GLFWwindow *window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void key_board_input(GLFWwindow* window, int key, int scancode, int action, int mods);

void additional_guis();

// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
unsigned int SCR_WIDTH = 960;
unsigned int SCR_HEIGHT = 720;
//960×720
// camera

Camera* camera;// (glm::vec3(7.9019, 29.3491, 18.9233), glm::vec3(0.0f, 1.0f, 0.0f), -89.2999, -71.7001);//looking at the whole Engine

bool draw_world_info;

float lastX = (float)SCR_WIDTH / 2.0f;
float lastY = (float)SCR_HEIGHT / 2.0f;

float current_mouse_x = lastX;
float current_mouse_y = lastY;

bool firstMouse = true;

engine* Engine = NULL;
timing* Time = NULL;
GUI* gui;
float* deltaTime = NULL;
keyboard_manger* keys;
bool typing;

text_engine* text_render;
bool take_input = true;;

bool freecam = false;

int main() {

    std::cout << "starting test program" << std::endl;
    std::cout << "makeing the api" << std::endl;

    engine_api* API = new engine_api();
    typing = false;
    std::cout << "setting the call backs" << std::endl;

   // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    API->set_frame_buffer_callback(framebuffer_size_callback);
   // glfwSetCursorPosCallback(window, mouse_callback);
    API->set_cursor_pos_callback(mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback);
   API->set_scroll_callback(scroll_callback);
   // glfwSetMouseButtonCallback(window, mouse_button_callback);
    API->set_mouse_button_callback(mouse_button_callback);
   // glfwSetKeyCallback(window, key_board_input);
    API->set_key_callback(key_board_input);

    GLFWwindow* window = API->init(SCR_WIDTH, SCR_HEIGHT, "this is a window");

    if (window == NULL) {
        std::cout << "something went wrong with the graphics engine" << std::endl;
    }

    std::cout << "" << std::endl;
    std::cout << "" << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "" << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "" << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "" << "OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "" << std::endl;

    //while (true);

    camera = API->get_camera();
    keys = API->get_keyboard();
    gui = API->get_engine_gui();
    text_render = API->get_text_render();
    Engine = API->get_engine();
    Time = API->get_timing();
    deltaTime = Time->get_time_change_static();

    glm::vec3 cam_start = glm::vec3(20, 10, -20);
    camera->set_pos(&cam_start);


    //load the test application scene
    scene testing;
    testing.init(API);
    API->additional_gui = &additional_guis;

    std::cout << "starting the main loop " << std::endl;

    while (API->is_window_open())
    {
        if (!typing) {
            process_movement(window);
        }
        API->draw();

        testing.update(*deltaTime);
    }


    delete API;
    return 0;
}

void process_movement(GLFWwindow* window) {

    if (!take_input) {
        //std::cout << "input for keyboard is turned off" << std::endl;
        return;
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, *deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, *deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, *deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, *deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera->ProcessKeyboard(UP, *deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera->ProcessKeyboard(DOWN, *deltaTime);


    
}

void key_board_input(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
        take_input = !take_input;
        if (take_input) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursorPos(window, 0.5, 0.5);
            lastY = 0.5;
            lastX = 0.5;

        }
    }

    if (!take_input) {
        //std::cout << "input for keyboard is turned off" << std::endl;
        //the backspace key was not linked correctly so I have to manually check for it
        if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS) {
            ImGui::GetIO().KeysDown[ImGui::GetIO().KeyMap[ImGuiKey_Backspace]] = true;
        }
        else {
            ImGui::GetIO().KeysDown[ImGui::GetIO().KeyMap[ImGuiKey_Backspace]] = false;
        }
        if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE) {
            gui->send_message();
        }

        return;
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
        if (typing) {
            text_render->send_meeage();
        }
        typing = !typing;
        std::cout << "enter was clicked " << typing << std::endl;
        text_render->set_typing(typing);
    }

    if (typing) {
        if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS) {
            char* tchar = new char(' ');
            text_render->add_char_to_message(tchar, true);
        }
        else {
            text_render->add_char_to_message(keys->key_board_input(key, action));
        }
        return;
    }

    //timimng changes
    if (key == GLFW_KEY_0 && action == GLFW_PRESS)
        Time->set_time_multipler(0);
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        Time->set_time_multipler(1);
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
        Time->set_time_multipler(2);
    if (key == GLFW_KEY_3 && action == GLFW_PRESS)
        Time->set_time_multipler(3);
    if (key == GLFW_KEY_4 && action == GLFW_PRESS)
        Time->set_time_multipler(4);
    if (key == GLFW_KEY_5 && action == GLFW_PRESS)
        Time->toggle_frame_rates();
    if (key == GLFW_KEY_6 && action == GLFW_RELEASE)
        Engine->play_sound_effect(0);
    if (key == GLFW_KEY_7 && action == GLFW_RELEASE)
        Engine->play_sound_effect(1);
    if (key == GLFW_KEY_8 && action == GLFW_RELEASE)
        Engine->play_sound_effect(2);
    if (key == GLFW_KEY_9 && action == GLFW_RELEASE)
        Engine->play_sound_effect(3);

    if (key == GLFW_KEY_O && action == GLFW_RELEASE)
        Engine->increase_background_music();
    if (key == GLFW_KEY_L && action == GLFW_RELEASE)
        Engine->decrease_background_music();

    if (key == GLFW_KEY_TAB && action == GLFW_RELEASE)
        gui->set_draw_debug_info(true);

}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    std::cout << "framebuffer_size_callback called" << std::endl;

    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
   // std::cout << "mouse_callback called" << std::endl;
    if (!take_input) {
        //std::cout << "input for keyboard is turned off" << std::endl;
        return;
    }

    if (firstMouse)
    {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
    }

    float xoffset = (float) xpos - lastX;
    float yoffset = lastY - (float)ypos; // reversed since y-coordinates go from bottom to top

    lastX = (float)xpos;
    lastY = (float)ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    std::cout << "scroll_callback called" << std::endl;
    if (Engine != NULL) {
       float zoom = camera->ProcessMouseScroll((float)yoffset);
       Engine->change_projection(glm::perspective(glm::radians(zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f));
    }
}

// glfw: whenever the mouse buttons are clicked, this callback is called
// ----------------------------------------------------------------------
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    std::cout << "mouse_button_callback called" << std::endl;

}

void additional_guis() {
    

}
