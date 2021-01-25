#ifndef WATERPLANE_H_INCLUDED
#define WATERPLANE_H_INCLUDED

class WaterPlane
{
    public:
        WaterPlane()
        {
            //Constructor
        }
        WaterPlane(float x,float z,float level,float watersize)
        {
            this->x = x;
            this->z = z;
            this->level = level;
            this->watersize = watersize;
        }

        float getX()
        {
            return x;
        }
        float getZ()
        {
            return z;
        }
        float getLevel()
        {
            return level;
        }
        float getSize()
        {
            return watersize;
        }

        void setX(float x)
        {
            this->x = x;
        }
        void setZ(float z)
        {
            this->z = z;
        }
        void setLevel(float level)
        {
            this->level = level;
        }
        void setSize(float watersize)
        {
            this->watersize = watersize;
        }
    private:
        float x;
        float z;
        float level;
        float watersize;
};

#endif // WATERPLANE_H_INCLUDED
