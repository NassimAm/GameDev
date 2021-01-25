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
#include "Terrain.h"

Terrain::Terrain(int gridX,int gridZ,Loader loader,TerrainTexturePack texturepack,TerrainTexture blendMap,std::string HeightMap,std::string SaveFile)
{
    this->texturepack = texturepack;
    this->blendMap = blendMap;
    this->SaveFile = SaveFile;
    x = gridX * Size - Size/2;
    z = gridZ * Size - Size/2;
    TestSave(saved);
    if(!saved)
        generateTerrain(loader,HeightMap);
    else
        loadSave(loader);
}

float Terrain::getX()
{
    return x;
}

float Terrain::getZ()
{
    return z;
}

RawModel Terrain::getModel()
{
    return model;
}

TerrainTexturePack Terrain::getTexturePack()
{
    return texturepack;
}
TerrainTexture Terrain::getBlendMap()
{
    return blendMap;
}

float Terrain::getTerrainHeight(float worldX,float worldZ)
{
    float TerrainX = worldX - x;
    float TerrainZ = worldZ - z;
    float GridSquareSize = Size/((float)(VERTEX_COUNT-1.0f));
    int GridX = (int)(TerrainX/GridSquareSize);
    int GridZ = (int)(TerrainZ/GridSquareSize);
    if(GridX<0||GridZ<0||GridX>=VERTEX_COUNT-1.0f||GridZ>=VERTEX_COUNT-1.0f)
        return 0;
    float xCoord = (TerrainX - GridX * GridSquareSize)/GridSquareSize;
    float zCoord = (TerrainZ - GridZ * GridSquareSize)/GridSquareSize;
    float answer;
    int pointer = GridZ*VERTEX_COUNT+GridX;
    if(xCoord>1.0f-zCoord)
    {
        answer = barryCentric(glm::vec3(0, heights[pointer], 0),glm::vec3(1,heights[pointer+1], 0),glm::vec3(0,heights[pointer+VERTEX_COUNT], 1),glm::vec2(xCoord, zCoord));
    }
    else
    {
        answer = barryCentric(glm::vec3(0, heights[pointer+1], 0),glm::vec3(1,heights[pointer+1+VERTEX_COUNT], 0),glm::vec3(0,heights[pointer+VERTEX_COUNT], 1),glm::vec2(xCoord, zCoord));
    }
    return answer;
}

void Terrain::generateTerrain(Loader loader,std::string HeightMap)
{
    PngImage h_image;
    std::vector<char> imageload(HeightMap.begin(), HeightMap.end());
    imageload.push_back('\0');
    h_image.loadImage(&imageload[0]);
    imageDim = h_image.getHeight();
    if(imageDim!=0)
    {
        VERTEX_COUNT = imageDim;
    }
    else if(imageDim == 0)
        std::cout<<"Height map not found at : "<<HeightMap<<std::endl;

    float height;
    std::vector<unsigned int> indices;
    for(unsigned int az=0;az<VERTEX_COUNT-1;az++)
    {
        for(unsigned int ax=0;ax<VERTEX_COUNT-1;ax++)
        {
                int topLeft = (az*VERTEX_COUNT)+ax;
                int topRight = topLeft + 1;
                int bottomLeft = ((az+1)*VERTEX_COUNT)+ax;
                int bottomRight = bottomLeft + 1;
                indices.push_back(topLeft);
                indices.push_back(bottomLeft);
                indices.push_back(topRight);
                indices.push_back(topRight);
                indices.push_back(bottomLeft);
                indices.push_back(bottomRight);
        }
    }
    unsigned int pointer = 0;
    std::vector<float> Pos;
    std::vector<float> Norm;
    std::vector<float> Text;
    for(unsigned int i=0;i<VERTEX_COUNT;i++)
    {
        for(unsigned int j=0;j<VERTEX_COUNT;j++)
        {
            Pos.push_back((float)j/((float)VERTEX_COUNT-1.0f)*Size);
            height = getHeight(j,i,h_image);
            Pos.push_back(height);
            Pos.push_back((float)i/((float)VERTEX_COUNT-1.0f)*Size);

            heights.push_back(height);

            glm::vec3 normal = CalculateNormal(j,i,h_image);
            Norm.push_back(normal.x);
            Norm.push_back(normal.y);
            Norm.push_back(normal.z);

            Text.push_back((float)j/((float)VERTEX_COUNT-1.0f));
            Text.push_back((float)i/((float)VERTEX_COUNT-1.0f));
            pointer++;
            std::cout<<(float)pointer/((float)(VERTEX_COUNT*VERTEX_COUNT))*100.0f<<" %"<<std::endl;
        }
    }
    std::cout<<Pos.size()<<" || "<<Norm.size()<<" || "<<Text.size()<<" || "<<indices.size()<<"\n";
    Save(Pos,Norm,Text,indices,heights,VERTEX_COUNT);
    model = loader.loadtoVAO(Pos,Norm,Text,indices);
}

float Terrain::getHeight(int x,int z,PngImage image)
{
    if(x<0 || x> image.getWidth() || z<0 || z>image.getHeight())
    {
        return 0;
    }
    int rComp,gComp,bComp;
    image.getRGB(x,z,rComp,gComp,bComp);
    float height = (rComp + gComp + bComp)/3.0f;
    height/=MAX_PIXEL_COLOR/2.0f;
    height-=1.0f;
    height*=MAX_HEIGHT;
    return height;
}

