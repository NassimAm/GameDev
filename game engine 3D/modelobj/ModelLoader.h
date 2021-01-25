#ifndef MODELLOADER_H_INCLUDED
#define MODELLOADER_H_INCLUDED

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shaders/Shader.h"
#include "Model.h"

#include <iostream>
#include <vector>

class ModelLoader
{
    public:
        ModelLoader();
        ModelLoader(Shader shader,glm::mat4 projection);
        void render(std::vector<Model> models);
        void prepareInstance(Model model);
    private:
        Shader shader;
};

#endif // MODELLOADER_H_INCLUDED
