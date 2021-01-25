#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../model/Texturedmodel.h"
#include "Entity.h"

#include <iostream>

Entity::Entity(TexturedModel model,glm::vec3 position,float degres,glm::vec3 rotationaxe,glm::vec3 scale)
{
    this->model = model;
    this->position = position;
    this->degres = degres;
    this->rotationaxe = rotationaxe;
    this->scale = scale;
}

TexturedModel Entity::getModel()
{
    return model;
}

void Entity::setModel(TexturedModel model)
{
    this->model = model;
}

glm::vec3 Entity::getPosition()
{
    return position;
}

void Entity::setPosition(glm::vec3 position)
{
    this->position = position;
}

float Entity::getRotation()
{
    return degres;
}
glm::vec3 Entity::getAxe()
{
    return rotationaxe;
}

void Entity::setRotation(float rotation,glm::vec3 axerotation)
{
    degres = rotation;
    rotationaxe = axerotation;
}

glm::vec3 Entity::getScale()
{
    return scale;
}

void Entity::Rotate(float rotation,glm::vec3 axerotation)
{
    addedrotation.push_back(rotation);
    addedaxerotation.push_back(axerotation);
}

std::vector<float> Entity::getAddedRotation()
{
    return addedrotation;
}
std::vector<glm::vec3> Entity::getAddedAxeRotation()
{
    return addedaxerotation;
}
void Entity::Clean()
{
    addedrotation.clear();
    addedaxerotation.clear();
}

void Entity::setVelX(float velocity_x)
{
    this->velocity_x = velocity_x;
}
void Entity::setVelY(float velocity_y)
{
    this->velocity_y = velocity_y;
}
void Entity::setVelZ(float velocity_z)
{
    this->velocity_z = velocity_z;
}

float Entity::getVelX()
{
    return velocity_x;
}
float Entity::getVelY()
{
    return velocity_y;
}
float Entity::getVelZ()
{
    return velocity_z;
}

void Entity::UpdatePos(float deltatime)
{
    position.x+=velocity_x * deltatime;
    position.y+=velocity_y * deltatime;
    position.z+=velocity_z * deltatime;
}

//Transparent---------------------------------------------------------------------------------------00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

TransparentEntity::TransparentEntity(TexturedModel model,glm::vec3 position,float degres,glm::vec3 rotationaxe,glm::vec3 scale)
{
    this->model = model;
    this->position = position;
    this->degres = degres;
    this->rotationaxe = rotationaxe;
    this->scale = scale;
}

TexturedModel TransparentEntity::getModel()
{
    return model;
}

void TransparentEntity::setModel(TexturedModel model)
{
    this->model = model;
}

glm::vec3 TransparentEntity::getPosition()
{
    return position;
}

void TransparentEntity::setPosition(glm::vec3 position)
{
    this->position = position;
}

float TransparentEntity::getRotation()
{
    return degres;
}
glm::vec3 TransparentEntity::getAxe()
{
    return rotationaxe;
}

void TransparentEntity::setRotation(float rotation,glm::vec3 axerotation)
{
    degres = rotation;
    rotationaxe = axerotation;
}

glm::vec3 TransparentEntity::getScale()
{
    return scale;
}


