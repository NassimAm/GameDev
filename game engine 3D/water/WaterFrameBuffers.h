#ifndef WATERFRAMEBUFFERS_H_INCLUDED
#define WATERFRAMEBUFFERS_H_INCLUDED

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class WaterFrameBuffers
{

    public:

        WaterFrameBuffers();
        WaterFrameBuffers(unsigned int SCR_WIDTH,unsigned int SCR_HEIGHT);
        void cleanUp();
        void bindReflectionFrameBuffer();
        void bindRefractionFrameBuffer();
        void unbindCurrentFrameBuffer(unsigned int SCR_WIDTH,unsigned int SCR_HEIGHT);
        unsigned int getReflectionTexture();
        unsigned int getRefractionTexture();
        unsigned int getRefractionDepthTexture();

	private:

        unsigned int REFLECTION_WIDTH = 320;
        unsigned int REFLECTION_HEIGHT = 180;

        unsigned int REFRACTION_WIDTH = 1280;
        unsigned int REFRACTION_HEIGHT = 720;

        unsigned int reflectionFrameBuffer;
        unsigned int reflectionTexture;
        unsigned int reflectionDepthBuffer;

        unsigned int refractionFrameBuffer;
        unsigned int refractionTexture;
        unsigned int refractionDepthTexture;

        void initialiseReflectionFrameBuffer(unsigned int SCR_WIDTH,unsigned int SCR_HEIGHT);
        void initialiseRefractionFrameBuffer(unsigned int SCR_WIDTH,unsigned int SCR_HEIGHT);
        void bindFrameBuffer(unsigned int frameBuffer,unsigned int width,unsigned int height);
        unsigned int createFrameBuffer();
        unsigned int createTextureAttachment(unsigned int width,unsigned int height);
        unsigned int createDepthTextureAttachment(unsigned int width,unsigned int height);
        unsigned int createDepthBufferAttachment(unsigned int width,unsigned int height);
};

#endif // WATERFRAMEBUFFERS_H_INCLUDED
