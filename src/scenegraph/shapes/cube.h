#ifndef CUBE_H
#define CUBE_H

#include "openglshape.h"
#include "../../gl/shaders/ShaderAttribLocations.h"

class Cube : public OpenGLShape
{
public:
    Cube(int tess = 1);

    void calcVertex(int tess);
    void update(int tess);

private:
    int prevTess; // previous tesselation
};

#endif // CUBE_H
