#ifndef TEXTUREDMODEL_H_INCLUDED
#define TEXTUREDMODEL_H_INCLUDED

#include <iostream>

#include "Rawmodel.h"
#include"../texture/Modeltexture.h"

class TexturedModel
{
    public:
        TexturedModel()
        {
            //Constructor
        }
        TexturedModel(RawModel model,ModelTexture texture)
        {
            this->model = model;
            this->texture = texture;
        }
        RawModel getRawModel()
        {
            return model;
        }
        ModelTexture getTexture()
        {
            return texture;
        }
    private:
        RawModel model;
        ModelTexture texture;
};

#endif // TEXTUREDMODEL_H_INCLUDED
