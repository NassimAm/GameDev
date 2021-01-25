#ifndef GUITEXTURE_H_INCLUDED
#define GUITEXTURE_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GuiTexture
{
    public:
        GuiTexture()
        {
            //Constructor
        }
        GuiTexture(unsigned int texture,glm::vec2 position,glm::vec2 scale,float rotation)
        {
            this->texture = texture;
            this->position = position;
            this->scale = scale;
            this->rotation = rotation;
        }

        unsigned int getTexture()
        {
            return texture;
        }
        glm::vec2 getPosition()
        {
            return position;
        }
        glm::vec2 getScale()
        {
            return scale;
        }
        float getRotation()
        {
            return rotation;
        }

        void setPosition(glm::vec2 position)
        {
            this->position = position;
        }
        void setScale(glm::vec2 scale)
        {
            this->scale = scale;
        }
        void setRotation(float rotation)
        {
            this->rotation = rotation;
        }
    private:
        unsigned int texture;
        glm::vec2 position;
        glm::vec2 scale;
        float rotation;
};

#endif // GUITEXTURE_H_INCLUDED
