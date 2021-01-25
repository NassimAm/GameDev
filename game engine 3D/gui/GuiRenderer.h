#ifndef GUIRENDERER_H_INCLUDED
#define GUIRENDERER_H_INCLUDED

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "GuiShader.h"
#include "../model/Rawmodel.h"
#include "../render_engine/Loader.h"
#include "GuiTexture.h"

class GuiRenderer
{
    public:
        GuiRenderer(GuiShader shader,Loader loader);
        void render(std::vector<GuiTexture> guis);
        void cleanUp();
    private:
        RawModel quad;
        GuiShader shader;

        void loadModelMatrix(GuiTexture gui);
};

#endif // GUIRENDERER_H_INCLUDED
