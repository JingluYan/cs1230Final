#include "quad.h"

Quad::Quad()
{
    v = {-1.f, 1.f, .0f, .0f, .0f,
         -1.f, -1.f, .0f, .0f, 1.f,
         1.f, 1.f, .0f, 1.f, .0f,
         1.f, -1.f, .0f, 1.f, 1.f};
    int vertexCount = v.size();
    setVertexData(&v[0], v.size(),VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP, vertexCount);
    setAttribute(CS123::GL::ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    setAttribute(CS123::GL::ShaderAttrib::NORMAL, 3, 3*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    setAttribute(CS123::GL::ShaderAttrib::TEXCOORD0, 2, 6*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    buildVAO();
}



