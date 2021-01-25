#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "GuiShader.h"

GuiShader::GuiShader()
{
    //Constructor
}

GuiShader::GuiShader(const GLchar *vertexPath,const GLchar *fragmentPath)
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


void GuiShader::use()
{
    glUseProgram(ID);
}

void GuiShader::stop()
{
    glUseProgram(0);
}

void GuiShader::Delete()
{
    glDeleteProgram(ID);
}

void GuiShader::setMat4(const GLchar *name,GLsizei count,GLboolean transpose,glm::mat4 matrixvalue)
{
    glUniformMatrix4fv(glGetUniformLocation(ID,name),count,transpose,glm::value_ptr(matrixvalue));
}
