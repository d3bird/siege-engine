#include "GUI.h"

GUI::GUI() {
    Time = NULL;
    deltatime = NULL;
    gui_window = NULL;

    online = false;
    server = false;

    show_demo_window = true;
    show_another_window = false;
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    tab = 0;
    debug_info_draw = true;
    //my_color = ImVec4(1, 1, 0, 1);

    my_color = new float[4];
    my_color[0] = 0;
    my_color[1] = 0;
    my_color[2] = 0;
    my_color[3] = 0;


    overal = new float(0.5f);
    effect = new float(0.5f);
    effects_3D = new float(0.5f);

    number_of_values = 10;
    my_values = new float[number_of_values];
    for (int i = 0; i < number_of_values; i++) {
        //my_values[i] = 0;
        last_frames.push_back(0);
    }
    passed_time = 0;
    record_check_point = 1;
    draw_debug_info = false;
    draw_server_windows = false;
    draw_model_windows = false;
    show_item_stats = false;
    edit_cell = false;
    spawn_item = false;
    show_animation_stats = false;
    edit_routine = false;
    edit_rendering = false;
    OBJM = NULL;
    item_data = NULL;
    frustum_win = false;
    routines_edit_index = -1;
    show_actors_that_follow_routine = -1;
    item_amounts = NULL;

    clear_on_spawn = true;

    spawn_x = 0;
    spawn_y = 0;
    spawn_z = 0;

    spawn_rot_x = 0;
    spawn_rot_y = 1;
    spawn_rot_z = 0;

    angle = 0;
    spawned = false;
    is_actor = false;
    type = 0;
    select_routine = false;

    recived_chat_messages = NULL;
    chat = false;
    commands = false;
    command_history = false;
    server_info = false;
    buffer_length = 100;
    clear_message = false;

    dir_changed = false;
    dir_selection = 0;
    dir_changed = true;
    veiw_disance = -1;
    veiw_width = -1;


    LM = NULL;
}

GUI::~GUI() {
    delete[] my_color;
    delete overal;
    delete effect;
    delete effects_3D;
}


void GUI::draw() {
    update_values();
    debug_info();
}



void GUI::update_values() {
    if (passed_time > record_check_point) {
        last_frames.insert(last_frames.begin(), ImGui::GetIO().Framerate);
        passed_time = 0;
        for (; last_frames.size() > number_of_values + 1;) {
            last_frames.pop_back();
        }
    }
    else {
        passed_time += (*deltatime);
    }

}

// Edit a color (stored as ~4 floats)
//  ImGui::ColorEdit4("Color", my_color);

void GUI::draw_server_window() {

    static float w = 200.0f;
    static float h = 300.0f;

    ImGui::Begin("server settings", &draw_server_windows);

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    ImGui::BeginChild("child1", ImVec2(w, h), true);
    if (ImGui::Button("show chat")) {
        chat = true;
        commands = false;
        command_history = false;
        server_info = false;
    }
    if (ImGui::Button("send command")) {
        commands = true;
        chat = false;
        command_history = false;
        server_info = false;
    }
    if (ImGui::Button("command history")) {
        command_history = true;
        chat = false;
        commands = false;
        server_info = false;
    }
    if (ImGui::Button("server_info")) {
        server_info = true;
        chat = false;
        commands = false;
        command_history = false;
    }
    ImGui::EndChild();
    ImGui::SameLine();
    ImGui::InvisibleButton("vsplitter", ImVec2(8.0f, h));
    if (ImGui::IsItemActive())
        w += ImGui::GetIO().MouseDelta.x;
    ImGui::SameLine();
    ImGui::BeginChild("child2", ImVec2(0, h), true);
    
    ImGui::EndChild();
    ImGui::InvisibleButton("hsplitter", ImVec2(-1, 8.0f));
    if (ImGui::IsItemActive())
        h += ImGui::GetIO().MouseDelta.y;
    ImGui::BeginChild("child3", ImVec2(0, 0), true);
    ImGui::EndChild();
    ImGui::PopStyleVar();

    ImGui::End();

}

void GUI::send_message() {
  
}

