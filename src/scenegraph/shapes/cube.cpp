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
                  0.0f, 0.0f, 1.0f};
            addVertex(tmp, v);

            tmp = {-.5f + (j + 1) / seg, -.5f + (i + 1) / seg, .5f,
                  0.0f, 0.0f, 1.0f};
            addVertex(tmp, v);

            tmp = {-.5f + j / seg, -.5f + (i + 1) / seg , .5f,
                  0.0f, 0.0f, 1.0f};
            addVertex(tmp, v);

            //lower triangle
            tmp = {-.5f + j / seg, -.5f + i / seg , .5f,
                  0.0f, 0.0f, 1.0f};
            addVertex(tmp, v);

            tmp = {-.5f + (j + 1) / seg , -.5f + i / seg, .5f,
                  0.0f, 0.0f, 1.0f};
            addVertex(tmp, v);

            tmp = { -.5f + (j + 1) / seg, -.5f + (i + 1) / seg, .5f,
                  0.0f, 0.0f, 1.0f};
            addVertex(tmp, v);

        }
    }

    //back face
    for (int i = 0; i < tess; i++) {
        for (int j = 0; j < tess; j++) {
            //upper triangle
            tmp = { .5f - j / seg, -.5f + i / seg, -.5f,
                  0.0f, 0.0f, -1.0f};
            addVertex(tmp, v);

            tmp = { .5f - (j + 1) / seg, -.5f + (i + 1) / seg, -.5f,
                  0.0f, 0.0f, -1.0f};
            addVertex(tmp, v);

            tmp = { .5f - j / seg, -.5f + (i + 1) / seg, -.5f,
                  0.0f, 0.0f, -1.0f};
            addVertex(tmp, v);

            //lower triangle
            tmp = { .5f - j / seg, -.5f + i / seg, -.5f,
                  0.0f, 0.0f, -1.0f};
            addVertex(tmp, v);

            tmp = { .5f - (j + 1) / seg, -.5f + i / seg, -.5f,
                  0.0f, 0.0f, -1.0f};
            addVertex(tmp, v);

            tmp = {.5f - (j + 1) / seg, -.5f + (i + 1) / seg, -.5f,
                  0.0f, 0.0f, -1.0f};
            addVertex(tmp, v);

        }
    }

    //right face
    for (int i = 0; i < tess; i++) {
        for (int j = 0; j < tess; j++) {
            //upper triangle
            tmp = {.5f, -.5f + j / seg, -.5f + i / seg,
                  1.0f, 0.0f, 0.0f};
            addVertex(tmp, v);

            tmp = {.5f, -.5f + (j + 1) / seg, -.5f + (i + 1) / seg,
                  1.0f, 0.0f, 0.0f};
            addVertex(tmp, v);

            tmp = {.5f, -.5f + j / seg, -.5f + (i + 1) / seg,
                  1.0f, 0.0f, 0.0f};
            addVertex(tmp, v);

            //lower triangle
            tmp = {.5f, -.5f + j / seg, -.5f + i / seg,
                  1.0f, 0.0f, 0.0f};
            addVertex(tmp, v);

            tmp = {.5f, -.5f + (j + 1) / seg, -.5f + i / seg,
                  1.0f, 0.0f, 0.0f};
            addVertex(tmp, v);

            tmp = {.5f, -.5f + (j + 1) / seg, -.5f + (i + 1) / seg,
                  1.0f, 0.0f, 0.0f};
            addVertex(tmp, v);

        }
    }


    //left face
    for (int i = 0; i < tess; i++) {
        for (int j = 0; j < tess; j++) {
            //upper triangle
            tmp = {-.5f, -.5f + i / seg, -.5f + j / seg,
                  -1.0f, 0.0f, 0.0f};
            addVertex(tmp, v);

            tmp = {-.5f, -.5f + (i + 1) / seg, -.5f + (j + 1) / seg,
                  -1.0f, 0.0f, 0.0f};
            addVertex(tmp, v);

            tmp = {-.5f, -.5f + (i + 1) / seg, -.5f + j / seg,
                  -1.0f, 0.0f, 0.0f};
            addVertex(tmp, v);

            //lower triangle
            tmp = {-.5f, -.5f + i / seg, -.5f + j / seg,
                  -1.0f, 0.0f, 0.0f};
            addVertex(tmp, v);

            tmp = {-.5f, -.5f + i / seg, -.5f + (j + 1) / seg,
                  -1.0f, 0.0f, 0.0f};
            addVertex(tmp, v);

            tmp = {-.5f, -.5f + (i + 1) / seg, -.5f + (j + 1) / seg,
                  -1.0f, 0.0f, 0.0f};
            addVertex(tmp, v);

        }
    }



    //bottom face
    for (int i = 0; i < tess; i++) {
        for (int j = 0; j < tess; j++) {
            //upper triangle
            tmp = { -.5f + j / seg, -.5f, -.5f + i / seg,
                  0.0f, -1.0f, 0.0f};
            addVertex(tmp, v);

            tmp = { -.5f + (j + 1) / seg, -.5f, -.5f + (i + 1) / seg,
                  0.0f, -1.0f, 0.0f};
            addVertex(tmp, v);

            tmp = { -.5f + j / seg, -.5f, -.5f + (i + 1) / seg,
                  0.0f, -1.0f, 0.0f};
            addVertex(tmp, v);

            //lower triangle
            tmp = { -.5f + j / seg, -.5f, -.5f + i / seg,
                  0.0f, -1.0f, 0.0f};
            addVertex(tmp, v);

            tmp = { -.5f + (j + 1) / seg, -.5f, -.5f + i / seg,
                  0.0f, -1.0f, 0.0f};
            addVertex(tmp, v);

            tmp = { -.5f + (j + 1) / seg, -.5f, -.5f + (i + 1) / seg,
                  0.0f, -1.0f, 0.0f};
            addVertex(tmp, v);


        }
    }


    //upper face
    for (int i = 0; i < tess; i++) {
        for (int j = 0; j < tess; j++) {
            //upper triangle
            tmp = { -.5f + j / seg, .5f, -.5f + i / seg,
                  0.0f, 1.0f, 0.0f};
            addVertex(tmp, v);

            tmp = { -.5f + (j + 1) / seg, .5f, -.5f + (i + 1) / seg,
                  0.0f, 1.0f, 0.0f};
            addVertex(tmp, v);

            tmp = { -.5f + (j + 1) / seg, .5f, -.5f + i / seg,
                  0.0f, 1.0f, 0.0f};
            addVertex(tmp, v);

            //lower triangle
            tmp = { -.5f + j / seg, .5f, -.5f + i / seg,
                  0.0f, 1.0f, 0.0f};
            addVertex(tmp, v);

            tmp = { -.5f + j / seg, .5f, -.5f + (i + 1) / seg,
                  0.0f, 1.0f, 0.0f};
            addVertex(tmp, v);

            tmp = { -.5f + (j + 1) / seg, .5f, -.5f + (i + 1) / seg,
                  0.0f, 1.0f, 0.0f};
            addVertex(tmp, v);

        }
    }
}

