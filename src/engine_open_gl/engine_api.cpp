#include "engine_api.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

engine_api::engine_api() {


    //window varibles
    window = NULL;
    key_callback = NULL;
    unicode_callback = NULL;
    mouse_callback = NULL;
    cursor_pos_callback = NULL;
    enter_window_callback = NULL;
    scroll_callback = NULL;
    frame_buffer_callback = NULL;

    //subsystem objects
    text_render = NULL;
    keys = NULL;
    Engine = NULL;
    engine_data = NULL;
    Time = NULL;
    sky = NULL;
    gui = NULL;
    camera = NULL;
    OBJM = NULL;
    ANIM = NULL;
    AM = NULL;

    //the viewing vars
    view = glm::mat4(0.0f);
    projection = glm::mat4(0.0f);
}

engine_api::~engine_api() {
    glfwTerminate();
}

void engine_api::draw() {
    ImGui_ImplGlfwGL3_NewFrame();
    Time->update_time();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    view = camera->GetViewMatrix();

    glEnable(GL_CULL_FACE);
    Engine->set_cam(view);
    Engine->set_cam_pos((*camera->get_pos()));

    Engine->draw_deferred();
   // Engine->draw_only_animations();

    sky->set_cam(view);
    sky->set_projection(projection);
    sky->draw();

    Engine->update();

    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void engine_api::update() {
    Engine->update();
}

GLFWwindow* engine_api::init(int width, int height, std::string title) {
    //create the window information

    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    win_title = title;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_SAMPLES, 4);


#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, win_title.c_str(), NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }

    //setting the context and callbacks
    glfwMakeContextCurrent(window);
    set_saved_callbacks();

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //set opengl flags
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return NULL;
    }
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_BLEND);
    // glCullFace(GL_BACK);
     //glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    
    //create the rest of the objects
    init_objects();

    //grabs the core engine objects that where created
    update_objects_from_engine();

    //return the created window context
    return window;
}

void engine_api::init_objects() {

    camera = new Camera(new glm::vec3(-2, 6, -2), glm::vec3(0.0f, 1.0f, 0.0f), 90, 0);//looking at the whole Engine
    keys = new keyboard_manger();

    Time = new timing(false);

    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
    view = camera->GetViewMatrix();

    gui = new GUI();
    gui->set_time(Time);

    text_render = new text_engine();
    text_render->set_time(Time);
    text_render->set_projection(projection);
    text_render->set_cam(view);
    text_render->set_height_screen(SCR_HEIGHT);
    text_render->set_width_screen(SCR_WIDTH);
    text_render->init();

    sky = new skymap();
    sky->set_cam(view);
    sky->set_projection(projection);
    sky->init();

    ANIM = new rendering::model_animation::animation_manager();
         
    engine_data = new engine_obj;
    //engine_data->OBJM = OBJM;
    engine_data->ANIM = ANIM;
    //engine_data->ADM = ADM;
    engine_data->time = Time;
    engine_data->text_render = text_render;
    engine_data->cam = camera;

    Engine = new engine();
    Engine->set_time(Time);
    Engine->set_cam(view);
    Engine->set_projection(projection);
    Engine->set_online(false);
    Engine->set_height_screen(SCR_HEIGHT);
    Engine->set_width_screen(SCR_WIDTH);
    Engine->set_text_engine(text_render);
    Engine->init(gui, engine_data);
    Engine->set_camera_obj(camera);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();
    gui->set_cam(camera);
    gui->init();

    //make sure that thte engine has the call back since imgui till take it
    if (key_callback != NULL) {
        set_key_callback(key_callback);
    }

    if (mouse_callback != NULL) {
        set_mouse_button_callback(mouse_callback);
    }
    // set_scroll_callback(scroll_callback);
}

void engine_api::update_objects_from_engine() {

    if (engine_data != NULL) {
        OBJM = engine_data->OBJM;
        AM = engine_data->ADM;
    }
}


void engine_api::start_networking() {

   // network->init();
}

//windows callback setters
void engine_api::set_saved_callbacks() {
    set_key_callback(key_callback);
    set_unicode_callback(unicode_callback);
    set_mouse_button_callback(mouse_callback);
    set_cursor_pos_callback(cursor_pos_callback);
    set_enter_window_callback(enter_window_callback);
    set_scroll_callback(scroll_callback);
    set_frame_buffer_callback(frame_buffer_callback);
}

void engine_api::set_key_callback(GLFWkeyfun callback) {

    if (callback != NULL) {
       // std::cout << "saving the key_callback" << std::endl;
        key_callback = callback;
        if (window != NULL) {
       //     std::cout << "setting the key_callback" << std::endl;
            glfwSetKeyCallback(window, callback);
        }
       /* else {
            std::cout << "the window was null, could not set call back" << std::endl;
        }*/
    }
}

void engine_api::set_unicode_callback(GLFWcharfun callback) {
    if (callback != NULL) {
       // std::cout << "saving the unicode_callback" << std::endl;
        unicode_callback = callback;
        if (window != NULL) {
         //   std::cout << "setting the unicode_callback" << std::endl;
            glfwSetCharCallback(window, callback);
        }
       /* else {
            std::cout << "the window was null, could not set call back" << std::endl;
        }*/
    }
}

void engine_api::set_mouse_button_callback(GLFWmousebuttonfun callback) {
    if (callback != NULL) {
       // std::cout << "saving the mouse_button_callback" << std::endl;
        mouse_callback = callback;
        if (window != NULL) {
          //  std::cout << "setting the mouse_button_callback" << std::endl;
            glfwSetMouseButtonCallback(window, callback);
        }
        /*else {
            std::cout << "the window was null, could not set call back" << std::endl;
        }*/
    }
}

void engine_api::set_cursor_pos_callback(GLFWcursorposfun callback) {
    if (callback != NULL) {
      //  std::cout << "saving the cursor_pos_callback" << std::endl;
        cursor_pos_callback = callback;
        if (window != NULL) {
         //   std::cout << "setting the cursor_pos_callback" << std::endl;
            glfwSetCursorPosCallback(window, callback);
        }
       /* else {
            std::cout << "the window was null, could not set call back" << std::endl;
        }*/
    }
}

void engine_api::set_enter_window_callback(GLFWcursorenterfun callback) {
    if (callback != NULL) {
       // std::cout << "saving the enter_window_callback" << std::endl;
        enter_window_callback = callback;
        if (window != NULL) {
           // std::cout << "setting the enter_window_callback" << std::endl;
            glfwSetCursorEnterCallback(window, callback);
        }
        /*else {
            std::cout << "the window was null, could not set call back" << std::endl;
        }*/
    }
}

void engine_api::set_scroll_callback(GLFWscrollfun callback) {
    if (callback != NULL) {
      //  std::cout << "saving the scroll_callback" << std::endl;
        scroll_callback = callback;
        if (window != NULL) {
           // std::cout << "setting the scroll_callback" << std::endl;
            glfwSetScrollCallback(window, callback);
        }
        /*else {
            std::cout << "the window was null, could not set call back" << std::endl;
        }*/
    }
}

void engine_api::set_frame_buffer_callback(GLFWframebuffersizefun callback) {
    if (callback != NULL) {
      //  std::cout << "saving the frame_buffer_callback" << std::endl;
        frame_buffer_callback = callback;
        if (window != NULL) {
        //    std::cout << "setting the frame_buffer_callback" << std::endl;
            glfwSetFramebufferSizeCallback(window, callback);
        }
       /* else {
            std::cout << "the window was null, could not set call back" << std::endl;
        }*/
    }
}
