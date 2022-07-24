#include "motion_manager_gui.h"

motion_manager_gui::motion_manager_gui(std::unordered_map< std::string, track_data*>* input):
	show_window(false), input_stream(input)
{
}

motion_manager_gui::~motion_manager_gui()
{
}


void motion_manager_gui::draw_gui_window() {
	ImGui::Begin("Motion manager GUI", &show_window);
	draw_gui_pannel();
	ImGui::End();
}

void motion_manager_gui::draw_gui_pannel() {
    ImGui::Text("This is all the currently active tracks");

    std::string temp;

    if (input_stream != NULL) {

        if (input_stream[0].size() == 0) {
            ImGui::Text("there are no tracks right now");
        }
        else {
            ImGui::BeginChild("full track list");
          /*  for (int i = 0; i < input_stream->size(); i++) {
                if (input_stream[0][i] != NULL) {
                    if (ImGui::CollapsingHeader(input_stream[0][i]->track_name.c_str())) {

                        temp = "location: " + input_stream[0][i]->base_location.to_string();
                        ImGui::Text(temp.c_str());

                        temp = "model number:: " + std::to_string(input_stream[0][i]->amount_models);
                        ImGui::Text(temp.c_str());

                        if (input_stream[0][i]->weapons != NULL) {
                            ImGui::Text("this track has weapons");
                        }

                        if (input_stream[0][i]->grnd_vehicle != NULL) {
                            ImGui::Text("this track is ground vehicle");
                        }

                        if (input_stream[0][i]->air_vehicle != NULL) {
                            ImGui::Text("this track is an air vehicle");
                        }
                    }
                    else {
                        std::cout << "NULL track in the track list" << std::endl;
                    }
                }
            }*/
            ImGui::EndChild();
        }
    }
    else {
        ImGui::Text("the track input stream is null");
    }


}

void motion_manager_gui::show() {
	show_window = true;
}

void motion_manager_gui::hide() {
	show_window = false;
}