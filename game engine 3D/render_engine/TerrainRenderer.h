#ifndef TERRAINRENDERER_H_INCLUDED
#define TERRAINRENDERER_H_INCLUDED

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

#include <iostream>
#include <vector>

class TerrainRenderer
{
    public:
        TerrainRenderer();
        TerrainRenderer(TerrainShader terrainshader,glm::mat4 projection);
        void render(std::vector<Terrain> terrains);
    private:
        TerrainShader terrainshader;
        void prepareTerrain(Terrain terrain);
        void BindTextures(Terrain terrain);
        void loadModelMatrix(Terrain terrain);
};

#endif // TERRAINRENDERER_H_INCLUDED
