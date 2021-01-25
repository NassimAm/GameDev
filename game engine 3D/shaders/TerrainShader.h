#ifndef TERRAINSHADER_H_INCLUDED
#define TERRAINSHADER_H_INCLUDED

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "../Player/Camera.h"
#include "../light/Lighting.h"

class TerrainShader
{
public :
    unsigned int ID;

    TerrainShader();
    TerrainShader(const GLchar *vertexPath,const GLchar *fragmentPath);

    void use();
    void stop();
    void Delete();

    void loadSun(DirLight sun);
    void loadCamera(Camera camera);
    void connectTextures();
    void loadClipPlane(glm::vec4 plane);

    void setBool(const GLchar *name,GLboolean value);
    void setFloat(const GLchar *name,GLfloat value);
    void setInt(const GLchar *name,GLint value);
    void setMat4(const GLchar *name,GLsizei count,GLboolean transpose,glm::mat4 matrixvalue);
    void setVec3(const GLchar *name,glm::vec3 vecvalue);
    void setVec3(const GLchar *name,float x,float y,float z);
    void setVec4(const GLchar *name,glm::vec4 vecvalue);
};

#endif // TERRAINSHADER_H_INCLUDED
