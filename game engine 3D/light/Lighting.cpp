#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

#include "Lighting.h"

DirLight::DirLight(glm::vec3 direction,glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular)
{
    this->direction = direction;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}

void DirLight::setDirection(glm::vec3 direction)
{
    this->direction = direction;
}
void DirLight::setAmbient(glm::vec3 ambient)
{
    this->ambient = ambient;
}
void DirLight::setDiffuse(glm::vec3 diffuse)
{
    this->diffuse = diffuse;
}
void DirLight::setSpecular(glm::vec3 specular)
{
    this->specular = specular;
}

glm::vec3 DirLight::getDirection()
{
    return direction;
}
glm::vec3 DirLight::getAmbient()
{
    return ambient;
}
glm::vec3 DirLight::getDiffuse()
{
    return diffuse;
}
glm::vec3 DirLight::getSpecular()
{
    return specular;
}

/*PointLight::PointLight(Shader shader,glm:: vec3 position,glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,float constant,float linear,float quadratic)
{

    positionloc = glGetUniformLocation(shader.ID,"pointlight.position");
    ambientloc = glGetUniformLocation(shader.ID,"pointlight.ambient");
    diffuseloc = glGetUniformLocation(shader.ID,"pointlight.diffuse");
    specularloc = glGetUniformLocation(shader.ID,"pointlight.specular");
    constantloc = glGetUniformLocation(shader.ID,"pointlight.constant");
    linearloc = glGetUniformLocation(shader.ID,"pointlight.linear");
    quadraticloc = glGetUniformLocation(shader.ID,"pointlight.quadratic");
    glUniform3f(positionloc,position.x,position.y,position.z);
    glUniform3f(ambientloc,ambient.x,ambient.y,ambient.z);
    glUniform3f(diffuseloc,diffuse.x,diffuse.y,diffuse.z);
    glUniform3f(specularloc,specular.x,specular.y,specular.z);
    glUniform1f(constantloc,constant);
    glUniform1f(linearloc,linear);
    glUniform1f(quadraticloc,quadratic);
}

void PointLight::setPosition(glm::vec3 position)
{
    glUniform3f(positionloc,position.x,position.y,position.z);
}
void PointLight::setAmbient(glm::vec3 ambient)
{
    glUniform3f(ambientloc,ambient.x,ambient.y,ambient.z);
}
void PointLight::setDiffuse(glm::vec3 diffuse)
{
    glUniform3f(diffuseloc,diffuse.x,diffuse.y,diffuse.z);
}
void PointLight::setSpecular(glm::vec3 specular)
{
    glUniform3f(specularloc,specular.x,specular.y,specular.z);
}
void PointLight::setConstant(float constant)
{
    glUniform1f(constantloc,constant);
}
void PointLight::setLinear(float linear)
{
    glUniform1f(linearloc,linear);
}
void PointLight::setQuadratic(float quadratic)
{
    glUniform1f(quadraticloc,quadratic);
}



SpotLight::SpotLight(Shader shader,glm:: vec3 position,glm::vec3 direction,glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,float constant,float linear,float quadratic,float cutoff,float outercutoff)
    {

        positionloc = glGetUniformLocation(shader.ID,"spotlight.position");
        directionloc = glGetUniformLocation(shader.ID,"spotlight.direction");
        ambientloc = glGetUniformLocation(shader.ID,"spotlight.ambient");
        diffuseloc = glGetUniformLocation(shader.ID,"spotlight.diffuse");
        specularloc = glGetUniformLocation(shader.ID,"spotlight.specular");
        constantloc = glGetUniformLocation(shader.ID,"spotlight.constant");
        linearloc = glGetUniformLocation(shader.ID,"spotlight.linear");
        quadraticloc = glGetUniformLocation(shader.ID,"spotlight.quadratic");
        cutoffloc = glGetUniformLocation(shader.ID,"spotlight.cutoff");
        outercutoffloc = glGetUniformLocation(shader.ID,"spotlight.outercutoff");
        glUniform3f(positionloc,position.x,position.y,position.z);
        glUniform3f(directionloc,direction.x,direction.y,direction.z);
        glUniform3f(ambientloc,ambient.x,ambient.y,ambient.z);
        glUniform3f(diffuseloc,diffuse.x,diffuse.y,diffuse.z);
        glUniform3f(specularloc,specular.x,specular.y,specular.z);
        glUniform1f(constantloc,constant);
        glUniform1f(linearloc,linear);
        glUniform1f(quadraticloc,quadratic);
        glUniform1f(cutoffloc,glm::radians(cutoff));
        glUniform1f(outercutoffloc,glm::radians(outercutoff));
    }


void SpotLight::setPosition(glm::vec3 position)
{
    glUniform3f(positionloc,position.x,position.y,position.z);
}
void SpotLight::setDirection(glm::vec3 direction)
{
    glUniform3f(directionloc,direction.x,direction.y,direction.z);
}
void SpotLight::setAmbient(glm::vec3 ambient)
{
    glUniform3f(ambientloc,ambient.x,ambient.y,ambient.z);
}
void SpotLight::setDiffuse(glm::vec3 diffuse)
{
    glUniform3f(diffuseloc,diffuse.x,diffuse.y,diffuse.z);
}
void SpotLight::setSpecular(glm::vec3 specular)
{
    glUniform3f(specularloc,specular.x,specular.y,specular.z);
}
void SpotLight::setConstant(float constant)
{
    glUniform1f(constantloc,constant);
}
void SpotLight::setLinear(float linear)
{
    glUniform1f(linearloc,linear);
}
void SpotLight::setQuadratic(float quadratic)
{
    glUniform1f(quadraticloc,quadratic);
}
void SpotLight::setCutoff(float cutoff)
{
    glUniform1f(cutoffloc,glm::radians(cutoff));
}
void SpotLight::setOuterCutoff(float outercutoff)
{
    glUniform1f(outercutoffloc,glm::radians(outercutoff));
}*/
