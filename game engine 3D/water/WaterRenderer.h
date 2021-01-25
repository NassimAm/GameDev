#ifndef WATERRENDERER_H_INCLUDED
#define WATERRENDERER_H_INCLUDED

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "WaterShader.h"
#include "../model/Rawmodel.h"
#include "../render_engine/Loader.h"
#include "WaterPlane.h"
#include "WaterFrameBuffers.h"

class WaterRenderer
{
    public:
        WaterRenderer();
        WaterRenderer(Loader loader,WaterShader shader,glm::mat4 projection,WaterFrameBuffers fbos);
        void render(std::vector<WaterPlane> waters);
    private:
        RawModel quad;
        WaterShader shader;
        WaterFrameBuffers fbos;
        std::string dudvMapPath = "ressources/dudvMap.png";
        std::string normalMapPath = "ressources/matchingNormalMap.png";
        unsigned int dudvMapID;
        unsigned int normalMapID;

        void loadModelMatrix(WaterPlane water);
        void BindTextures(WaterPlane water);
};

#endif // WATERRENDERER_H_INCLUDED
