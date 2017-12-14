#ifndef CYLINDER_H
#define CYLINDER_H

//#include "openglshape.h"
#include "../../gl/shaders/ShaderAttribLocations.h"
#include "flatbottomcurveshape.h"

class Cylinder : public FlatBottomCurveShape
{
public:
    Cylinder();
    Cylinder(int p1, int p2);

    int calcVertices(int p1, int p2);
    void update(int p1, int p2);

private:
    int prev_p1;
    int prev_p2;
    std::vector<float> tempV;
    void addNormal(float deg, std::vector<float>& vertices);
    void addUV(float theta, float y, std::vector<float>& vertices);

};

#endif // CYLINDER_H
