#ifndef RAWMODEL_H_INCLUDED
#define RAWMODEL_H_INCLUDED

#include <iostream>

class RawModel
{
    public:
        RawModel()
        {

        }
        RawModel(unsigned int VaoID, unsigned int vertexCount)
        {
            this->VaoID = VaoID;
            this->vertexCount = vertexCount;
        }

        unsigned int getVaoID()
        {
            return VaoID;
        }

        unsigned int getVertexCount()
        {
            return vertexCount;
        }
    private:
        unsigned int VaoID;
        unsigned int vertexCount;
};

#endif // RAWMODEL_H_INCLUDED
