#include "animation.h"

namespace rendering {


	namespace model_animation {

		Animation::Animation(const std::string& animationPath, Model_bone* model)
		{
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);
			assert(scene && scene->mRootNode);
			auto animation = scene->mAnimations[0];
			//change the level of prececion for the engine
			m_Duration = static_cast<float>(animation->mDuration);
			m_TicksPerSecond = static_cast<float>(animation->mTicksPerSecond);

			aiMatrix4x4 globalTransformation = scene->mRootNode->mTransformation;
			globalTransformation = globalTransformation.Inverse();
			ReadHeirarchyData(m_RootNode, scene->mRootNode);
			ReadMissingBones(animation, *model);
		}

		Animation::~Animation()
		{
		}

		Bone* Animation::FindBone(const std::string& name)
		{
			auto iter = std::find_if(m_Bones.begin(), m_Bones.end(),
				[&](const Bone& Bone)
				{
					return Bone.GetBoneName() == name;
				}
			);
			if (iter == m_Bones.end()) return nullptr;
			else return &(*iter);
		}


		float Animation::GetTicksPerSecond() {
			return m_TicksPerSecond;
		}

		float Animation::GetDuration() {
			return m_Duration;
		}

		const AssimpNodeData& Animation::GetRootNode() {
			return m_RootNode;
		}

		const std::map<std::string, BoneInfo>& Animation::GetBoneIDMap()
		{
			return m_BoneInfoMap;
		}

		void Animation::ReadMissingBones(const aiAnimation* animation, Model_bone& model)
		{
			int size = animation->mNumChannels;

			auto& boneInfoMap = model.GetBoneInfoMap();//getting m_BoneInfoMap from Model_bone class
			int& boneCount = model.GetBoneCount(); //getting the m_BoneCounter from Model_bone class

			//reading channels(bones engaged in an animation and their keyframes)
			for (int i = 0; i < size; i++)
			{
				auto channel = animation->mChannels[i];
				std::string boneName = channel->mNodeName.data;

				if (boneInfoMap.find(boneName) == boneInfoMap.end())
				{
					boneInfoMap[boneName].id = boneCount;
					boneCount++;
				}
				m_Bones.push_back(Bone(channel->mNodeName.data,
					boneInfoMap[channel->mNodeName.data].id, channel));
			}

			m_BoneInfoMap = boneInfoMap;
		}

		void Animation::ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src)
		{
			assert(src);

			dest.name = src->mName.data;
			dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
			dest.childrenCount = src->mNumChildren;

			for (unsigned int i = 0; i < src->mNumChildren; i++)
			{
				AssimpNodeData newData;
				ReadHeirarchyData(newData, src->mChildren[i]);
				dest.children.push_back(newData);
			}
		}
	}
}