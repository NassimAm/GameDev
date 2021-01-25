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
#include "WaterRenderer.h"
#include "WaterFrameBuffers.h"

WaterRenderer::WaterRenderer()
{
    //Constructor
}
WaterRenderer::WaterRenderer(Loader loader,WaterShader shader,glm::mat4 projection,WaterFrameBuffers fbos)
{
    this->shader = shader;
    this->fbos = fbos;
    dudvMapID = loader.loadTexture(dudvMapPath);
    normalMapID = loader.loadTexture(normalMapPath);
    shader.use();
    shader.setMat4("projection",1,GL_FALSE,projection);
    shader.connectTextures();
    shader.stop();
    float positions[] = {-1,-1,-1,1,1,1,1,1,1,-1,-1,-1};
    quad = loader.loadtoVAO(positions,sizeof(positions));
}

void WaterRenderer::render(std::vector<WaterPlane> waters)
{
    glBindVertexArray(quad.getVaoID());
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    for(unsigned int i=0;i<waters.size();i++)
    {
        loadModelMatrix(waters[i]);
        BindTextures(waters[i]);
        glDrawArrays(GL_TRIANGLES,0,quad.getVertexCount());
    }
    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glBindVertexArray(0);
}

void WaterRenderer::loadModelMatrix(WaterPlane water)
{
    glm::mat4 modelmat = glm::mat4(1.0f);
    modelmat = glm::translate(modelmat,glm::vec3(water.getX(),water.getLevel(),water.getZ()));
    modelmat = glm::scale(modelmat,glm::vec3(water.getSize(),0.0f,water.getSize()));
    shader.setMat4("model",1,GL_FALSE,modelmat);
}

void WaterRenderer::BindTextures(WaterPlane water)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,fbos.getReflectionTexture());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,fbos.getRefractionTexture());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D,dudvMapID);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D,normalMapID);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D,fbos.getRefractionDepthTexture());
}
