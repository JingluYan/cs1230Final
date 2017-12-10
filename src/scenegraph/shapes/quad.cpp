#include "quad.h"

Quad::Quad()
{
    v = { -1.0f,  1.0f,   0.0f, 1.0f,
          -1.0f, -1.0f,   0.0f, 0.0f,
           1.0f,  1.0f,   1.0f, 1.0f,
           1.0f, -1.0f,   1.0f, 0.0f };
    int vertexCount = v.size();
    setVertexData(&v[0], v.size(),VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP, vertexCount);
    setAttribute(CS123::GL::ShaderAttrib::POSITION, 2, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    setAttribute(CS123::GL::ShaderAttrib::TEXCOORD0, 2, 2*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    buildVAO();
}



