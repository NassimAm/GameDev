#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"
#include "Player/Camera.h"
#include "light/Lighting.h"
#include "shaders/Shader.h"
#include "shaders/TerrainShader.h"
#include "model/Rawmodel.h"
#include "texture/Modeltexture.h"
#include "texture/Terraintexture.h"
#include "texture/TerraintexturePack.h"
#include "model/Texturedmodel.h"
#include "render_engine/Loader.h"
#include "entity/Entity.h"
#include "terrain/Terrain.h"
#include "render_engine/MainRenderer.h"
#include "gui/GuiTexture.h"
#include "gui/GuiShader.h"
#include "gui/GuiRenderer.h"
#include "water/WaterPlane.h"
#include "water/WaterShader.h"
#include "water/WaterFrameBuffers.h"
#include "modelobj/Model.h"
#include "Player/Player.h"

#include <iostream>
#include <string>
#include <vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const float SCR_WIDTH = 800;
const float SCR_HEIGHT = 600;

glm::vec3 Camera_front(0.0f,0.0f,-1.0f);

bool firstenter = true;
bool fly,fclicked = false;
float time = 0;
float lasttime = 0;
float deltatime = 0;
float mousespeed;
float yaw,pitch;

float lastX = SCR_WIDTH/2;
float lastY = SCR_HEIGHT/2;

