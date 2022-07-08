#ifndef MESH_BONE_H
#define MESH_BONE_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../shader.h"

#include <string>
#include <vector>

#define MAX_BONE_INFLUENCE 4

namespace rendering {

    namespace model_animation {

        struct Vertex {
            // position
            glm::vec3 Position;
            // normal
            glm::vec3 Normal;
            // texCoords
            glm::vec2 TexCoords;
            // tangent
            glm::vec3 Tangent;
            // bitangent
            glm::vec3 Bitangent;
            //bone indexes which will influence this vertex
            int m_BoneIDs[MAX_BONE_INFLUENCE];
            //weights from each bone
            float m_Weights[MAX_BONE_INFLUENCE];
        };

        struct Texture {
            unsigned int id;
            std::string type;
            std::string path;
        };

        class Mesh_bone {
        public:
            // mesh Data
            std::vector<Vertex>       vertices;
            std::vector<unsigned int> indices;
            std::vector<Texture>      textures;
            unsigned int VAO;

            // constructor
            Mesh_bone(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

            // render the mesh
            void Draw(rendering::Shader& shader);

        private:
            // render data 
            unsigned int VBO, EBO;

            // initializes all the buffer objects/arrays
            void setupMesh();
        };

    }
}
#endif
