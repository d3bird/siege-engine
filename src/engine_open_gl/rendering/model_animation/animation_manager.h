#pragma once

#include "animator.h"
#include "model_animation.h"
namespace rendering {

	namespace model_animation {

		class animation_manager
		{
		public:
			animation_manager();
			~animation_manager();

			void update(float deltaTime);
			void draw();

			bool need_update() { return need_to_update; }

			rendering::Shader* get_shader() { return shader; }
		private:
			bool need_to_update;
			rendering::Shader* shader;
			Model_bone* ourModel;
			Animation* danceAnimation;
			Animator* animator;
		};
	}
}