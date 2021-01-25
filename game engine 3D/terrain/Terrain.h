#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "../pngLoader/pngImage.h"
#include "../model/Rawmodel.h"
#include "../texture/Terraintexture.h"
#include "../texture/TerraintexturePack.h"
#include "../render_engine/Loader.h"

class Terrain
{
    public:
        Terrain(int gridX,int gridZ,Loader loader,TerrainTexturePack texturepack,TerrainTexture blendMap,std::string HeightMap,std::string SaveFile);
        float getX();
        float getZ();
        RawModel getModel();
        TerrainTexturePack getTexturePack();
        TerrainTexture getBlendMap();
        float getTerrainHeight(float worldX,float worldZ);

    private:
        const float Size = 50;
        unsigned int VERTEX_COUNT;
        const float MAX_HEIGHT = 20.0f;
        const float MAX_PIXEL_COLOR = 256;
        unsigned int imageDim;
        float x,z;
        std::vector<float> heights;
        bool saved;
        std::string SaveFile;

        RawModel model;
        TerrainTexturePack texturepack;
        TerrainTexture blendMap;

        void generateTerrain(Loader loader,std::string HeightMap);
        float getHeight(int x,int z,PngImage image);
        glm::vec3 CalculateNormal(int x,int z,PngImage image);
        float barryCentric(glm::vec3 p1,glm::vec3 p2,glm::vec3 p3,glm::vec2 pos);
        void TestSave(bool &save);
        void Save(std::vector<float> vec1,std::vector<float> vec2,std::vector<float> vec3,std::vector<unsigned int> vec4,std::vector<float> vec5,unsigned int vertexcount);
        void loadSave(Loader loader);

};

#endif // TERRAIN_H_INCLUDED
