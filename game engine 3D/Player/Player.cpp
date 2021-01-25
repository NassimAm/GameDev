#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "../terrain/Terrain.h"
#include "Camera.h"
#include "Player.h"

Player::Player()
{
    //Constructor
}

void Player::Move(GLFWwindow *window,float deltatime)
{
    if(glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS)
    {
        if(!fp&&!fpclicked)
        {
            fp = true;
            fpclicked = true;
        }
        if(fp&&!fpclicked)
        {
            fp = false;
            fpclicked = true;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_F5) == GLFW_RELEASE)
        fpclicked = false;

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        scoop = true;
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
        scoop = false;

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        if(!fireclicked)
        {
            fire = true;
            fireclicked = true;
        }
        else
            fire = false;
    }
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        fireclicked = false;

    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        if(!fly&&!fclicked)
        {
            fly = true;
            fclicked = true;
        }
        if(fly&&!fclicked)
        {
            fly = false;
            fclicked = true;
            if(PlayerPos.y>0.0f)
                jumping = true;
        }

    }
    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE)
        fclicked = false;

    //FLYING----------------------------------------------------------------------
    Camera_right=glm::normalize(glm::cross(camera.getFront(), camera.getUp()));

    if(fly)
    {
        if(running)
            playerspeed = 10.0f;
        else
            playerspeed = 8.0f;

        if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
            PlayerPos +=  camera.getFront()*playerspeed*deltatime;
        if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
            PlayerPos -=  camera.getFront()*playerspeed*deltatime;
        if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
            PlayerPos -= glm::normalize(glm::cross(camera.getFront(), camera.getUp())) * playerspeed*deltatime;
        if (glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
            PlayerPos += glm::normalize(glm::cross(camera.getFront(),camera.getUp()))*playerspeed*deltatime;
        if (glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            PlayerPos -= camera.getUp()*playerspeed*deltatime;
        if (glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS)
            PlayerPos += camera.getUp()*playerspeed*deltatime;
    }


    //WALKING-----------------------------------------------------------------------
    if(!fly)
    {
        frontx = camera.getFront().x;
        frontz = camera.getFront().z;
        multiplicator = 1.0f/sqrt(pow(camera.getFront().x,2)+pow(camera.getFront().z,2));
        if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
        {
            PlayerPos.x += frontx*multiplicator*playerspeed*deltatime;
            PlayerPos.z += frontz*multiplicator*playerspeed*deltatime;
        }
        if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
        {
            PlayerPos.x -= frontx*multiplicator*playerspeed*deltatime;
            PlayerPos.z -= frontz*multiplicator*playerspeed*deltatime;
        }
        if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
        {
            PlayerPos.x -= Camera_right.x * playerspeed*deltatime;
            PlayerPos.z -= Camera_right.z * playerspeed*deltatime;
        }
        if (glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
        {
            PlayerPos.x += Camera_right.x * playerspeed*deltatime;
            PlayerPos.z += Camera_right.z * playerspeed*deltatime;
        }


        //Physics-----------------------------------------------
        if (glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            crouching=true;
        if (glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS&&!jumping)
        {
            jump =true;
        }


        if (glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
            crouching=false;
        if (glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_RELEASE)
            jump=false;

    }

    if(glfwGetKey(window,GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        running = true;
    if (glfwGetKey(window,GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
        running=false;

    if(fp)
        camera.setPosition(PlayerPos);
    else
        camera.setPosition(PlayerPos-camera.getFront()*1.5f);

}

void Player::GlobalCollision(Terrain terrain,std::vector<Entity> entities,float deltatime)
{
    terrainh = terrain.getTerrainHeight(PlayerPos.x,PlayerPos.z)+2.0f;
    getEntityCollisionID(entities);

    std::cout<<entityidentifier<<" || "<<onEntity<<std::endl;

    if(!fly)
    {

        if(jump&&!jumping)
        {
            velocityy=6.0f;
            onEntity = false;
            jumping=true;
            jump=false;
        }



        if(!onEntity)
        {
            if(PlayerPos.y<=terrainh)
            {
                jumping=false;
            }


            if(PlayerPos.y>terrainh&&jumping)
            {
                velocityy-= gravity * deltatime;
            }
            else if(PlayerPos.y<terrainh&&!jumping&&!crouching)
            {
                if(running)
                    playerspeed = 10.0f;
                else
                    playerspeed = 8.0f;

                PlayerPos.y = terrainh;
                velocityy=0.0f;
                jumping=false;
                stopcrouch=false;
            }

            if(crouching)
            {
                if(PlayerPos.y>terrainh-1.0f)
                {
                    velocityy-=4.0f* deltatime;
                }
                if(PlayerPos.y<=terrainh-1.0f)
                {
                    if(!stopcrouch||!jumping)
                        velocityy=0.0f;

                    stopcrouch=true;
                    playerspeed = 2.0f;
                }
            }
        }
        else if(onEntity&&((entityidentifier!=entities.size()&&!entities.empty())||entities.size()==1))
        {

            if(PlayerPos.y<=entities[entityidentifier].getPosition().y+entities[entityidentifier].getScale().y+2.0f)
            {
                jumping=false;
            }

            if(PlayerPos.y>entities[entityidentifier].getPosition().y+entities[entityidentifier].getScale().y+2.0f&&jumping)
            {
                velocityy-= gravity * deltatime;
            }
            else if(PlayerPos.y<entities[entityidentifier].getPosition().y+entities[entityidentifier].getScale().y+2.0f&&!jumping&&!crouching)
            {
                if(running)
                    playerspeed = 10.0f;
                else
                    playerspeed = 8.0f;

                PlayerPos.y = entities[entityidentifier].getPosition().y+entities[entityidentifier].getScale().y+2.0f;
                velocityy=0.0f;
                jumping=false;
                stopcrouch=false;
            }

            if(crouching)
            {
                if(PlayerPos.y>entities[entityidentifier].getPosition().y+entities[entityidentifier].getScale().y+1.0f)
                {
                    velocityy-=4.0f* deltatime;
                }
                if(PlayerPos.y<=entities[entityidentifier].getPosition().y+entities[entityidentifier].getScale().y+1.0f)
                {
                    if(!stopcrouch||!jumping)
                        velocityy=0.0f;

                    stopcrouch=true;
                    playerspeed = 2.0f;
                }
            }
        }



        UpDatePosition(deltatime);
    }
}

void Player::UpDatePosition(float deltatime)
{
    PlayerPos.x += velocityx;
    PlayerPos.y = PlayerPos.y + velocityy * deltatime;
    PlayerPos.z += velocityz;

    if(fp)
        camera.setPosition(PlayerPos);
    else
        camera.setPosition(PlayerPos-camera.getFront()*1.5f);

    if(scoop)
    {
        camera.setPosition(camera.getPosition()+camera.getFront()*glm::vec3(0.4f));
        //playerspeed = 2.0f;
    }

}

//Camera--------------------------------------------------------------------------------------------

Camera Player::getCamera()
{
    return camera;
}

void Player::setCFront(glm::vec3 Camera_front)
{
    camera.setFront(Camera_front);
}
void Player::setCAll(float pitch,float yaw)
{
    camera.setAll(pitch,yaw);
}
void Player::setCPosition(glm::vec3 position)
{
    camera.setPosition(position);
}
void Player::setCX(float x)
{
    camera.setX(x);
}
void Player::setCY(float y)
{
    camera.setY(y);
}
void Player::setCZ(float z)
{
    camera.setZ(z);
}

void Player::CInvertPitch()
{
    camera.invertPitch();
}
void Player::CActualiseFront()
{
    camera.ActualiseFront();
}
void Player::CViewCalculate()
{
    camera.CalculateView();
}

//Arms-----------------------------------------------------------------------------------
void Player::HoldGun(Model &gun,float deltatime,Entity entity,TransparentEntity &entity2)
{
    glm::vec3 genpos;
    if(scoop)
        genpos = PlayerPos+camera.getFront() - glm::normalize(glm::cross(Camera_right,camera.getFront()))  * glm::vec3(0.25f);
    else
        genpos = PlayerPos + camera.getFront() + Camera_right * glm::vec3(0.5f) - glm::normalize(glm::cross(Camera_right,camera.getFront())) * glm::vec3(0.25f);

    gun.setPosition(glm::vec3(genpos));
    gun.setRotation(-camera.getYaw(),glm::normalize(glm::cross(Camera_right,camera.getFront())));
    if(fire)
    {
        firerecul = 30.0f;
        entity2.setRotation(entity.getRotation(),entity.getAxe());
        entity2.setPosition(getBulletCollision(entity));
    }
    else if(!fire)
    {
        if(firerecul>0.0f)
            firerecul-= 250.0f * deltatime;
        else
            firerecul = 0.0f;
    }
    gun.Rotate(camera.getPitch(),Camera_right);
    gun.Rotate(firerecul,glm::vec3(0.0f,0.0f,1.0f));

}

glm::vec3 Player::getBulletCollision(Entity entity)
{
    glm::vec3 first = camera.getPosition();
    glm::vec3 second = camera.getPosition()+camera.getFront()*glm::vec3(range);
    glm::vec3 midle;
    for(unsigned int i=0;i<calculations;i++)
    {
        midle = glm::vec3((first+second)/2.0f);
        if(midle.z<-(sin(glm::radians(entity.getRotation()))/cos(glm::radians(entity.getRotation()))) * (midle.x-entity.getPosition().x)+entity.getPosition().z+0.01f)
            second = midle;
        if(midle.z>-(sin(glm::radians(entity.getRotation()))/cos(glm::radians(entity.getRotation()))) * (midle.x-entity.getPosition().x)+entity.getPosition().z+0.01f)
            first = midle;
    }
    if(midle.y<entity.getPosition().y-entity.getScale().y || midle.y>entity.getPosition().y+entity.getScale().y || midle.x<entity.getPosition().x-entity.getScale().x * cos(glm::radians(entity.getRotation()))
        || midle.x>entity.getPosition().x+entity.getScale().x * cos(glm::radians(entity.getRotation())))
        {
            return glm::vec3(0.0f,-8.0f,0.0f);
        }
    else
        return midle;
}

void Player::SpawnBox(std::vector<Entity> &entities,Entity &entityex,Terrain terrain,float deltatime)
{
    float speed = 15.0f;
    if(fire)
    {
        entityex.setPosition(camera.getPosition());
        entityex.setVelX(speed*camera.getFront().x);
        entityex.setVelY(speed*camera.getFront().y);
        entityex.setVelZ(speed*camera.getFront().z);
        entities.push_back(entityex);
    }
    for(unsigned int i=0;i<entities.size();i++)
    {
        if(entities[i].getPosition().y-0.5f<terrain.getTerrainHeight(entities[i].getPosition().x,entities[i].getPosition().z))
        {
            entities[i].setVelX(0.0f);
            entities[i].setVelY(0.0f);
            entities[i].setVelZ(0.0f);
            entities[i].setPosition(glm::vec3(entities[i].getPosition().x,terrain.getTerrainHeight(entities[i].getPosition().x,entities[i].getPosition().z)+0.5f,entities[i].getPosition().z));
        }
        else
            entities[i].setVelY(entities[i].getVelY()-gravity*deltatime);
    }
    if(scoop)
        entities.clear();
}
void Player::getEntityCollisionID(std::vector<Entity> entities)
{
    entityidentifier = 0;

    for(unsigned int i=0;i<entities.size();i++)
    {
        /*if(PlayerPos.x>entities[i].getPosition().x-entities[i].getScale().x&&PlayerPos.x<entities[i].getPosition().x+entities[i].getScale().x
           &&PlayerPos.z>entities[i].getPosition().z-entities[i].getScale().z&&PlayerPos.z<entities[i].getPosition().z+entities[i].getScale().z
           &&PlayerPos.y<entities[i].getPosition().y+entities[i].getScale().y+2.0f)
        {
            PlayerPos.x = prevPos.x;
            PlayerPos.z = prevPos.z;
        }*/
        if(PlayerPos.x>entities[i].getPosition().x-entities[i].getScale().x&&PlayerPos.x<entities[i].getPosition().x+entities[i].getScale().x
           &&PlayerPos.z>entities[i].getPosition().z-entities[i].getScale().z&&PlayerPos.z<entities[i].getPosition().z+entities[i].getScale().z
                &&PlayerPos.y>entities[i].getPosition().y+entities[i].getScale().y+2.0f)
        {
            onEntity = true;
            justQuitEntity = false;
            break;
        }
        /*else
        {
            prevPos = PlayerPos;

        }*/
        entityidentifier++;
    }


    /*if((entityidentifier!=entities.size()&&!entities.empty())||entities.size()==1)
    {
        if(PlayerPos.x<entities[entityidentifier].getPosition().x-entities[entityidentifier].getScale().x||PlayerPos.x>entities[entityidentifier].getPosition().x+entities[entityidentifier].getScale().x
       ||PlayerPos.z<entities[entityidentifier].getPosition().z-entities[entityidentifier].getScale().z||PlayerPos.z>entities[entityidentifier].getPosition().z+entities[entityidentifier].getScale().z)
       {
           onEntity = false;
           if(!justQuitEntity)
           {
               jumping = true;
               justQuitEntity = true;
           }
       }
    }*/
}
