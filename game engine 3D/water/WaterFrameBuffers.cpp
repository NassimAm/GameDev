
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "WaterFrameBuffers.h"

WaterFrameBuffers::WaterFrameBuffers()
{
    //Constructor
}
WaterFrameBuffers::WaterFrameBuffers(unsigned int SCR_WIDTH,unsigned int SCR_HEIGHT)
{
    //call when loading the game
    initialiseReflectionFrameBuffer(SCR_WIDTH,SCR_HEIGHT);
    initialiseRefractionFrameBuffer(SCR_WIDTH,SCR_HEIGHT);
}

void WaterFrameBuffers::cleanUp()
{
    //call when closing the game
    glDeleteFramebuffers(1,&reflectionFrameBuffer);
    glDeleteTextures(1,&reflectionTexture);
    glDeleteRenderbuffers(1,&reflectionDepthBuffer);
    glDeleteFramebuffers(1,&refractionFrameBuffer);
    glDeleteTextures(1,&refractionTexture);
    glDeleteTextures(1,&refractionDepthTexture);
}

void WaterFrameBuffers::bindReflectionFrameBuffer()
{
    //call before rendering to this FBO
    bindFrameBuffer(reflectionFrameBuffer,REFLECTION_WIDTH,REFLECTION_HEIGHT);
}

void WaterFrameBuffers::bindRefractionFrameBuffer()
{
    //call before rendering to this FBO
    bindFrameBuffer(refractionFrameBuffer,REFRACTION_WIDTH,REFRACTION_HEIGHT);
}

void WaterFrameBuffers::unbindCurrentFrameBuffer(unsigned int SCR_WIDTH,unsigned int SCR_HEIGHT)
{
    //call to switch to default frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

unsigned int WaterFrameBuffers::getReflectionTexture()
{
    //get the resulting texture
    return reflectionTexture;
}

unsigned int WaterFrameBuffers::getRefractionTexture()
{
    //get the resulting texture
    return refractionTexture;
}

unsigned int WaterFrameBuffers::getRefractionDepthTexture()
{
    //get the resulting depth texture
    return refractionDepthTexture;
}

void WaterFrameBuffers::initialiseReflectionFrameBuffer(unsigned int SCR_WIDTH,unsigned int SCR_HEIGHT)
{
    reflectionFrameBuffer = createFrameBuffer();
    reflectionTexture = createTextureAttachment(REFLECTION_WIDTH,REFLECTION_HEIGHT);
    reflectionDepthBuffer = createDepthBufferAttachment(REFLECTION_WIDTH,REFLECTION_HEIGHT);
    unbindCurrentFrameBuffer(SCR_WIDTH,SCR_HEIGHT);
}

void WaterFrameBuffers::initialiseRefractionFrameBuffer(unsigned int SCR_WIDTH,unsigned int SCR_HEIGHT)
{
    refractionFrameBuffer = createFrameBuffer();
    refractionTexture = createTextureAttachment(REFRACTION_WIDTH,REFRACTION_HEIGHT);
    refractionDepthTexture = createDepthTextureAttachment(REFRACTION_WIDTH,REFRACTION_HEIGHT);
    unbindCurrentFrameBuffer(SCR_WIDTH,SCR_HEIGHT);
}

void WaterFrameBuffers::bindFrameBuffer(unsigned int frameBuffer,unsigned int width,unsigned int height)
{
    glBindTexture(GL_TEXTURE_2D, 0);//To make sure the texture isn't bound
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glViewport(0, 0, width, height);
}

unsigned int WaterFrameBuffers::createFrameBuffer()
{
    unsigned int frameBuffer;
    glGenFramebuffers(1,&frameBuffer);
    //generate name for frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    //create the framebuffer
    return frameBuffer;
}

unsigned int WaterFrameBuffers::createTextureAttachment(unsigned int width,unsigned int height)
{
    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,texture, 0);
    return texture;
}

unsigned int WaterFrameBuffers::createDepthTextureAttachment(unsigned int width,unsigned int height)
{
    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height,0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,texture, 0);
    return texture;
}

unsigned int WaterFrameBuffers::createDepthBufferAttachment(unsigned int width,unsigned int height)
{
    unsigned int depthBuffer;
    glGenRenderbuffers(1,&depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width,height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER, depthBuffer);
    return depthBuffer;
}
