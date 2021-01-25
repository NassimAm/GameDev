#ifndef MAINRENDERER_H_INCLUDED
#define MAINRENDERER_H_INCLUDED

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <map>

#include "../Player/Camera.h"
#include "../shaders/Shader.h"
#include "../shaders/TerrainShader.h"
#include "../model/Texturedmodel.h"
#include "../entity/Entity.h"
#include "EntityRenderer.h"
#include "../terrain/Terrain.h"
#include "TerrainRenderer.h"
#include "../water/WaterPlane.h"
#include "../water/WaterShader.h"
#include "../water/WaterRenderer.h"
#include "../water/WaterFrameBuffers.h"
#include "../modelobj/Model.h"
#include "../modelobj/ModelLoader.h"


class MainRenderer
{
    public:
        MainRenderer(Loader loader,Shader shader,Shader modelshader,TerrainShader terrainshader,WaterShader watershader,WaterFrameBuffers fbos,float SCR_WIDTH,float SCR_HEIGHT);
        void render(DirLight sun,Camera camera,glm::vec4 plane,float deltatime);
        void processEntity(Entity entity);
        void processTransparentEntity(TransparentEntity transparententity);
        void processTerrain(Terrain terrain);
        void processWater(WaterPlane water);
        void processModel(Model model);
        void cleanUp();
        void prepare();
    private:
        const float FOV = 70.0f;
        const float NEAR_PLANE = 0.1f;
        const float FAR_PLANE = 1000.0f;

        const float WAVE_SPEED = 0.02f;
        float moveFactor = 0;

        Shader shader;
        Shader modelshader;
        TerrainShader terrainshader;
        WaterShader watershader;
        EntityRenderer renderer;
        TerrainRenderer terrainrenderer;
        WaterRenderer waterrenderer;
        ModelLoader modelloader;

        std::vector<TexturedModel> textures;
        std::vector<Entity> entities;
        std::vector<TransparentEntity> transparententities;
        std::vector<Terrain> terrains;
        std::vector<WaterPlane> waters;
        std::vector<Model> models;

};

#endif // MAINRENDERER_H_INCLUDED
