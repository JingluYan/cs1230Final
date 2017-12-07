#include "cube.h"
#include <iostream>
#include <cmath>

Cube::Cube()
{
    Cube(0);
}

Cube::Cube(int tess) :
    prevTess(0)
{
    update(tess);
}

void Cube::update(int tess) {
    if (prevTess == tess || tess == 0) {
        return;
    }
    prevTess = tess;
    calcVertex(tess);
    int faceNum = 6;
    int vertexCount = std::pow(tess, 2) * 2 * 3 * faceNum;
    setVertexData(&v[0], v.size(),VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, vertexCount);
    setAttribute(CS123::GL::ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    setAttribute(CS123::GL::ShaderAttrib::NORMAL, 3, 3*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    setAttribute(CS123::GL::ShaderAttrib::TEXCOORD0, 2, 24, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    buildVAO();
}

void Cube::calcVertex(int tess) {
    v.clear();
    float seg = static_cast<float>(tess);
    std::vector<float> tmp;
    //front face
    for (int i = 0; i < tess; i++) {
        for (int j = 0; j < tess; j++) {
            //upper triangle    }
            tmp = {-.5f + j / seg, -.5f + i / seg, .5f,
                  0.0f, 0.0f, 1.0f,
                   j / seg, i / seg};
            addVertex(tmp, v);

            tmp = {-.5f + (j + 1) / seg, -.5f + (i + 1) / seg, .5f,
                  0.0f, 0.0f, 1.0f,
                   (j + 1) / seg, (i + 1) / seg};
            addVertex(tmp, v);

            tmp = {-.5f + j / seg, -.5f + (i + 1) / seg , .5f,
                  0.0f, 0.0f, 1.0f,
                   j / seg, (i + 1) / seg};
            addVertex(tmp, v);

            //lower triangle
            tmp = {-.5f + j / seg, -.5f + i / seg , .5f,
                  0.0f, 0.0f, 1.0f,
                   j / seg, i / seg};
            addVertex(tmp, v);

            tmp = {-.5f + (j + 1) / seg , -.5f + i / seg, .5f,
                  0.0f, 0.0f, 1.0f,
                   (j + 1) / seg, i / seg};
            addVertex(tmp, v);

            tmp = { -.5f + (j + 1) / seg, -.5f + (i + 1) / seg, .5f,
                  0.0f, 0.0f, 1.0f,
                    (j + 1) / seg, (i + 1) / seg};
            addVertex(tmp, v);

        }
    }

    //back face
    for (int i = 0; i < tess; i++) {
        for (int j = 0; j < tess; j++) {
            //upper triangle
            tmp = { .5f - j / seg, -.5f + i / seg, -.5f,
                  0.0f, 0.0f, -1.0f,
                    - j / seg, i / seg};
            addVertex(tmp, v);

            tmp = { .5f - (j + 1) / seg, -.5f + (i + 1) / seg, -.5f,
                  0.0f, 0.0f, -1.0f,
                    - (j + 1) / seg, + (i + 1) / seg};
            addVertex(tmp, v);

            tmp = { .5f - j / seg, -.5f + (i + 1) / seg, -.5f,
                  0.0f, 0.0f, -1.0f,
                    - j / seg, (i + 1) / seg};
            addVertex(tmp, v);

            //lower triangle
            tmp = { .5f - j / seg, -.5f + i / seg, -.5f,
                  0.0f, 0.0f, -1.0f,
                    - j / seg, i / seg};
            addVertex(tmp, v);

            tmp = { .5f - (j + 1) / seg, -.5f + i / seg, -.5f,
                  0.0f, 0.0f, -1.0f,
                    - (j + 1) / seg, i / seg};
            addVertex(tmp, v);

            tmp = {.5f - (j + 1) / seg, -.5f + (i + 1) / seg, -.5f,
                  0.0f, 0.0f, -1.0f,
                   - (j + 1) / seg, (i + 1) / seg};
            addVertex(tmp, v);

        }
    }

    //right face
    for (int i = 0; i < tess; i++) {
        for (int j = 0; j < tess; j++) {
            //upper triangle
            tmp = {.5f, -.5f + j / seg, -.5f + i / seg,
                  1.0f, 0.0f, 0.0f,
                   -(j / seg), - i / seg};
            addVertex(tmp, v);

            tmp = {.5f, -.5f + (j + 1) / seg, -.5f + (i + 1) / seg,
                  1.0f, 0.0f, 0.0f,
                   -(j + 1) / seg, - (i + 1) / seg};
            addVertex(tmp, v);

            tmp = {.5f, -.5f + j / seg, -.5f + (i + 1) / seg,
                  1.0f, 0.0f, 0.0f,
                  - j / seg, - (i + 1) / seg};
            addVertex(tmp, v);

            //lower triangle
            tmp = {.5f, -.5f + j / seg, -.5f + i / seg,
                  1.0f, 0.0f, 0.0f,
                  -j / seg, - i / seg};
            addVertex(tmp, v);

            tmp = {.5f, -.5f + (j + 1) / seg, -.5f + i / seg,
                  1.0f, 0.0f, 0.0f,
                  -(j + 1) / seg, - i / seg};
            addVertex(tmp, v);

            tmp = {.5f, -.5f + (j + 1) / seg, -.5f + (i + 1) / seg,
                  1.0f, 0.0f, 0.0f,
                  -(j + 1) / seg, -(i + 1) / seg};
            addVertex(tmp, v);

        }
    }


    //left face
    for (int i = 0; i < tess; i++) {
        for (int j = 0; j < tess; j++) {
            //upper triangle
            tmp = {-.5f, -.5f + i / seg, -.5f + j / seg,
                  -1.0f, 0.0f, 0.0f,
                  i / seg, j / seg};
            addVertex(tmp, v);

            tmp = {-.5f, -.5f + (i + 1) / seg, -.5f + (j + 1) / seg,
                  -1.0f, 0.0f, 0.0f,
                  (i + 1) / seg, (j + 1) / seg};
            addVertex(tmp, v);

            tmp = {-.5f, -.5f + (i + 1) / seg, -.5f + j / seg,
                  -1.0f, 0.0f, 0.0f,
                  (i + 1) / seg, j / seg};
            addVertex(tmp, v);

            //lower triangle
            tmp = {-.5f, -.5f + i / seg, -.5f + j / seg,
                  -1.0f, 0.0f, 0.0f,
                  i / seg, j / seg};
            addVertex(tmp, v);

            tmp = {-.5f, -.5f + i / seg, -.5f + (j + 1) / seg,
                  -1.0f, 0.0f, 0.0f,
                  i / seg, (j + 1) / seg};
            addVertex(tmp, v);

            tmp = {-.5f, -.5f + (i + 1) / seg, -.5f + (j + 1) / seg,
                  -1.0f, 0.0f, 0.0f,
                  (i + 1) / seg, (j + 1) / seg};
            addVertex(tmp, v);

        }
    }



    //bottom face
    for (int i = 0; i < tess; i++) {
        for (int j = 0; j < tess; j++) {
            //upper triangle
            tmp = { -.5f + j / seg, -.5f, -.5f + i / seg,
                  0.0f, -1.0f, 0.0f,
                    j / seg, i / seg};
            addVertex(tmp, v);

            tmp = { -.5f + (j + 1) / seg, -.5f, -.5f + (i + 1) / seg,
                  0.0f, -1.0f, 0.0f,
                  (j + 1) / seg, (i + 1) / seg};
            addVertex(tmp, v);

            tmp = { -.5f + j / seg, -.5f, -.5f + (i + 1) / seg,
                  0.0f, -1.0f, 0.0f,
                  j / seg, (i + 1) / seg};
            addVertex(tmp, v);

            //lower triangle
            tmp = { -.5f + j / seg, -.5f, -.5f + i / seg,
                  0.0f, -1.0f, 0.0f,
                  j / seg, i / seg};
            addVertex(tmp, v);

            tmp = { -.5f + (j + 1) / seg, -.5f, -.5f + i / seg,
                  0.0f, -1.0f, 0.0f,
                  (j + 1) / seg,  i / seg};
            addVertex(tmp, v);

            tmp = { -.5f + (j + 1) / seg, -.5f, -.5f + (i + 1) / seg,
                  0.0f, -1.0f, 0.0f,
                  (j + 1) / seg,  (i + 1) / seg};
            addVertex(tmp, v);


        }
    }


    //upper face
    for (int i = 0; i < tess; i++) {
        for (int j = 0; j < tess; j++) {
            //upper triangle
            tmp = { -.5f + j / seg, .5f, -.5f + i / seg,
                  0.0f, 1.0f, 0.0f,
                  i / seg, j / seg};
            addVertex(tmp, v);

            tmp = { -.5f + (j + 1) / seg, .5f, -.5f + (i + 1) / seg,
                  0.0f, 1.0f, 0.0f,
                  (i + 1) / seg, (j + 1) / seg};
            addVertex(tmp, v);

            tmp = { -.5f + (j + 1) / seg, .5f, -.5f + i / seg,
                  0.0f, 1.0f, 0.0f,
                  i / seg, (j + 1) / seg};
            addVertex(tmp, v);

            //lower triangle
            tmp = { -.5f + j / seg, .5f, -.5f + i / seg,
                  0.0f, 1.0f, 0.0f,
                  i / seg, j / seg};
            addVertex(tmp, v);

            tmp = { -.5f + j / seg, .5f, -.5f + (i + 1) / seg,
                  0.0f, 1.0f, 0.0f,
                  (i + 1) / seg, j / seg};
            addVertex(tmp, v);

            tmp = { -.5f + (j + 1) / seg, .5f, -.5f + (i + 1) / seg,
                  0.0f, 1.0f, 0.0f,
                  (i + 1) / seg, (j + 1) / seg};
            addVertex(tmp, v);

        }
    }
}

void Cube::addVertex(std::vector<float> vertex, std::vector<float>& vertices) {
    for (int i = 0; i < vertex.size(); i++) {
        vertices.push_back(vertex[i]);
    }
}
