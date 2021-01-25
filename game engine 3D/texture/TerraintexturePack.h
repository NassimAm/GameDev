#ifndef TERRAINTEXTUREPACK_H_INCLUDED
#define TERRAINTEXTUREPACK_H_INCLUDED

#include "Terraintexture.h"

class TerrainTexturePack
{
    public:
        TerrainTexturePack()
        {
            //Constructor
        }
        TerrainTexturePack(TerrainTexture backgroundTexture,TerrainTexture rTexture,TerrainTexture gTexture,TerrainTexture bTexture)
        {
            this->backgroundTexture = backgroundTexture;
            this->rTexture = rTexture;
            this->gTexture = gTexture;
            this->bTexture = bTexture;
        }
        TerrainTexture getBackgroundTexture()
        {
            return backgroundTexture;
        }
        TerrainTexture getrTexture()
        {
            return rTexture;
        }
        TerrainTexture getgTexture()
        {
            return gTexture;
        }
        TerrainTexture getbTexture()
        {
            return bTexture;
        }
    private:
        TerrainTexture backgroundTexture;
        TerrainTexture rTexture;
        TerrainTexture gTexture;
        TerrainTexture bTexture;
};


#endif // TERRAINTEXTUREPACK_H_INCLUDED
