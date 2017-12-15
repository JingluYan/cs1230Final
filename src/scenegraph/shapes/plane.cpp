#include "plane.h"
#include <iostream>
#include <cmath>

Plane::Plane()
{
    Plane(0);
}

Plane::Plane(int tess) :
    prevTess(0)
{
    update(tess);
}

void Plane::update(int tess) {
    if (prevTess == tess || tess == 0) {
        return;
    }
    prevTess = tess;
    calcVertex(tess);
    int faceNum = 1;
    int vertexCount = std::pow(tess, 2) * 2 * 3 * faceNum;
    setVertexData(&v[0], v.size(),VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, vertexCount);
    setAttribute(CS123::GL::ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    setAttribute(CS123::GL::ShaderAttrib::NORMAL, 3, 3*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    setAttribute(CS123::GL::ShaderAttrib::TEXCOORD0, 2, 6*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    setAttribute(CS123::GL::ShaderAttrib::TANGENT, 3, 8*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    setAttribute(CS123::GL::ShaderAttrib::BINORMAL, 3, 11*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    buildVAO();
}

void Plane::calcVertex(int tess) {
    v.clear();
    float seg = static_cast<float>(tess);
    //front face
    for (int i = 0; i < tess; i++) {
        for (int j = 0; j < tess; j++) {
            glm::vec3 normal = {0.0f, 0.0f, 1.0f};
            //upper triangle
            glm::vec3 v1pos = {-.5f + j / seg, -.5f + i / seg, .5f};
            glm::vec2 v1uv = {j / seg, i / seg};
            glm::vec3 v2pos = {-.5f + (j + 1) / seg, -.5f + (i + 1) / seg, .5f};
            glm::vec2 v2uv = {(j + 1) / seg, (i + 1) / seg};
            glm::vec3 v3pos = {-.5f + j / seg, -.5f + (i + 1) / seg , .5f};
            glm::vec2 v3uv = {j / seg, (i + 1) / seg};
            add3VertexInV(v, v1pos, normal, v1uv, v2pos, normal, v2uv, v3pos, normal, v3uv);

            //lower triangle
            v1pos = {-.5f + j / seg, -.5f + i / seg , .5f};
            v1uv = {j / seg, i / seg};
            v2pos = {-.5f + (j + 1) / seg , -.5f + i / seg, .5f};
            v2uv = {(j + 1) / seg, i / seg};
            v3pos = {-.5f + (j + 1) / seg, -.5f + (i + 1) / seg, .5f};
            v3uv = {(j + 1) / seg, (i + 1) / seg};
            add3VertexInV(v, v1pos, normal, v1uv, v2pos, normal, v2uv, v3pos, normal, v3uv);
        }
    }

}