void mouse_callback(GLFWwindow* window,double posx,double posy)
{
    if(firstenter)
    {
        lastX=posx;
        lastY=posy;
        firstenter=false;
    }

    float offsetX=posx-lastX;
    float offsetY=lastY-posy;
    mousespeed = sqrt(pow(offsetX,2)+pow(offsetY,2));

    lastX=posx;
    lastY=posy;

    float sensibility=0.05f;
    offsetX*=sensibility;
    offsetY*=sensibility;

    yaw+=offsetX;
    pitch+=offsetY;

    if(pitch>=89.0f)
    {
        pitch = 89.0f;
    }
    else if(pitch<=-89.0f)
    {
        pitch = -89.0f;
    }

    glm::vec3 front;
    front.x=cos(glm::radians(pitch))*cos(glm::radians(yaw));
    front.y=sin(glm::radians(pitch));
    front.z=cos(glm::radians(pitch))*sin(glm::radians(yaw));
    Camera_front = glm::normalize(front);

}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }



    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

    Loader loader;

    Shader objshader("shaders/objvertex.txt","shaders/objfragment.txt");
    Shader modelshader("shaders/modelvertex.txt","shaders/modelfragment.txt");
    TerrainShader terrainshader("shaders/terrainvertex.txt","shaders/terrainfragment.txt");
    GuiShader guishader("shaders/guivertex.txt","shaders/guifragment.txt");
    WaterShader watershader("shaders/watervertex.txt","shaders/waterfragment.txt");
    WaterFrameBuffers waterfbos(SCR_WIDTH,SCR_HEIGHT);

    MainRenderer renderer(loader,objshader,modelshader,terrainshader,watershader,waterfbos,800.0f,600.0f);
    GuiRenderer guirenderer(guishader,loader);

    Player mainplayer;

    std::vector<float> Pos = {
        -1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,

        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f,  1.0f,  1.0f,
        1.0f,  -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,

        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,   1.0f,
        1.0f,  1.0f,  -1.0f,
        -1.0f,  1.0f,  1.0f
    };
    std::vector<float> Norm = {
        0.0f,0.0f,-1.0f,
        0.0f,0.0f,-1.0f,
        0.0f,0.0f,-1.0f,
        0.0f,0.0f,-1.0f,

        0.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,

        -1.0f,0.0f,0.0f,
        -1.0f,0.0f,0.0f,
        -1.0f,0.0f,0.0f,
        -1.0f,0.0f,0.0f,

        1.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,

        0.0f,-1.0f,0.0f,
        0.0f,-1.0f,0.0f,
        0.0f,-1.0f,0.0f,
        0.0f,-1.0f,0.0f,

        0.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f
    };
    std::vector<float> Text = {
        0.0f,0.0f,
        1.0f,1.0f,
        1.0f,0.0f,
        0.0f,1.0f,

        0.0f,0.0f,
        1.0f,0.0f,
        1.0f,1.0f,
        0.0f,1.0f,

        1.0f,0.0f,
        1.0f,1.0f,
        0.0f,1.0f,
        0.0f,0.0f,

        1.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        0.0f,0.0f,

        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f,
        0.0f,0.0f,

        0.0f,1.0f,
        1.0f,0.0f,
        1.0f,1.0f,
        0.0f,0.0f,
    };
    std::vector<unsigned int> indices = {
        0,1,2,1,0,3,
        4,5,6,6,7,4,
        8,9,10,10,11,8,
        12,13,14,13,12,15,
        16,17,18,18,19,16,
        20,21,22,21,20,23
    };


    std::vector<float> planepositions = {
        -1.0f,1.0f,0.0f,
        -1.0f,-1.0f,0.0f,
        1.0f,1.0f,0.0f,
        1.0f,-1.0f,0.0f,
        1.0f,1.0f,0.0f,
        -1.0f,-1.0f,0.0f
    };
    std::vector<float> planeNorm = {
        0.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f
    };
    std::vector<float> planeText = {
        0.0f,0.0f,
        0.0f,1.0f,
        1.0f,0.0f,
        1.0f,1.0f,
        1.0f,0.0f,
        0.0f,1.0f
    };
    std::vector<unsigned int> planeindices = {0,1,2,3,4,5};
    //Terrain loading------------------------------------------------------0000000000000000000000000000000000000000000000000000
    std::string TextureFile = "ressources/box.jpg";

    TerrainTexture backgroundTexture(loader.loadTexture("ressources/grass.jpg"));
    TerrainTexture rTexture(loader.loadTexture("ressources/dirt.jpg"));
    TerrainTexture gTexture(loader.loadTexture("ressources/leaves.jpg"));
    TerrainTexture bTexture(loader.loadTexture("ressources/smooth_rock.jpg"));
    TerrainTexturePack texturepack(backgroundTexture,rTexture,gTexture,bTexture);

    TerrainTexture blendMap(loader.loadTexture("ressources/blendMaprr.png"));

    Terrain terrain(0,0,loader,texturepack,blendMap,"ressources/heightmapwater.png","terrain/save1.trn");

    //Entities---------------------------------------------------------------------0000000000000000000000000000000000000000000000000000000000000
    RawModel model = loader.loadtoVAO(Pos,Norm,Text,indices);
    TexturedModel staticModel(model,ModelTexture(loader.loadTexture(TextureFile)));
    std::vector<Entity> entities;

    RawModel planemodel = loader.loadtoVAO(planepositions,planeNorm,planeText,planeindices);
    TexturedModel planestaticModel(planemodel,ModelTexture(loader.loadTexture("ressources/floortexture.jpg")));
    RawModel impactmodel = loader.loadtoVAO(planepositions,planeNorm,planeText,planeindices);
    TexturedModel impactstaticModel(impactmodel,ModelTexture(loader.loadTexture("ressources/bullethole.png")));

    Entity entity(staticModel,glm::vec3(17.0f,terrain.getTerrainHeight(17.0f,0.0f)+0.5f,0.0f),0.0f,glm::vec3(1.0f,0.0f,0.0f),glm::vec3(0.5f));
    Entity wall(planestaticModel,glm::vec3(-19.0f,terrain.getTerrainHeight(-19.0f,8.0f)+2.0f,8.0f),67.0f,glm::vec3(0.0f,1.0f,0.0f),glm::vec3(3.0f));
    TransparentEntity impact(impactstaticModel,glm::vec3(0.0f,-8.0f,0.0f),0.0f,glm::vec3(0.0f,1.0f,0.0f),glm::vec3(0.2f));

    //Light---------------------------------0000000000000000000000000000000000000000000000000000000000000000000
    DirLight Sun(glm::vec3(-0.6f, -1.5f, -0.4f),glm::vec3(0.2f),glm::vec3(0.8f),glm::vec3(0.01f));

    //Gui--------------------------------------0000000000000000000000000000000000000000000000000000000000000
    std::vector<GuiTexture> Guis;
    /*GuiTexture reflection(waterfbos.getReflectionTexture(),glm::vec2(0.5f,0.5f),glm::vec2(0.25f,0.25f),0.0f);
    GuiTexture refraction(waterfbos.getRefractionTexture(),glm::vec2(-0.5f,0.5f),glm::vec2(0.25f,0.25f),0.0f);
    Guis.push_back(reflection);
    Guis.push_back(refraction);*/

    //Water-----------------------------------0000000000000000000000000000000000000000000
    WaterPlane water1(0.0f,0.0f,-1.0f,5.0f);
    //Models-------------------------------------------000000000000000000000000000000000000000000000000000
    Model gun(loader,"ressources/HandGun/gun.obj");
    gun.setPosition(glm::vec3(0.0f,5.0f,0.0f));
    gun.setScale(glm::vec3(0.4f));

    lasttime=glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        mainplayer.Move(window,deltatime);
        glfwSetCursorPosCallback(window,mouse_callback);

        //Calculate View------------------------------------------------------0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
        mainplayer.setCFront(Camera_front);
        mainplayer.setCAll(pitch,yaw);

        //Walking,Crouching and Jumping Physics ------------------------------------000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
        mainplayer.GlobalCollision(terrain,entities,deltatime);
        mainplayer.HoldGun(gun,deltatime,wall,impact);
        //mainplayer.SpawnBox(entities,entity,terrain,deltatime);
        //Render OBJ----------------------------------------------------------0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

        glEnable(GL_CLIP_DISTANCE0);

        waterfbos.bindReflectionFrameBuffer();
        float distance;
        distance = 2 * (mainplayer.getCamera().getY()-water1.getLevel());
        mainplayer.setCY(mainplayer.getCamera().getY() - distance);
        mainplayer.CInvertPitch();
        mainplayer.CActualiseFront();
        mainplayer.CViewCalculate();
        renderer.prepare();
        renderer.processEntity(wall);
        for(unsigned int i=0;i<entities.size();i++)
            renderer.processEntity(entities[i]);
        renderer.processTransparentEntity(impact);
        renderer.processTerrain(terrain);
        renderer.processModel(gun);
        renderer.render(Sun,mainplayer.getCamera(),glm::vec4(0.0f,1.0f,0.0f,-water1.getLevel()),deltatime);
        mainplayer.setCY(mainplayer.getCamera().getY() + distance);
        mainplayer.CInvertPitch();
        mainplayer.CActualiseFront();
        mainplayer.CViewCalculate();
        waterfbos.unbindCurrentFrameBuffer(SCR_WIDTH,SCR_HEIGHT);

        waterfbos.bindRefractionFrameBuffer();
        renderer.prepare();
        renderer.processEntity(wall);
        for(unsigned int i=0;i<entities.size();i++)
            renderer.processEntity(entities[i]);
        renderer.processTransparentEntity(impact);
        renderer.processTerrain(terrain);
        renderer.processModel(gun);
        renderer.render(Sun,mainplayer.getCamera(),glm::vec4(0.0f,-1.0f,0.0f,water1.getLevel()),deltatime);
        waterfbos.unbindCurrentFrameBuffer(SCR_WIDTH,SCR_HEIGHT);


        mainplayer.CViewCalculate();

        renderer.prepare();
        renderer.processEntity(wall);
        for(unsigned int i=0;i<entities.size();i++)
        {
            renderer.processEntity(entities[i]);
            entities[i].UpdatePos(deltatime);
            entities[i].Clean();
        }

        renderer.processTransparentEntity(impact);
        renderer.processTerrain(terrain);
        renderer.processModel(gun);
        renderer.processWater(water1);
        renderer.render(Sun,mainplayer.getCamera(),glm::vec4(0.0f,-1.0f,0.0f,1000.0f),deltatime);
        guirenderer.render(Guis);

        //Timing ---------------------------------------------------------00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

        time=glfwGetTime();
        deltatime=time-lasttime;
        lasttime=time;

        //Cleaning Rotation Model-----------------------------------
        wall.Clean();
        gun.Clean();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    waterfbos.cleanUp();
    guirenderer.cleanUp();
    renderer.cleanUp();
    loader.cleanUp();
    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
