#ifndef TERRAINTEXTURE_H_INCLUDED
#define TERRAINTEXTURE_H_INCLUDED

class TerrainTexture
{
    public:
        TerrainTexture()
        {
            //Constructor
        }
        TerrainTexture(unsigned int textureID)
        {
            this->textureID = textureID;
        }
        unsigned int getID()
        {
            return textureID;
        }
    private:
        unsigned int textureID;
};

#endif // TERRAINTEXTURE_H_INCLUDED
