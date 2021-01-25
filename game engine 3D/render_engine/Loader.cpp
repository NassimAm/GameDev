#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

#include "../stb_image.h"
#include "../model/Rawmodel.h"
#include "Loader.h"

Loader::Loader()
{
    //Constructor
}
RawModel Loader::loadtoVAO(std::vector<float> Pos,std::vector<float> Norm,std::vector<float> TextCoord,std::vector<unsigned int> indices)
{
    unsigned int VaoID = createVAO();
    setupBuffer(Pos,Norm,TextCoord,indices);
    unbindVAO();
    vertexcount = indices.size();
    return RawModel(VaoID,vertexcount);
}

RawModel Loader::loadtoVAO(float Pos[],unsigned int vsize)
{
    unsigned int VaoID = createVAO();
    setupBuffer(Pos,vsize);
    unbindVAO();
    vertexcount = vsize/(sizeof(float)*2);
    return RawModel(VaoID,vertexcount);
}

unsigned int Loader::loadTexture(std::string path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);


        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    textures.push_back(textureID);
    return textureID;
}

unsigned int Loader::TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);


    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
    textures.push_back(textureID);
    return textureID;
}

void Loader::cleanUp()
{
    for(unsigned int i=0;i<VAOs.size();i++)
        glDeleteVertexArrays(1,&VAOs[i]);
    for(unsigned int i=0;i<VBOs.size();i++)
        glDeleteBuffers(1,&VBOs[i]);
    for(unsigned int i=0;i<EBOs.size();i++)
        glDeleteBuffers(1,&EBOs[i]);
    for(unsigned int i=0;i<textures.size();i++)
        glDeleteTextures(1,&textures[i]);
}

unsigned int Loader::createVAO()
{
    unsigned int vao;
    glGenVertexArrays(1,&vao);
    VAOs.push_back(vao);
    glBindVertexArray(vao);
    return vao;
}

void Loader::unbindVAO()
{
    glBindVertexArray(0);
}

void Loader::setupBuffer(std::vector<float> Pos,std::vector<float> Norm,std::vector<float> TextCoord,std::vector<unsigned int> indices)
{
    unsigned int VboID[3];
    glGenBuffers(3,VboID);
    for(unsigned int i=0;i<3;i++)
        VBOs.push_back(VboID[i]);


    unsigned int EBO;
    glGenBuffers(1,&EBO);
    EBOs.push_back(EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,VboID[0]);
    glBufferData(GL_ARRAY_BUFFER,Pos.size()*sizeof(float),&Pos[0],GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,VboID[1]);
    glBufferData(GL_ARRAY_BUFFER,Norm.size()*sizeof(float),&Norm[0],GL_STATIC_DRAW);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER,VboID[2]);
    glBufferData(GL_ARRAY_BUFFER,TextCoord.size()*sizeof(float),&TextCoord[0],GL_STATIC_DRAW);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Loader::setupBuffer(float Pos[],unsigned int vsize)
{
    unsigned int VboID;
    glGenBuffers(1,&VboID);
    VBOs.push_back(VboID);
    //std::cout<<VboID<<std::endl;

    glBindBuffer(GL_ARRAY_BUFFER,VboID);
    glBufferData(GL_ARRAY_BUFFER,vsize,Pos,GL_STATIC_DRAW);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
}
