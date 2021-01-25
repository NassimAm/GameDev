#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shaders/TerrainShader.h"
#include "../model/Rawmodel.h"
#include "../texture/Terraintexture.h"
#include "../texture/TerraintexturePack.h"
#include "../terrain/Terrain.h"
#include "TerrainRenderer.h"

#include <iostream>
#include <vector>


TerrainRenderer::TerrainRenderer()
{
    //Constructor
}

TerrainRenderer::TerrainRenderer(TerrainShader terrainshader,glm::mat4 projection)
{
    this->terrainshader = terrainshader;
    terrainshader.use();
    terrainshader.setMat4("projection",1,GL_FALSE,projection);
    terrainshader.connectTextures();
    terrainshader.stop();
}

void TerrainRenderer::prepareTerrain(Terrain terrain)
{
    RawModel rawModel = terrain.getModel();
    glBindVertexArray(rawModel.getVaoID());
    BindTextures(terrain);
}

void TerrainRenderer::render(std::vector<Terrain> terrains)
{
    for(unsigned int i=0;i<terrains.size();i++)
    {
        prepareTerrain(terrains[i]);
        loadModelMatrix(terrains[i]);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES,terrains[i].getModel().getVertexCount(),GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
    }
}

void TerrainRenderer::BindTextures(Terrain terrain)
{
    TerrainTexturePack texturepack = terrain.getTexturePack();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texturepack.getBackgroundTexture().getID());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,texturepack.getrTexture().getID());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D,texturepack.getgTexture().getID());
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D,texturepack.getbTexture().getID());
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D,terrain.getBlendMap().getID());

}

void TerrainRenderer::loadModelMatrix(Terrain terrain)
{
    glm::mat4 modelmat = glm::mat4(1.0f);
    modelmat = glm::translate(modelmat,glm::vec3(terrain.getX(),0.0f,terrain.getZ()));
    terrainshader.setMat4("model",1,GL_FALSE,modelmat);
}
