#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <iostream>
#include <vector>

#include "../shaders/Shader.h"
#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>vertices,std::vector<unsigned int>indices,std::vector<Texture>textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    MeshSetup();
}

void Mesh::Draw(Shader shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse")
        {
            number = std::to_string(diffuseNr);
            diffuseNr++;
        }
        else if(name == "texture_specular")
        {
            number = std::to_string(specularNr);
            specularNr++;
        }
        shader.setInt(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
