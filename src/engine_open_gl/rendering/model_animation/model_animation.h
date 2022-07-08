#ifndef MODEL_BONE_H
#define MODEL_BONE_H

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh_an.h"
#include "../shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "assimp_glm_helpers.hpp"
#include "animdata.hpp"

namespace rendering {

	namespace model_animation {
		class Model_bone
		{
		public:
			// model data 
			std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
			std::vector<Mesh_bone>    meshes;
			std::string directory;
			bool gammaCorrection;

			// constructor, expects a filepath to a 3D model.
			Model_bone(std::string const& path, bool gamma = false) : gammaCorrection(gamma)
			{
				loadModel(path);
			}

			// draws the model, and thus all its meshes
			void Draw(rendering::Shader& shader)
			{
				for (unsigned int i = 0; i < meshes.size(); i++)
					meshes[i].Draw(shader);
			}

			auto& GetBoneInfoMap() { return m_BoneInfoMap; }
			int& GetBoneCount() { return m_BoneCounter; }


		private:

			std::map<std::string, BoneInfo> m_BoneInfoMap;
			int m_BoneCounter = 0;

			// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
			void loadModel(std::string const& path);

			// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
			void processNode(aiNode* node, const aiScene* scene);

			void SetVertexBoneDataToDefault(Vertex& vertex);


			Mesh_bone processMesh(aiMesh* mesh, const aiScene* scene);

			void SetVertexBoneData(Vertex& vertex, int boneID, float weight);


			void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);


			unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

			// checks all material textures of a given type and loads the textures if they're not loaded yet.
			// the required info is returned as a Texture struct.
			std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
		};

	}
}
#endif