void GUI::draw_model_window() {


    static float width = 200.0f;
    static float height = 300.0f;

    ImGui::Begin("model settings", &draw_model_windows);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    ImGui::BeginChild("option_selection", ImVec2(width, height), true);
    if (ImGui::Button("spawn item")) {
        show_item_stats = false;
        edit_cell = false;
        spawn_item = true;
        show_animation_stats = false;
        edit_routine = false;
        edit_rendering = false;
    }
    if (ImGui::Button("edit cell")) {
        spawn_item = false;
        show_item_stats = false;
        edit_cell = true;
        show_animation_stats = false;
        edit_routine = false;
        edit_rendering = false;
    }
  /*  if (ImGui::Button("edit animation routine")) {
        spawn_item = false;
        edit_cell = false;
        show_item_stats = false;
        show_animation_stats = false;
        edit_routine = true;
        edit_rendering = false;
    }*/
    if (ImGui::Button("show item stats")) {
        spawn_item = false;
        edit_cell = false;
        show_item_stats = true;
        show_animation_stats = false;
        edit_routine = false;
        edit_rendering = false;
    }
  /*  if (ImGui::Button("show animation stats")) {
        spawn_item = false;
        edit_cell = false;
        show_item_stats = false;
        show_animation_stats = true;
        edit_routine = false;
        edit_rendering = false;
    }*/
    if (ImGui::Button("set rendering data")) {
        spawn_item = false;
        edit_cell = false;
        show_item_stats = false;
        show_animation_stats = false;
        edit_routine = false;
        edit_rendering = true;
    }
    ImGui::EndChild();
    ImGui::SameLine();
    ImGui::InvisibleButton("vsplitter", ImVec2(8.0f, height));
    if (ImGui::IsItemActive())
        width += ImGui::GetIO().MouseDelta.x;
    ImGui::SameLine();
    ImGui::BeginChild("option options", ImVec2(0, height), true);
    if (spawn_item) {
        std::string temp = "spawn item: ";
        temp += "need to add name";
        ImGui::Text(temp.c_str());
        ImGui::Text("item info: ");
        ImGui::InputFloat("x loc", &spawn_x);
        ImGui::InputFloat("y loc", &spawn_y);
        ImGui::InputFloat("z loc", &spawn_z);
        if (ImGui::Button("set loc to cammera possition")) {
            glm::vec3 temp_loc = (*cam->get_pos());
            spawn_x = temp_loc.x;
            spawn_y = temp_loc.y;
            spawn_z = temp_loc.z;
        }
        ImGui::Text("(each cube is 2.0f appart. To snap to grid make cords divisible by 2");
        ImGui::NewLine();
        ImGui::SliderFloat("x rot", &spawn_rot_x, 0.0f, 1.0f);
        ImGui::SliderFloat("y rot", &spawn_rot_y, 0.0f, 1.0f);
        ImGui::SliderFloat("z rot", &spawn_rot_z, 0.0f, 1.0f);
        ImGui::Text("how much to rotate around each object");
        ImGui::NewLine();
        ImGui::InputFloat("angle", &angle);
        ImGui::NewLine();
        if (!is_actor) {
            if (ImGui::Button("turn into actor:")) {
                is_actor = true;
            }
        }
        else {
            if (ImGui::Button("turn into object:")) {
                is_actor = false;
            }
        }
      
        if (ImGui::Button("spawn object")) {
            spawn_object();
        }
    }
    else if (edit_cell) {
        ImGui::Text("edit cell:");
    }
    else if (edit_routine) {
        ImGui::Text("edit routine:");
     
    }
    else if (show_item_stats) {
        ImGui::Text("show item stats:");
        if (OBJM == NULL) {
            ImGui::Text("can not show info, OBJM is NULL");
        }
        else {
            if (item_data == NULL) {
                item_data = OBJM->get_all_item_info();
                ImGui::Text("item_info was null");
            }
            else {
                ImGui::BeginChild("Scrolling 1");
                for (int n = 0; n < item_data[0].size(); n++) {
                    std::string temp = "item_name ";
                    if (item_data[0][n]->item_name != NULL) {
                        temp += *item_data[0][n]->item_name;
                    }
                    ImGui::Text(temp.c_str());

                    temp = "max amount: ";
                    temp += std::to_string(item_data[0][n]->buffer_size);
                    ImGui::Text(temp.c_str());

                    temp = "currently spawned: ";
                    temp += std::to_string(item_data[0][n]->amount);

                    ImGui::Text(temp.c_str());
                    if (item_data[0][n]->draw) {
                        ImGui::Text("drawling: true");
                    }
                    else {
                        ImGui::Text("drawling: false");
                    }
                    ImGui::NewLine();
                }
                ImGui::EndChild();
            }
        }
    }
    else if (show_animation_stats) {
        
    }
    else if (edit_rendering) {
        draw_rendering_module();
    }
    ImGui::EndChild();
    ImGui::InvisibleButton("hsplitter", ImVec2(-1, 8.0f));
    if (ImGui::IsItemActive())
        height += ImGui::GetIO().MouseDelta.y;
    ImGui::BeginChild("child3", ImVec2(0, 0), true);
    if ((show_animation_stats || edit_routine)) {
        if (show_animation_stats) {
            ImGui::Text("showing routine stats:");
           
        }
        else if (edit_routine) {
            ImGui::Text("pick a routine to edit");
           
        }
    }
    else if (spawn_item) {
        if (item_data == NULL) {
            item_data = OBJM->get_all_item_info();
        }
        else {
            std::string temp = "unkown";
            if (is_actor && select_routine) {
                

            }
            else {
                ImGui::Text("select an item to spawn");
                ImGui::BeginChild("item_selection_list");
                for (int n = 0; n < item_data[0].size(); n++) {
                    std::string temp = "item_name: ";
                    if (item_data[0][n]->item_name != NULL) {
                        temp += *item_data[0][n]->item_name;
                    }
                    // ImGui::Text(temp.c_str());

                    if (ImGui::CollapsingHeader(temp.c_str())) {
                        temp = "max amount: ";
                        temp += std::to_string(item_data[0][n]->buffer_size);
                        ImGui::Text(temp.c_str());

                        temp = "currently spawned: ";
                        temp += std::to_string(item_data[0][n]->amount);

                        ImGui::Text(temp.c_str());
                        if (item_data[0][n]->draw) {
                            ImGui::Text("drawling: true");
                        }
                        else {
                            ImGui::Text("drawling: false");
                        }

                        if (ImGui::Button("select this item to spawn")) {
                            type = item_data[0][n]->type;
                        }
                    }
                }
                ImGui::EndChild();
            }
        }

    }
    else if (show_item_stats) {
        //static float TestData[6] = { 0.f,4.f,3.f,2.f,0.f,4.f };
        if (item_amounts == NULL) {
            if (item_data == NULL) {
                item_data = OBJM->get_all_item_info();
            }
            else {
                item_amounts = new float[item_data[0].size()];
                for (int i = 0; i < item_data[0].size(); i++) {
                    item_amounts[i] = float(item_data[0][i]->amount);
                }
                ImGui::PlotHistogram("", item_amounts, (int) item_data[0].size(), 0, "amount of each object", 0, 200, ImVec2(400, 140));
            }
        }
        else {
            for (int i = 0; i < item_data[0].size(); i++) {
                item_amounts[i] = float(item_data[0][i]->amount);
            }
            ImGui::PlotHistogram("", item_amounts, (int)item_data[0].size(), 0, "amount of each object", 0, 200, ImVec2(400, 140));
        }
        ImGui::SameLine();
        ImGui::BeginChild("plot legend");
        std::string temp = "%04d: ";
        for (int n = 0; n < item_data[0].size(); n++) {
            if (item_data[0][n]->item_name != NULL) {
                temp = "%04d: ";
                temp += *(item_data[0][n]->item_name);
                ImGui::Text(temp.c_str(), n);
            }
        }
        ImGui::EndChild();
    }
    else if (edit_rendering) {
        draw_rendering_bottom_module();
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();

    ImGui::End();
}

void GUI::debug_info() {
    ImGui::Begin("Debug Information", &debug_info_draw, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("settings/information"))
        {
            if (ImGui::MenuItem("frame rate", "")) { tab = 0; }
            if (ImGui::MenuItem("audio settings", "")) { tab = 1; }
            if (ImGui::MenuItem("model information", "")) { tab = 2; }
            if (ImGui::MenuItem("server information", "")) { tab = 3; }
            if (ImGui::MenuItem("frustum culling", "")) { tab = 4; }
            if (ImGui::MenuItem("lighting settings", "")) { draw_lighting = true; }
            if (ImGui::MenuItem("close", "")) { debug_info_draw = false; }
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }


    switch (tab) {
    case 1:
        ImGui::Text("over all");
        ImGui::SliderFloat("", overal, 0.0f, 1.0f);
        ImGui::Text("sound effects:");
        ImGui::SliderFloat("", effect, 0.0f, 1.0f);
        ImGui::Text("3D sound effects");
        ImGui::SliderFloat("", effects_3D, 0.0f, 1.0f);
        ImGui::Text("3D sound min range:");
        ImGui::Text("3D sound max range:");

        ImGui::TextColored(ImVec4(1, 1, 0, 1), "current sounds in engine");

        ImGui::BeginChild("Scrolling 1");
        for (int n = 0; n < 20; n++)
            ImGui::Text("%04d: Some text", n);
        ImGui::EndChild();
        break;
    case 2:
        if (draw_model_windows) {
            draw_model_windows = false;
        }
        else {
            draw_model_windows = true;
        }
        tab = 0;
        break;
    case 3:
        if (draw_server_windows) {
            draw_server_windows = false;
        }
        else {
            draw_server_windows = true;
        }
        tab = 0;
        break;
    case 4:
        frustum_win = true;
            break;
    case 0:
    default:
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        my_values = &last_frames[0];
        ImGui::PlotLines("Frame rate", my_values, number_of_values);
        ImGui::InputFloat("cammera speed", &(cam->MovementSpeed));
        break;
    }
    
    //if (ImGui::Button("send keyboard inputs to gui")) {
    //    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //}

    if (draw_server_windows) {
        draw_server_window();
    }
    if (draw_model_windows) {
        draw_model_window();
    }
    if (frustum_win) {
        draw_frustum_win();
    }

    if (draw_lighting) {
        draw_lighting_window();
    }

    // Display contents in a scrolling region
   /* ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
    ImGui::BeginChild("Scrolling");
    for (int n = 0; n < 50; n++)
        ImGui::Text("%04d: Some text", n);
    ImGui::EndChild();*/
    ImGui::End();

}

void GUI::draw_frustum_win() {
    ImGui::Begin("frustum culling information", &frustum_win);
    ImGui::Text("frustum culling information");
    if (OBJM != NULL) {
        if (veiw_disance == -1) {
         //   veiw_disance = OBJM->get_veiw_distance();
        }
        if (veiw_width == -1) {
           // veiw_width = OBJM->get_veiw_width();
        }
        ImGui::Text("edit veiw distance");
        if (ImGui::InputInt("distance:", &veiw_disance)) {
            if (veiw_disance < 1) {
                veiw_disance = 1;
            }
          //  OBJM->set_veiw_distance(veiw_disance);
        }
        ImGui::Text("edit veiw width");
        if (ImGui::InputInt("width:", &veiw_width)) {
           if (veiw_width < 1) {
                veiw_width = 1;
            }
          //  OBJM->set_veiw_width(veiw_width);
        }
    }
    else {
        ImGui::Text("OBJM is null");
    }
    ImGui::End();
}

void GUI::draw_rendering_module() {

    std::string temp = "Currently rendering";
    ImGui::Text(temp.c_str());
    temp = "veiw distance";
    ImGui::Text(temp.c_str());
    temp = "the player is looking to the ";
    ImGui::Text(temp.c_str());
    temp = "currently editing ";
    std::string n;
    switch (dir_selection)
    {
    case 0:
        n = "north";
        temp = temp + n;
        break;
    case 1:
        n = "east";
        temp = temp + n;
        break;
    case 2:
        n = "west";
        temp = temp + n;
        break;
    case 3:
        n = "south";
        temp = temp + n;
        break;
    }
    ImGui::Text(temp.c_str());
    if (ImGui::Checkbox("set x_start to player", &x_start)) {
        x_start = !x_start;
    }
    if (ImGui::Checkbox("set z_start to player", &x_start)) {
        x_start = !x_start;
    }
    if (ImGui::Checkbox("set x_end to player", &x_start)) {
        x_start = !x_start;
    }
    if (ImGui::Checkbox("set z_end to player", &x_start)) {
        x_start = !x_start;
    }
    ImGui::InputInt("x_start_off", &x_start_off);
    ImGui::InputInt("z_start_off", &z_start_off);
    ImGui::InputInt("x_end_off", &x_end_off);
    ImGui::InputInt("z_end_off", &z_end_off);

}

void GUI::draw_rendering_bottom_module() {
    ImGui::Text("select direction to edit");
    int new_dir_selection = dir_selection;
    if (ImGui::Button("north")) {
        new_dir_selection = 0;
    }
    if (ImGui::Button("east")) {
        new_dir_selection = 1;
    }
    if (ImGui::Button("west")) {
        new_dir_selection = 2;
    }
    if (ImGui::Button("south")) {
        new_dir_selection = 3;
    }
    if (new_dir_selection != dir_selection) {
        dir_selection = new_dir_selection;
        dir_changed = true;
    }

  
    

}

void GUI::spawn_object() {

    glm::vec3 loc(spawn_x, spawn_y, spawn_z);
    glm::vec3 rot(spawn_rot_x, spawn_rot_y, spawn_rot_z);

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, loc);
    trans = glm::rotate(trans, glm::radians(angle), rot);

    if (!spawned) {
        fresh_item = OBJM->spawn_item(type, -1, -1, -1, &trans);
    }

    fresh_item->x_rot = rot.x;
    fresh_item->y_rot = rot.y;
    fresh_item->z_rot = rot.z;
    fresh_item->angle = angle;
    fresh_item->x = (int) loc.x;
    fresh_item->y = (int) loc.y;
    fresh_item->z = (int) loc.z;

    if (!spawned) {
        spawned = true;
    }
    else {
        item_data[0][fresh_item->item_id]->modelMatrices[fresh_item->buffer_loc] = trans;
        item_data[0][fresh_item->item_id]->updatemats = true;
    }

    //clearn the options
    if (clear_on_spawn) {
        spawn_x = 0;
        spawn_y = 0;
        spawn_z = 0;

        spawn_rot_x = 0;
        spawn_rot_y = 1;
        spawn_rot_z = 0;

        angle = 0;
        is_actor = false;
        type = 0;
        select_routine = false;
        spawned = false;

    }
}

