#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shaders/Shader.h"
#include "../model/Rawmodel.h"
#include "../model/Texturedmodel.h"
#include "../entity/Entity.h"
#include "EntityRenderer.h"

#include <iostream>
#include <vector>


EntityRenderer::EntityRenderer()
{
    //Constructor
}

EntityRenderer::EntityRenderer(Shader shader,glm::mat4 projection)
{
    this->shader = shader;
    shader.use();
    shader.setMat4("projection",1,GL_FALSE,projection);
    shader.stop();
}

void EntityRenderer::prepareTexturedModel(TexturedModel model)
{
    RawModel rawModel = model.getRawModel();
    glBindVertexArray(rawModel.getVaoID());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,model.getTexture().getID());
}

void EntityRenderer::render(std::vector<TexturedModel> textures,std::vector<Entity> entities,std::vector<TransparentEntity> transparententities)
{
    for(unsigned int i=0;i<textures.size();i++)
    {
        prepareTexturedModel(textures[i]);
        for(unsigned int j=0;j<entities.size();j++)
        {
            if(entities[j].getModel().getRawModel().getVaoID()==textures[i].getRawModel().getVaoID())
            {
                prepareInstance(entities[j]);
                glDrawElements(GL_TRIANGLES,textures[i].getRawModel().getVertexCount(),GL_UNSIGNED_INT,0);
            }
        }
        glBindVertexArray(0);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    for(unsigned int i=0;i<textures.size();i++)
    {
        prepareTexturedModel(textures[i]);
        for(unsigned int j=0;j<transparententities.size();j++)
        {
            if(transparententities[j].getModel().getRawModel().getVaoID()==textures[i].getRawModel().getVaoID())
            {
                prepareInstance(transparententities[j]);
                glDrawElements(GL_TRIANGLES,textures[i].getRawModel().getVertexCount(),GL_UNSIGNED_INT,0);
            }
        }
        glBindVertexArray(0);
    }
    glDisable(GL_BLEND);

}

void EntityRenderer::prepareInstance(Entity entity)
{
    glm::mat4 modelmat = glm::mat4(1.0f);
    modelmat = glm::translate(modelmat,entity.getPosition());
    modelmat = glm::rotate(modelmat,glm::radians(entity.getRotation()),entity.getAxe());
    for(unsigned int i=0;i<entity.getAddedRotation().size();i++)
        modelmat = glm::rotate(modelmat,glm::radians(entity.getAddedRotation()[i]),entity.getAddedAxeRotation()[i]);
    modelmat = glm::scale(modelmat,entity.getScale());
    shader.setMat4("model",1,GL_FALSE,modelmat);
}

void EntityRenderer::prepareInstance(TransparentEntity entity)
{
    glm::mat4 modelmat = glm::mat4(1.0f);
    modelmat = glm::translate(modelmat,entity.getPosition());
    modelmat = glm::rotate(modelmat,glm::radians(entity.getRotation()),entity.getAxe());
    modelmat = glm::scale(modelmat,entity.getScale());
    shader.setMat4("model",1,GL_FALSE,modelmat);
}
