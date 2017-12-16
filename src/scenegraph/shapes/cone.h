#ifndef CONE_H
#define CONE_H

//#include "openglshape.h"
#include "../../gl/shaders/ShaderAttribLocations.h"
#include "flatbottomcurveshape.h"

class Cone : public FlatBottomCurveShape
{
public:
    Cone(int p1 = 1, int p2 = 20);

    int calcVertices(int p1, int p2);
    void update(int p1, int p2);

private:
    const float r; //radius
    const float slope; //slope
    int prev_p1;
    int prev_p2;
    std::vector<float> tempV;
    void addUV(float theta, float y, std::vector<float>& vertices);
};

#endif // CONE_H
