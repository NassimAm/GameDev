#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "../model/Texturedmodel.h"

class Entity
{
    public:
        Entity(TexturedModel model,glm::vec3 position,float degres,glm::vec3 rotationaxe,glm::vec3 scale);
        TexturedModel getModel();
        void setModel(TexturedModel model);
        glm::vec3 getPosition();
        void setPosition(glm::vec3 position);

        float getRotation();
        glm::vec3 getAxe();
        void setRotation(float rotation,glm::vec3 axerotation);
        glm::vec3 getScale();

        void Rotate(float rotation,glm::vec3 axerotation);
        std::vector<float> getAddedRotation();
        std::vector<glm::vec3> getAddedAxeRotation();
        void Clean();

        void setVelX(float velocity_x);
        void setVelY(float velocity_y);
        void setVelZ(float velocity_z);

        float getVelX();
        float getVelY();
        float getVelZ();

        void UpdatePos(float deltatime);

    private:
        TexturedModel model;
        glm::vec3 position;
        float degres;
        glm::vec3 rotationaxe;
        glm::vec3 scale;
        std::vector<float> addedrotation;
        std::vector<glm::vec3> addedaxerotation;
        float velocity_x=0;
        float velocity_y=0;
        float velocity_z=0;
};

class TransparentEntity
{
    public:
        TransparentEntity(TexturedModel model,glm::vec3 position,float degres,glm::vec3 rotationaxe,glm::vec3 scale);
        TexturedModel getModel();
        void setModel(TexturedModel model);
        glm::vec3 getPosition();
        void setPosition(glm::vec3 position);

        float getRotation();
        glm::vec3 getAxe();
        void setRotation(float rotation,glm::vec3 axerotation);
        glm::vec3 getScale();

    private:
        TexturedModel model;
        glm::vec3 position;
        float degres;
        glm::vec3 rotationaxe;
        glm::vec3 scale;
};

#endif // ENTITY_H_INCLUDED
