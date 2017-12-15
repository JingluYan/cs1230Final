#ifndef PLANE_H
#define PLANE_H

#include "openglshape.h"
#include "../../gl/shaders/ShaderAttribLocations.h"

class Plane : public OpenGLShape
{
public:
    Plane();
    Plane(int tess);

    void calcVertex(int tess);
    void update(int tess);

private:
    int prevTess; // previous tesselation
};

#endif // PLANE_H
