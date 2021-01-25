#ifndef LIGHTING_H_INCLUDED
#define LIGHTING_H_INCLUDED

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

class DirLight
{
    public:
        DirLight(glm::vec3 direction,glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular);

        void setDirection(glm::vec3 direction);
        void setAmbient(glm::vec3 ambient);
        void setDiffuse(glm::vec3 diffuse);
        void setSpecular(glm::vec3 specular);
        glm::vec3 getDirection();
        glm::vec3 getAmbient();
        glm::vec3 getDiffuse();
        glm::vec3 getSpecular();

    private:
        glm::vec3 direction,ambient,diffuse,specular;
};

/*class PointLight
{
public:
    PointLight(Shader shader,glm:: vec3 position,glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,float constant,float linear,float quadratic);

    void setPosition(glm::vec3 position);
    void setAmbient(glm::vec3 ambient);
    void setDiffuse(glm::vec3 diffuse);
    void setSpecular(glm::vec3 specular);
    void setConstant(float constant);
    void setLinear(float linear);
    void setQuadratic(float quadratic);



private:
    int positionloc,ambientloc,diffuseloc,specularloc,constantloc,linearloc,quadraticloc;
};


class SpotLight
{
public:
    SpotLight(Shader shader,glm:: vec3 position,glm::vec3 direction,glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,float constant,float linear,float quadratic,float cutoff,float outercutoff);

    void setPosition(glm::vec3 position);
    void setDirection(glm::vec3 direction);
    void setAmbient(glm::vec3 ambient);
    void setDiffuse(glm::vec3 diffuse);
    void setSpecular(glm::vec3 specular);
    void setConstant(float constant);
    void setLinear(float linear);
    void setQuadratic(float quadratic);
    void setCutoff(float cutoff);
    void setOuterCutoff(float outercutoff);

private:
    int positionloc,directionloc,ambientloc,diffuseloc,specularloc,constantloc,linearloc,quadraticloc,cutoffloc,outercutoffloc;
};*/

#endif // LIGHTING_H_INCLUDED
