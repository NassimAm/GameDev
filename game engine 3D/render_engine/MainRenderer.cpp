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


#include "MainRenderer.h"

MainRenderer::MainRenderer(Loader loader,Shader shader,Shader modelshader,TerrainShader terrainshader,WaterShader watershader,WaterFrameBuffers fbos,float SCR_WIDTH,float SCR_HEIGHT)
{
    this->shader = shader;
    this->modelshader = modelshader;
    this->terrainshader = terrainshader;
    this->watershader = watershader;
    glm::mat4 projection = glm::perspective(glm::radians(FOV),SCR_WIDTH/SCR_HEIGHT,NEAR_PLANE,FAR_PLANE);
    renderer = EntityRenderer(shader,projection);
    terrainrenderer = TerrainRenderer(terrainshader,projection);
    waterrenderer = WaterRenderer(loader,watershader,projection,fbos);
    modelloader = ModelLoader(modelshader,projection);
}

void MainRenderer::render(DirLight sun,Camera camera,glm::vec4 plane,float deltatime)
{
    shader.use();
    shader.loadCamera(camera);
    shader.loadSun(sun);
    shader.loadClipPlane(plane);
    renderer.render(textures,entities,transparententities);
    shader.stop();

    modelshader.use();
    modelshader.loadCamera(camera);
    modelshader.loadSun(sun);
    modelshader.loadClipPlane(plane);
    modelloader.render(models);
    modelshader.stop();

    terrainshader.use();
    terrainshader.loadCamera(camera);
    terrainshader.loadSun(sun);
    terrainshader.loadClipPlane(plane);
    terrainrenderer.render(terrains);
    terrainshader.stop();

    watershader.use();
    watershader.loadCamera(camera);
    watershader.loadSun(sun);
    moveFactor+=WAVE_SPEED*deltatime;
    if(moveFactor>1.0f)
        moveFactor -= 1.0f;
    watershader.loadMoveFactor(moveFactor);
    watershader.setFloat("near",NEAR_PLANE);
    watershader.setFloat("far",FAR_PLANE);
    waterrenderer.render(waters);
    watershader.stop();

    entities.clear();
    transparententities.clear();
    models.clear();
    textures.clear();
    terrains.clear();
    waters.clear();
}

void MainRenderer::processEntity(Entity entity)
{
    entities.push_back(entity);
    TexturedModel model = entity.getModel();
    unsigned int pointer = 0;
    for(unsigned int i=0;i<textures.size();i++)
    {
        if(textures[i].getRawModel().getVaoID() == model.getRawModel().getVaoID())
            break;
        pointer++;
    }
    if(pointer == textures.size())
        textures.push_back(model);
}

void MainRenderer::processTransparentEntity(TransparentEntity transparententity)
{
    transparententities.push_back(transparententity);
    TexturedModel model = transparententity.getModel();
    unsigned int pointer = 0;
    for(unsigned int i=0;i<textures.size();i++)
    {
        if(textures[i].getRawModel().getVaoID() == model.getRawModel().getVaoID())
            break;
        pointer++;
    }
    if(pointer == textures.size())
        textures.push_back(model);
}

void MainRenderer::processTerrain(Terrain terrain)
{
    terrains.push_back(terrain);
}

void MainRenderer::processWater(WaterPlane water)
{
    waters.push_back(water);
}

void MainRenderer::processModel(Model model)
{
    models.push_back(model);
}

void MainRenderer::cleanUp()
{
    shader.Delete();
    modelshader.Delete();
    terrainshader.Delete();
    watershader.Delete();
}

void MainRenderer::prepare()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.6f, 0.6f, 1.0f, 1.0f);
}

