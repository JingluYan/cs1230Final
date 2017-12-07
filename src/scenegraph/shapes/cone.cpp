#include "cone.h"
#include <math.h>
#include <iostream>
using namespace std;

Cone::Cone() :
    r(.5f),
    slope(2.0f)
{
}


Cone::Cone(int p1, int p2) :
    r(.5f),
    slope(2.0f)
{
    update(p1, p2);
}


int Cone::calcVertices(int p1, int p2) {
    v.clear();
    int count = 0;
    p2 = p2 < 3 ? 3 : p2;
    float d_theta = 2 * 3.1415 / p2; //delta theta in radian
    float y_seg_len = 1.0f / p1;
    for (int i = 0; i < p1; i++) {
        for (int j = 0; j <= p2; j++) {
            float rc = i * y_seg_len * (1.0f / slope);
            //add position
            v.push_back(rc * cosf(-j * d_theta));
            v.push_back(0.5f - i * y_seg_len);
            v.push_back(rc * sinf(-j * d_theta));

            //add normal
            float h_component = 2 / sqrt(5);
            float v_componet = 1 / sqrt(5);
            v.push_back(h_component * cosf(-j * d_theta));
            v.push_back(v_componet);
            v.push_back(h_component * sinf(-j * d_theta));

            //add uv
            addUV(-j * d_theta, 0.5f - i * y_seg_len, v);

            // vertex below
            float rn = (i + 1) * y_seg_len * (1 / slope);
            //add position
            v.push_back(rn * cosf(-j * d_theta));
            v.push_back(0.5f - (i + 1) * y_seg_len);
            v.push_back(rn * sinf(-j * d_theta));

            //add normal
            v.push_back(h_component * cosf(-j * d_theta));
            v.push_back(v_componet);
            v.push_back(h_component * sinf(-j * d_theta));

            //add uv
            addUV(-j * d_theta, 0.5f - (i + 1) * y_seg_len, v);

            count += 2;
        }
    }
    //add a center point, otherwise the bot face will flip
    v.push_back(0.0f);
    v.push_back(-0.5f);
    v.push_back(0.0f);
    //normal
    v.push_back(0.0f);
    v.push_back(-1.0f);
    v.push_back(0.0f);
    //uv
    v.push_back(0.5f);
    v.push_back(0.5f);
    count++;

    count += calcBottom(p1, p2, -.5f, v, true);

    return count;
}


void Cone::update(int p1, int p2) {
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
    setAttribute(CS123::GL::ShaderAttrib::TEXCOORD0, 2, 24, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    buildVAO();
}

void Cone::addUV(float theta, float y, std::vector<float> &vertices) {
    float v = y + 0.5f;
    float u = 0.f;
    u = theta < 0 ? u = -theta / (2 * M_PI) : u = 1 -theta / (2 * M_PI);
    vertices.push_back(u);
    vertices.push_back(v);
}
