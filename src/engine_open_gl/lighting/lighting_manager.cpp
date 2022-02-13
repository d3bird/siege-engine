#include "lighting_manager.h"

#include <iostream>

light_mgr::light_mgr(int max_lights_in_scene){
	factory = NULL;
    max_lights_scence = max_lights_in_scene;

    current_index = -1;
    current_scene = NULL;

    need_update = true;
}

light_mgr::~light_mgr(){

}

void light_mgr::update() {

}

int light_mgr::create_light_scene(int max_lights, bool set_as_current) {
    int output = -1;
    if (max_lights >= max_lights_scence) {
        std::cout << "max_lights was >= max_lights_scence, setting to engine max" << std::endl;
    }
    
    if (factory != NULL) {
        
        lighting_scene* temp= factory->create_light_scene(max_lights);
        if(temp != NULL){
            output = l_scenes.size();
            temp->index = output;
            l_scenes.push_back(temp);

            if (set_as_current) {
                set_current_scene(output);
                need_update = true;
            }
        }
    }

    return output;
}

void light_mgr::delete_light_scene(int index) {
    if (is_scene_index_valid(index)) {
        need_update = true;

    }
    else {
        std::cout << "can not delete_light_scene, index is invalid" << std::endl;
    }
}

void light_mgr::set_current_scene(int index) {
    if (is_scene_index_valid(index)) {
        need_update = true;
        current_scene = l_scenes[index];
    }
    else {
        std::cout << "can not delete_light_scene, index is invalid" << std::endl;
    }
}

void light_mgr::clear_current_scene() {
    need_update = true;

}

void light_mgr::add_def_light(glm::vec3 col, glm::vec3 pos, int scene) {

    if (scene == -1 && current_scene != NULL) {
        bool result = factory->create_light(pos, col, current_scene);
        if (!result) {
            std::cout << "failed to create light or add to scene" << std::endl;
        }
        else {
            need_update = true;
        }
    }
    else if(is_scene_index_valid(scene)) {
        bool result = factory->create_light(pos, col, l_scenes[scene]);
        if (!result) {
            std::cout << "failed to create light or add to scene" << std::endl;
        }
        else {
            need_update = true;
        }
    }
    else {
        std::cout << "failed to create light" << std::endl;
    }
}


inline bool light_mgr::is_scene_index_valid(int in) {
    return !l_scenes.empty() &&
        (in >= 0 && in < l_scenes.size()) &&
        (l_scenes[in] != NULL);
}

void light_mgr::init() {
    std::cout << std::endl;
    std::cout << "creating lighting manager" << std::endl;
    std::cout << "creating lighting modules" << std::endl;
	factory = new light_factory(max_lights_scence);

    std::cout << "creating starting lighting scene" << std::endl;

    create_light_scene(NR_LIGHTS, true);

    std::cout << "done" << std::endl;
    std::cout << std::endl;
}

void light_mgr::print_info() {
    std::cout << "printing infomation about the lighting manager" << std::endl;
    std::cout << "scences: " << l_scenes.size() << std::endl;

    if (current_scene != NULL) {
        std::cout << "Current scence" << std::endl;
        print_info(current_scene);
    }
    else {
        std::cout << "there is no current scene" << std::endl;
    }

}

void light_mgr::print_info(def_light* in) {
    if (in != NULL) {
        std::cout << "printing light information" << std::endl;
        std::cout << "pos: " << in->light_col->x << " " << in->light_col->y << " " << in->light_col->z << std::endl;
        std::cout << "col: " << in->light_loc->x << " " << in->light_loc->y << " " << in->light_loc->z << std::endl;
        std::cout << std::endl;
    }
}

void light_mgr::print_info(lighting_scene* in) {
    if (in != NULL) {
        std::cout << "printing light scene information" << std::endl;
        std::cout << "contains: " << in->current_lights << " out of " << in->max_lights << std::endl;
      
        std::cout << "light_pos size: " << in->light_pos.size() << std::endl;
        std::cout << "light_col size: " << in->light_col.size() << std::endl;

        std::cout << "active lights: " << in->active_lights.size() << std::endl;
        std::cout << "non active lights: " << in->non_active_lights.size() << std::endl;

        bool print_lights = true;

        if (print_lights) {
            std::cout << "active lights" << std::endl;
            for (int i = 0; i < in->active_lights.size(); i++) {
                print_info(in->active_lights[i]);
            }
            std::cout << "non active lights" << std::endl;
            for (int i = 0; i < in->non_active_lights.size(); i++) {
                print_info(in->non_active_lights[i]);
            }
        }

        std::cout << std::endl;
    }
}