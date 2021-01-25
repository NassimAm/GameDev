#include <iostream>

#include "Rawmodel.h"
#include "../texture/Modeltexture.h"
#include "Texturedmodel.h"

TexturedModel::TexturedModel(RawModel model)
{
    rawModel = model;
    //this->texture = texture;
}

TexturedModel::RawModel getRawModel()
{
    return rawModel;
}

TexturedModel::ModelTexture getTexture()
{
    return texture;
}
