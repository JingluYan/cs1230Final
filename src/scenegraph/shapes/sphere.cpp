#include "sphere.h"
#include <math.h>
#include <iostream>
#include <iomanip>
using namespace std;

Sphere::Sphere() :
    r(0.5f)
{
}

Sphere::Sphere(int p1, int p2) :
    r(0.5f)
{
    update(p1, p2);
}

int Sphere::calcVertices(int p1, int p2) {
    v.clear();
    int count = 0;
    p2 = p2 < 3 ? 3 : p2;
    p1 = p1 < 2 ? 2 : p1;

    float d_phai = M_PI / p1; //delta phai
    float d_theta = 2 * M_PI / p2; //delta theta

    for (int i = 0; i < p1; i++) { //tess
        for (int j = 0; j <= p2; j++) { //round
            v.push_back(r * sinf(i * d_phai) * cosf(-j * d_theta));
            v.push_back(r * cosf(i * d_phai));
            v.push_back(r * sinf(i * d_phai) * sinf(-j * d_theta));
            addNormal(-j * d_theta, i * d_phai, v);
            addUV(-j * d_theta, r * cosf(i * d_phai), v);

            v.push_back(r * sinf((i + 1) * d_phai) * cosf(-j * d_theta));
            v.push_back(r * cosf((i + 1) * d_phai));
            v.push_back(r * sinf((i + 1) * d_phai) * sinf(-j * d_theta));
            addNormal(-j * d_theta, (i + 1) * d_phai, v);
            addUV(-j * d_theta, r * cosf((i + 1) * d_phai), v);

            count += 2;
        }
    }

    return count;
}

void Sphere::update(int p1, int p2) {
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
    setAttribute(CS123::GL::ShaderAttrib::TEXCOORD0, 2, 6*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    buildVAO();
}

void Sphere::addNormal(float theta, float phai, std::vector<float> &vertices) {
    vertices.push_back(sinf(phai) * cosf(theta));
    vertices.push_back(cosf(phai));
    vertices.push_back(sinf(phai) * sinf(theta));
}

void Sphere::addUV(float theta, float y, std::vector<float> &vertices) {
    float radius = .5f;
    float u = 0.f;
    u = theta < 0 ? u = -theta / (2 * M_PI) : u = 1 -theta / (2 * M_PI);
    float v = asin(y/ radius)/M_PI + 0.5;
    vertices.push_back(u);
    vertices.push_back(v);
}
