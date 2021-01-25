#ifndef MODELTEXTURE_H_INCLUDED
#define MODELTEXTURE_H_INCLUDED

#include <iostream>

class ModelTexture
{
    public:
        ModelTexture()
        {

        }
        ModelTexture(unsigned int texture)
        {
            this->textureID = texture;
        }
        unsigned int getID()
        {
            return textureID;
        }
    private:
        unsigned int textureID;
};

#endif // MODELTEXTURE_H_INCLUDED
