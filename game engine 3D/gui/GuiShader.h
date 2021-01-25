#ifndef GUISHADER_H_INCLUDED
#define GUISHADER_H_INCLUDED

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class GuiShader
{
    public:
        unsigned int ID;

        GuiShader();
        GuiShader(const GLchar *vertexPath,const GLchar *fragmentPath);

        void use();
        void stop();
        void Delete();

        void setMat4(const GLchar *name,GLsizei count,GLboolean transpose,glm::mat4 matrixvalue);
};

#endif // GUISHADER_H_INCLUDED