glm::vec3 Terrain::CalculateNormal(int x,int z,PngImage image)
{
    float HeightL = getHeight(x-1,z,image);
    float HeightR = getHeight(x+1,z,image);
    float HeightD = getHeight(x,z-1,image);
    float HeightU = getHeight(x,z+1,image);
    glm::vec3 normal = glm::vec3(HeightL-HeightR,2.0f,HeightD-HeightU);
    glm::normalize(normal);
    return normal;
}

float Terrain::barryCentric(glm::vec3 p1,glm::vec3 p2,glm::vec3 p3,glm::vec2 pos)
{
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
    float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    float l3 = 1.0f - l1 - l2;
    return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

void Terrain::TestSave(bool &save)
{
    std::ifstream inFile;
    inFile.open(SaveFile);
    std::string input;
    std::getline(inFile,input);
    if(input.empty())
        save = false;
    else
        save = true;

    inFile.close();
}

void Terrain::Save(std::vector<float> vec1,std::vector<float> vec2,std::vector<float> vec3,std::vector<unsigned int> vec4,std::vector<float> vec5,unsigned int vertexcount)
{
    std::ofstream outputfile;
    outputfile.open(SaveFile);
    std::string enteredinput;
    enteredinput = "V"+std::to_string(vertexcount)+" ";
    outputfile<<enteredinput;
    for(unsigned int i=0;i<vec1.size();i++)
    {
        enteredinput = std::to_string(vec1[i]);
        enteredinput+=" ";
        outputfile<<enteredinput;
    }
    enteredinput = "; ";
    outputfile<<enteredinput;
    for(unsigned int i=0;i<vec2.size();i++)
    {
        enteredinput = std::to_string(vec2[i]);
        enteredinput+=" ";
        outputfile<<enteredinput;
    }
    enteredinput = "; ";
    outputfile<<enteredinput;
    for(unsigned int i=0;i<vec3.size();i++)
    {
        enteredinput = std::to_string(vec3[i]);
        enteredinput+=" ";
        outputfile<<enteredinput;
    }
    enteredinput = "; ";
    outputfile<<enteredinput;
    for(unsigned int i=0;i<vec4.size();i++)
    {
        enteredinput = std::to_string(vec4[i]);
        enteredinput+=" ";
        outputfile<<enteredinput;
    }
    enteredinput = "; ";
    outputfile<<enteredinput;
    for(unsigned int i=0;i<vec5.size();i++)
    {
        enteredinput = std::to_string(vec5[i]);
        enteredinput+=" ";
        outputfile<<enteredinput;
    }
    enteredinput = "; ";
    outputfile<<enteredinput;
    outputfile.close();
}

void Terrain::loadSave(Loader loader)
{
    std::vector<float> vec1;
    std::vector<float> vec2;
    std::vector<float> vec3;
    std::vector<unsigned int> vec4;
    std::vector<float> vec5;
    unsigned int storedvertexcount;

    bool stop1 = false;
    bool stop2 = false;
    bool act2 = false;
    bool stop3 = false;
    bool act3 = false;
    bool stop4 = false;
    bool act4 = false;
    bool stop5 = false;
    bool act5 = false;
    std::ifstream inFile;
    inFile.open(SaveFile);
    std::stringstream s;
    s<<inFile.rdbuf();
    std::string newstring;
    int pointer = 0;
    int oldpointer = 0;
    while(s>>newstring)
    {
        if(newstring[0]!='V')
        {
            pointer++;
            //vec1
            if(!stop1)
            {
                if(newstring == ";")
                {
                    stop1 = true;
                    act2 = true;
                    oldpointer = pointer;
                }
                else
                {
                    float numb = std::stof(newstring);
                    vec1.push_back(numb);
                }

            }
            //vec2

            if(!stop2&&act2&&pointer!=oldpointer)
            {
                if(newstring == ";")
                {
                    stop2 = true;
                    act3 = true;
                    oldpointer = pointer;
                }
                else
                {
                    float numb = std::stof(newstring);
                    vec2.push_back(numb);
                }

            }
            //vec3
            if(!stop3&&act3&&pointer!=oldpointer)
            {
                if(newstring == ";")
                {
                    stop3 = true;
                    act4 = true;
                    oldpointer = pointer;
                }
                else
                {
                    float numb = std::stof(newstring);
                    vec3.push_back(numb);
                }

            }
            //vec4
            if(!stop4&&act4&&pointer!=oldpointer)
            {
                if(newstring == ";")
                {
                    stop4 = true;
                    act5 = true;
                    oldpointer = pointer;
                }
                else
                {
                    unsigned int numb = std::stoul(newstring,nullptr,0);
                    vec4.push_back(numb);
                }
            }
            //vec5
            if(!stop5&&act5&&pointer!=oldpointer)
            {
                if(newstring == ";")
                {
                    stop5 = true;
                    oldpointer = pointer;
                }
                else
                {
                    float numb = std::stof(newstring);
                    vec5.push_back(numb);
                }
            }
        }
        else
        {
            newstring.erase(newstring.begin());
            storedvertexcount = std::stoul(newstring,nullptr,0);
        }

    }

    VERTEX_COUNT = storedvertexcount;
    heights = vec5;
    model = loader.loadtoVAO(vec1,vec2,vec3,vec4);
}

