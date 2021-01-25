#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "../terrain/Terrain.h"
#include "Camera.h"
#include "../entity/Entity.h"
#include "../modelobj/Model.h"

class Player
{
    public:
        Player();
        void Move(GLFWwindow *window,float deltatime);
        void GlobalCollision(Terrain terrain,std::vector<Entity> entities,float deltatime);
        void UpDatePosition(float deltatime);

        //Camera----------------------------------------------------------
        Camera getCamera();
        void setCFront(glm::vec3 Camera_front);
        void setCAll(float pitch,float yaw);
        void setCPosition(glm::vec3 position);
        void setCX(float x);
        void setCY(float y);
        void setCZ(float z);
        void CInvertPitch();
        void CActualiseFront();
        void CViewCalculate();
        //Player------------------------------------------------------------
        void HoldGun(Model &gun,float deltatime,Entity entity,TransparentEntity &entity2);
        //Test
        void SpawnBox(std::vector<Entity> &entities,Entity &entityex,Terrain terrain,float deltatime);
    private:
        glm::vec3 PlayerPos = glm::vec3(0.0f,0.0f,0.0f);
        bool fly = false;
        bool fclicked = false;
        float gravity = 15.0f;
        float multiplicator = 0.0f;
        float frontx = 0.0f;
        float frontz = 0.0f;
        bool jumping = false;
        bool jump = false;
        bool crouching = false;
        bool stopcrouch = false;
        bool running = false;
        float velocityx = 0.0f;
        float velocityy = 0.0f;
        float velocityz = 0.0f;
        float playerspeed = 8.0f;
        //Commands----------------------------------------------
        bool fp = true;
        bool fpclicked = false;
        bool scoop = false;
        bool fire = false;
        bool fireclicked = false;
        float firerecul = 0.0f;

        float range = 50.0f;
        unsigned int calculations = 200;
        //Terrain---------------------------------
        float terrainh;
        glm::vec3 prevPos;
        bool onEntity = false;
        bool justQuitEntity = true;
        unsigned int entityidentifier = 0;

        Camera camera;
        glm::vec3 Camera_right = glm::vec3(1.0f,0.0f,0.0f);
        glm::vec3 getBulletCollision(Entity entity);
        void getEntityCollisionID(std::vector<Entity> entities);
};

#endif // PLAYER_H_INCLUDED
