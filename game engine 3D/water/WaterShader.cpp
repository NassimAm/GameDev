#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "../light/Lighting.h"
#include "WaterShader.h"


WaterShader::WaterShader()
{
    //Constructor
}

WaterShader::WaterShader(const GLchar *vertexPath,const GLchar *fragmentPath)
{
    //Read vertex's and fragment's code--------------------------------------------------
    std::string vertexString,fragmentString;
    std::ifstream vShaderFile,fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit|std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit|std::ifstream::badbit);

    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderScript,fShaderScript;

        vShaderScript<<vShaderFile.rdbuf();
        fShaderScript<<fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexString = vShaderScript.str();
        fragmentString = fShaderScript.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout<<"ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ"<<std::endl;
    }
    const char* vertexCode = vertexString.c_str();
    const char* fragmentCode = fragmentString.c_str();

    //Vertex and fragment----------------------------------------------------------------
    unsigned int vertex,fragment;
    int success;
    char Infolog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vertexCode,NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(vertex,512,NULL,Infolog);
        std::cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<Infolog<<std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fragmentCode,NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(fragment,512,NULL,Infolog);
        std::cout<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<Infolog<<std::endl;
    }

    //Shader Program-----------------------------------------------------------------------
    ID = glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID,GL_LINK_STATUS,&success);
    if(!success)
    {
        glGetProgramInfoLog(ID,512,NULL,Infolog);
        std::cout<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<Infolog<<std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}


void WaterShader::use()
{
    glUseProgram(ID);
}

void WaterShader::stop()
{
    glUseProgram(0);
}

void WaterShader::Delete()
{
    glDeleteProgram(ID);
}

void WaterShader::setInt(const GLchar *name, GLint value)
{
    glUniform1i(glGetUniformLocation(ID,name),value);
}

void WaterShader::setFloat(const GLchar *name, GLfloat value)
{
    glUniform1f(glGetUniformLocation(ID,name),value);
}

void WaterShader::setMat4(const GLchar *name,GLsizei count,GLboolean transpose,glm::mat4 matrixvalue)
{
    glUniformMatrix4fv(glGetUniformLocation(ID,name),count,transpose,glm::value_ptr(matrixvalue));
}

void WaterShader::setVec3(const GLchar *name,glm::vec3 vecvalue)
{
    glUniform3f(glGetUniformLocation(ID,name),vecvalue.x,vecvalue.y,vecvalue.z);
}
void WaterShader::setVec3(const GLchar *name,float x,float y,float z)
{
    glUniform3f(glGetUniformLocation(ID,name),x,y,z);
}

void WaterShader::loadSun(DirLight sun)
{
    setVec3("sun.direction",sun.getDirection());
    setVec3("sun.ambient",sun.getAmbient());
    setVec3("sun.diffuse",sun.getDiffuse());
    setVec3("sun.specular",sun.getSpecular());
}

void WaterShader::loadCamera(Camera camera)
{
    setMat4("view",1,GL_FALSE,camera.getViewMat());
    setVec3("ViewPos",camera.getPosition());
}

void WaterShader::connectTextures()
{
    setInt("reflectionTexture",0);
    setInt("refractionTexture",1);
    setInt("dudvMap",2);
    setInt("normalMap",3);
    setInt("depthMap",4);
}

void WaterShader::loadMoveFactor(float factor)
{
    setFloat("moveFactor",factor);
}
