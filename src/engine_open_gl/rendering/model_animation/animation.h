#pragma once

#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include "bone.h"
#include <functional>
#include "animdata.hpp"
#include "model_animation.h"

namespace rendering {

	namespace model_animation {

		struct AssimpNodeData
		{
			glm::mat4 transformation;
			std::string name;
			int childrenCount;
			std::vector<AssimpNodeData> children;
		};

		class Animation
		{
		public:
			Animation() = delete;
			Animation(const std::string& animationPath, Model_bone* model);
			~Animation();

			Bone* FindBone(const std::string& name);

			float GetTicksPerSecond();
			float GetDuration();
			const AssimpNodeData& GetRootNode();
			const std::map<std::string, BoneInfo>& GetBoneIDMap();

		private:

			void ReadMissingBones(const aiAnimation* animation, Model_bone& model);
			void ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src);

			float m_Duration;
			float m_TicksPerSecond;
			std::vector<Bone> m_Bones;
			AssimpNodeData m_RootNode;
			std::map<std::string, BoneInfo> m_BoneInfoMap;
		};

	}
}