#ifndef SPHERE_H
#define SPHERE_H

#include "openglshape.h"
#include "../../gl/shaders/ShaderAttribLocations.h"


class Sphere : public OpenGLShape
{
public:
    Sphere();
    Sphere(int p1, int p2);

    int calcVertices(int p1, int p2);
    void update(int p1, int p2);
    bool intersect(glm::vec3 &eye, glm::vec3 &ray, double &t);

private:
    const float r; //radius
    int prev_p1;
    int prev_p2;
    void addNormal(float theta, float thai, std::vector<float>& vertices);
};

#endif // SPHERE_H
