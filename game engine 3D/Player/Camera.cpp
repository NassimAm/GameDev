#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "Camera.h"

Camera::Camera()
{
    //Constructor
}

void Camera::CalculateView()
{
    viewmat = glm::lookAt(Viewpos,Viewpos+Camera_front,Camera_up);
}

void Camera::setPosition(glm::vec3 position)
{
    Viewpos = position;
}

void Camera::setX(float x)
{
    Viewpos.x = x;
}
void Camera::setY(float y)
{
    Viewpos.y = y;
}
void Camera::setZ(float z)
{
    Viewpos.z = z;
}

void Camera::setFront(glm::vec3 frontcamera)
{
    Camera_front = frontcamera;
}

void Camera::setSpeed(float speed)
{
    Camera_speed = speed;
}

void Camera::setAll(float pitch,float yaw)
{
    this->pitch = pitch;
    this->yaw = yaw;
}

void Camera::invertPitch()
{
    pitch = -pitch;
}

glm::mat4 Camera::getViewMat()
{
    return viewmat;
}

glm::vec3 Camera::getPosition()
{
    return Viewpos;
}

float Camera::getX()
{
    return Viewpos.x;
}
float Camera::getY()
{
    return Viewpos.y;
}
float Camera::getZ()
{
    return Viewpos.z;
}

glm::vec3 Camera::getFront()
{
    return Camera_front;
}
glm::vec3 Camera::getUp()
{
    return Camera_up;
}
float Camera::getSpeed()
{
    return Camera_speed;
}

float Camera::getYaw()
{
    return yaw;
}

float Camera::getPitch()
{
    return pitch;
}

void Camera::ActualiseFront()
{
    glm::vec3 front;
    front.x=cos(glm::radians(pitch))*cos(glm::radians(yaw));
    front.y=sin(glm::radians(pitch));
    front.z=cos(glm::radians(pitch))*sin(glm::radians(yaw));
    Camera_front = glm::normalize(front);
}
