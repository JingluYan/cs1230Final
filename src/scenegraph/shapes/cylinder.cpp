#include "cylinder.h"
#include <iostream>
#include <math.h>

using namespace std;

Cylinder::Cylinder()
//    r(0.5f)
{
}

Cylinder::Cylinder(int p1, int p2)
//    r(0.5f)
{
    update(p1, p2);
}

int Cylinder::calcVertices(int p1, int p2) {
    v.clear();
    p2 = p2 < 3 ? 3 : p2;
    int count = 0;
    //calc side
    for (float i = 0; i < p1; i++) {
        float deg = 360.0f;
        for (int j = 0; j <= p2; j++) {
            deg -= 360 / static_cast<float>(p2);
            float rad = deg * M_PI / 180;
            //upper
            v.push_back(r * cos(rad));
            v.push_back(0.5f - i / p1);
            v.push_back( r * sin(rad));
            addNormal(rad, v);

            //lower point
            v.push_back(r * cos(rad));
            v.push_back(0.5f - (i + 1) / p1);
            v.push_back( r * sin(rad));
            addNormal(rad, v);
            count += 2;
        }
    }

    std::vector<float> tmp = {0.0f, -.5f, 0.0f, 0.0f, -1.0f, 0.0f};
    v.insert(v.end(), tmp.begin(), tmp.end());
    count++;

    count += calcBottom(p1, p2, -.5f, v, true);
    count += calcBottom(p1, p2, 0.5f, v, false);
    return count;
}

void Cylinder::update(int p1, int p2) {
    if (prev_p1 == p1 && prev_p2 == p2) {
        return;
    } else {
        prev_p1 = p1;
        prev_p2 = p2;
    }
    int vertexCount = calcVertices(p1, p2);
    setVertexData(&v[0], v.size(),VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP, vertexCount);
    setAttribute(CS123::GL::ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    setAttribute(CS123::GL::ShaderAttrib::NORMAL, 3, 3*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    buildVAO();
}


void Cylinder::addNormal(float deg, std::vector<float> &vertices) {
    vertices.push_back(cos(deg));
    vertices.push_back(0);
    vertices.push_back(sin(deg));
}


bool Cylinder::intersect(glm::vec3 &eye, glm::vec3 &ray, double &t) {

    return false;
}
