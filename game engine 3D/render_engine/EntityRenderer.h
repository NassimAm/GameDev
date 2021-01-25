#ifndef ENTITYRENDERER_H_INCLUDED
#define ENTITYRENDERER_H_INCLUDED

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shaders/Shader.h"
#include "../model/Rawmodel.h"
#include "../model/Texturedmodel.h"
#include "../entity/Entity.h"

#include <iostream>
#include <vector>

class EntityRenderer
{
    public:
        EntityRenderer();
        EntityRenderer(Shader shader,glm::mat4 projection);
        void prepareTexturedModel(TexturedModel model);
        void render(std::vector<TexturedModel> textures,std::vector<Entity> entities,std::vector<TransparentEntity> transparententities);
    private:
        Shader shader;
        void prepareInstance(Entity entity);
        void prepareInstance(TransparentEntity entity);
};

#endif // ENTITYRENDERER_H_INCLUDED
