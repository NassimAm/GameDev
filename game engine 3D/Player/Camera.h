#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Camera
{
    public:
        Camera();
        void CalculateView();
        void setPosition(glm::vec3 position);
        void setX(float x);
        void setY(float y);
        void setZ(float z);
        void setFront(glm::vec3 frontcamera);
        void setSpeed(float speed);
        void ActualiseFront();
        void invertPitch();
        void setAll(float pitch,float yaw);
        glm::mat4 getViewMat();
        glm::vec3 getPosition();
        float getX();
        float getY();
        float getZ();
        glm::vec3 getFront();
        glm::vec3 getUp();
        float getSpeed();
        float getYaw();
        float getPitch();
    private:
        glm::vec3 Viewpos = glm::vec3(0.0f,10.0f,0.0f);
        glm::vec3 Camera_up = glm::vec3(0.0f,1.0f,0.0f);
        glm::vec3 Camera_front;
        float Camera_speed = 8.0f;
        float yaw;
        float pitch;
        float sensibility=0.05f;

        glm::mat4 viewmat = glm::mat4(1.0f);

        bool firstenter = true;

};

#endif // CAMERA_H_INCLUDED
