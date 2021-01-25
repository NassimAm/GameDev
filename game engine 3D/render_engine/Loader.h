#ifndef LOADER_H_INCLUDED
#define LOADER_H_INCLUDED

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <string>

#include "../stb_image.h"
#include "../model/Rawmodel.h"

class Loader
{
    public:
        Loader();
        RawModel loadtoVAO(std::vector<float> Pos,std::vector<float> Norm,std::vector<float> TextCoord,std::vector<unsigned int> indices);
        RawModel loadtoVAO(float Pos[],unsigned int vsize);
        unsigned int loadTexture(std::string path);
        unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
        void cleanUp();

    private:
        std::vector<unsigned int> VAOs;
        std::vector<unsigned int> VBOs;
        std::vector<unsigned int> EBOs;
        std::vector<unsigned int> textures;
        unsigned int vertexcount;

        unsigned int createVAO();
        void unbindVAO();
        void setupBuffer(std::vector<float> Pos,std::vector<float> Norm,std::vector<float> TextCoord,std::vector<unsigned int> indices);
        void setupBuffer(float Pos[],unsigned int vsize);
};


#endif // LOADER_H_INCLUDED