void GUI::init() {
	
	if (Time != NULL) {
		deltatime = Time->get_time_change();
	}
	else {
		std::cout << "there was a problem getting time in the GUI" << std::endl;
	}
}


void GUI::draw_lighting_window() {

    static float w = 200.0f;
    static float h = 300.0f;

    ImGui::Begin("lighting settings", &draw_server_windows);

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    ImGui::BeginChild("child1", ImVec2(w, h), true);

    if (ImGui::Button("light scence")) {
        light_scene = true;
        create_light = false;
        ligh_info = false;
    }
    if (ImGui::Button("create light")) {
        light_scene = false;
        create_light = true;
        ligh_info = false;
    }
    if (ImGui::Button("lighting stats")) {
        light_scene = false;
        create_light = false;
        ligh_info = true;
    }

    ImGui::EndChild();
    ImGui::SameLine();
    ImGui::InvisibleButton("vsplitter", ImVec2(8.0f, h));
    if (ImGui::IsItemActive())
        w += ImGui::GetIO().MouseDelta.x;
    ImGui::SameLine();
    ImGui::BeginChild("child2", ImVec2(0, h), true);

    if (LM != NULL) {
        if (light_scene) {
            ImGui::Text("lighing scence option");
        }
        else if (create_light) {
            static float pos[] = { 0,0,0 };
            static float col[] = { 0,0,0 };

            switch (light_c_sub)
            {
            case 1:
                ImGui::Text("creating a light");
                ImGui::Text("");
                ImGui::InputFloat3("pos", pos);
                ImGui::Text("");
                ImGui::ColorPicker3("color", col);
                ImGui::Text("");

                if (ImGui::Button("back")) {
                    light_c_sub = 0;
                }
                ImGui::SameLine();
                if (ImGui::Button("create")) {
                    light_c_sub = 0;

                }
                break;
            case 2:
                ImGui::Text("loading a light");
                if (ImGui::Button("back")) {
                    light_c_sub = 0;
                }
                ImGui::SameLine();
                if (ImGui::Button("load")) {
                    light_c_sub = 0;
                }
                break;
            case 3:
                ImGui::Text("deleting a light");
                if (ImGui::Button("back")) {
                    light_c_sub = 0;
                }
                ImGui::SameLine();
                if (ImGui::Button("delete")) {
                    light_c_sub = 0;
                }
                break;
            default:
                ImGui::Text("individal light options");

                if (ImGui::Button("create new light")) {
                    light_c_sub = 1;
                }
                if (ImGui::Button("load a light")) {
                    light_c_sub = 2;
                }
                if (ImGui::Button("delete a light")) {
                    light_c_sub = 3;
                }
                break;
            }
        }
        else {
            ImGui::Text("lighing manager info");
            ImGui::Text("");

            std::string temp = "current scence: ";
            temp += std::to_string(LM->get_current_scene()->index);
            ImGui::Text(temp.c_str());

            temp = "total lights: ";
            temp += std::to_string(LM->get_current_scene()->current_lights);
            ImGui::Text(temp.c_str());

            temp = "max lights: ";
            temp += std::to_string(LM->get_current_scene()->max_lights);
            ImGui::Text(temp.c_str());

            ImGui::Text("");
            temp = "total scences: ";
            temp += std::to_string(LM->get_scene_amount());
            ImGui::Text(temp.c_str());

            ImGui::Text("");

            if (ImGui::Button("trigger a lighting update")) {
                LM->set_trigger_update(true);
            }
        }
    }
    else {
        ImGui::Text("lighing manager is NULL");
    }
    ImGui::EndChild();
    ImGui::InvisibleButton("hsplitter", ImVec2(-1, 8.0f));
    if (ImGui::IsItemActive())
        h += ImGui::GetIO().MouseDelta.y;
    ImGui::BeginChild("child3", ImVec2(0, 0), true);

    ImGui::Text("there is on info here yet");

    ImGui::EndChild();
    ImGui::PopStyleVar();

    ImGui::End();

}