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
#include "GuiRenderer.h"

GuiRenderer::GuiRenderer(GuiShader shader,Loader loader)
{
    this->shader = shader;
    float positions[] = {-1,1,-1,-1,1,1,1,-1,1,1,-1,-1};
    quad = loader.loadtoVAO(positions,sizeof(positions));
}

void GuiRenderer::render(std::vector<GuiTexture> guis)
{
    shader.use();
    glBindVertexArray(quad.getVaoID());
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC0_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    for(unsigned int i=0;i<guis.size();i++)
    {
        loadModelMatrix(guis[i]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,guis[i].getTexture());
        glDrawArrays(GL_TRIANGLES,0,quad.getVertexCount());
    }
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glBindVertexArray(0);
    shader.stop();
}

void GuiRenderer::cleanUp()
{
    shader.Delete();
}

void GuiRenderer::loadModelMatrix(GuiTexture gui)
{
    glm::mat4 modelmat = glm::mat4(1.0f);
    modelmat = glm::translate(modelmat,glm::vec3(gui.getPosition(),0.0f));
    modelmat = glm::rotate(modelmat,glm::radians(gui.getRotation()),glm::vec3(0.0f,0.0f,1.0f));
    modelmat = glm::scale(modelmat,glm::vec3(gui.getScale(),0.0f));
    shader.setMat4("model",1,GL_FALSE,modelmat);
}
