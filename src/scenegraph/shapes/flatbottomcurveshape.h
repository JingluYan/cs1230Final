#ifndef FLATBOTTOMSHAPE_H
#define FLATBOTTOMSHAPE_H
#include "openglshape.h"

class FlatBottomCurveShape : public OpenGLShape
{
public:
    FlatBottomCurveShape();
    int calcBottom(int p1, int p2, float y, std::vector<float>& vertices, bool up);
    void addUV(float x, float z, std::vector<float>& vertices);
protected:
    const float r; //radius
};

#endif // FLATBOTTOMSHAPE_H
