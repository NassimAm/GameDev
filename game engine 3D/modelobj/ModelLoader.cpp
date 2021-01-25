#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shaders/Shader.h"
#include "Model.h"
#include "ModelLoader.h"

#include <iostream>
#include <vector>


ModelLoader::ModelLoader()
{
    //Constructor
}

ModelLoader::ModelLoader(Shader shader,glm::mat4 projection)
{
    this->shader = shader;
    shader.use();
    shader.setMat4("projection",1,GL_FALSE,projection);
    shader.stop();
}


void ModelLoader::render(std::vector<Model> models)
{
    for(unsigned int i=0;i<models.size();i++)
    {
        prepareInstance(models[i]);
        models[i].Draw(shader);
    }
}

void ModelLoader::prepareInstance(Model model)
{
    glm::mat4 modelmat = glm::mat4(1.0f);
    modelmat = glm::translate(modelmat,model.getPosition());
    modelmat = glm::rotate(modelmat,glm::radians(model.getRotation()),model.getAxeRotation());

    for(unsigned int i=0;i<model.getAddedRotation().size();i++)
        modelmat = glm::rotate(modelmat,glm::radians(model.getAddedRotation()[i]),model.getAddedAxeRotation()[i]);

    modelmat = glm::scale(modelmat,model.getScale());
    shader.setMat4("model",1,GL_FALSE,modelmat);
    //std::cout<<model.getAddedRotation().size()<<std::endl;
    model.Clean();
}
