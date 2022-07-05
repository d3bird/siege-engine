#include "animation_manager.h"

#include <misc/external_files.hpp>
#include <iostream>

namespace model_animation {
	animation_manager::animation_manager()
	{
		need_to_update = true;
		shader = new Shader("anim_model.vs", "anim_model.fs");
		external_paths paths;
		std::string import_str = (paths.get_external_objs_loc() + "vampire/dancing_vampire.dae");
		std::cout << std::endl;
		std::cout << "creating animation manager" << std::endl;
		std::cout << "importing example from: "<< import_str << std::endl;
		std::cout << "making the model" << std::endl;
		ourModel = new Model_bone(import_str);
		std::cout << "making the Animation" << std::endl;
		danceAnimation = new Animation(import_str, ourModel);
		std::cout << "making the Animator" << std::endl;
		animator = new Animator(danceAnimation);
		std::cout << "done" << std::endl;
		std::cout << std::endl;
	}

	animation_manager::~animation_manager()
	{
		delete shader;
		shader = NULL;
	}

	void animation_manager::update(float deltaTime) {
		animator->UpdateAnimation(deltaTime);



	}

	void animation_manager::draw() {
		shader->use();
		std::vector<glm::mat4> transforms = animator->GetFinalBoneMatrices();
		//std::cout << "transforms: " << transforms.size() << std::endl;;
		for (int i = 0; i < transforms.size(); ++i) {
			shader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
		}

		// render the loaded model
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, -4.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(4.5f, 4.5f, 4.5f));	// it's a bit too big for our scene, so scale it down
		shader->setMat4("model", model);
		ourModel->Draw(*shader);

	}

}
