#ifndef FLATBOTTOMSHAPE_H
#define FLATBOTTOMSHAPE_H
#include "openglshape.h"

class FlatBottomCurveShape : public OpenGLShape
{
public:
    FlatBottomCurveShape();
    int calcBottom(int p1, int p2, float y, std::vector<float>& vertices, bool up);
    bool intersect(glm::vec3 &eye, glm::vec3 &ray, double &t) = 0;

protected:
    const float r; //radius
};

#endif // FLATBOTTOMSHAPE_H
