#ifndef SPHERE_H
#define SPHERE_H

#include "openglshape.h"
#include "../../gl/shaders/ShaderAttribLocations.h"


class Sphere : public OpenGLShape
{
public:
    Sphere(int p1 = 20, int p2 = 20);

    int calcVertices(int p1, int p2);
    void update(int p1, int p2);

private:
    const float r; //radius
    int prev_p1;
    int prev_p2;
    std::vector<float> tempV;
    void addNormal(float theta, float thai, std::vector<float>& vertices);
    void addUV(float theta, float y, std::vector<float>& vertices);
};

#endif // SPHERE_H