void Cube::addVertex(std::vector<float> vertex, std::vector<float>& vertices) {
    for (int i = 0; i < vertex.size(); i++) {
        vertices.push_back(vertex[i]);
    }
}

//Need scale
bool Cube::intersect(glm::vec3 &eye, glm::vec3 &ray, double &t) {
    double px = static_cast<double>(eye.x);
    double py = static_cast<double>(eye.y);
    double pz = static_cast<double>(eye.z);

    double dx = static_cast<double>(ray.x);
    double dy = static_cast<double>(ray.y);
    double dz = static_cast<double>(ray.z);

    bool res = false;

    double t1 = (0.5f - px) / dx;
    if ( (py + t1*dy - 0.5f) <= EPSILON && (py + t1*dy + 0.5f) >= EPSILON
         && (pz + t1*dz - 0.5f) <= EPSILON && (pz + t1*dz + 0.5f) >= EPSILON) {
        t = std::min(t, t1);
        res = true;
    }

    double t2 = (-0.5f - px) / dx;
    if ( (py + t2*dy - 0.5f) <= EPSILON && (py + t2*dy + 0.5f) >= EPSILON
         && (pz + t2*dz - 0.5f) <= EPSILON && (pz + t2*dz + 0.5f) >= EPSILON) {
        t = std::min(t, t2);
        res = true;
    }

    double t3 = (0.5f - py) / dy;
    if ( (px + t3*dx - 0.5f) <= EPSILON && (px + t3*dx + 0.5f) >= EPSILON
         && (pz + t3*dz - 0.5f) <= EPSILON && (pz + t3*dz + 0.5f) >= EPSILON) {
        t = std::min(t, t2);
        res = true;
    }

    double t4 = (-0.5f - py) / dy;
    if ( (px + t4*dx - 0.5f) <= EPSILON && (px + t4*dx + 0.5f) >= EPSILON
         && (pz + t4*dz - 0.5f) <= EPSILON && (pz + t4*dz + 0.5f) >= EPSILON) {
        t = std::min(t, t2);
        res = true;
    }

    return res;
}

