#ifndef WATERSHADER_H_INCLUDED
#define WATERSHADER_H_INCLUDED

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

class WaterShader
{
    public:
        unsigned int ID;

        WaterShader();
        WaterShader(const GLchar *vertexPath,const GLchar *fragmentPath);

        void use();
        void stop();
        void Delete();

        void loadSun(DirLight sun);
        void loadCamera(Camera camera);
        void connectTextures();
        void loadMoveFactor(float factor);

        void setInt(const GLchar *name,GLint value);
        void setFloat(const GLchar *name,GLfloat value);
        void setMat4(const GLchar *name,GLsizei count,GLboolean transpose,glm::mat4 matrixvalue);
        void setVec3(const GLchar *name,glm::vec3 vecvalue);
        void setVec3(const GLchar *name,float x,float y,float z);
};

#endif // WATERSHADER_H_INCLUDED
