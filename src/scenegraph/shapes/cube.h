#ifndef CUBE_H
#define CUBE_H

#include "openglshape.h"
#include "../../gl/shaders/ShaderAttribLocations.h"

class Cube : public OpenGLShape
{
public:
    Cube();
    Cube(int tess);

    void calcVertex(int tess);
    void update(int tess);
    void addVertex(std::vector<float> vertex, std::vector<float>& vertices);
    void addglmVec3ToVector(glm::vec3 src, std::vector<float>& dest);
    void addglmVec2ToVector(glm::vec2 src, std::vector<float>& dest);

private:
    int prevTess; // previous tesselation
};

#endif // CUBE_H
