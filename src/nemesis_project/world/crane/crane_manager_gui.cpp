#include "crane_manager_gui.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <gui/GUI.h>

#include <iostream>

crane_manager_gui::crane_manager_gui() {
	crane_mgr = NULL;
	showing_window = true;
}

crane_manager_gui::crane_manager_gui(crane_manager* acrane_mgr) {
	crane_mgr = acrane_mgr;
	showing_window = true;
}

crane_manager_gui::~crane_manager_gui() {

}

void crane_manager_gui::draw() {
	ImGui::Begin("crane informations", &showing_window, ImGuiWindowFlags_MenuBar);

	if (crane_mgr) {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("settings/information"))
            {
                if (ImGui::MenuItem("information", "")) { tab = 0; }
                if (ImGui::MenuItem("change crane", "")) { tab = 1; }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

		switch (tab)
		{

		default:
			ImGui::Text("nothing is defined for this menu option");
			break;
		}

	}
	else {
		ImGui::Text("the crane manager is null");
	}

	ImGui::End();
}