#include "cone.h"
#include <math.h>
#include <iostream>
using namespace std;

Cone::Cone(int p1, int p2) :
    r(.5f),
    slope(2.0f)
{
    update(p1, p2);
}


int Cone::calcVertices(int p1, int p2) {
    tempV.clear();
    int count = 0;
    p2 = p2 < 3 ? 3 : p2;
    float d_theta = 2 * 3.1415 / p2; //delta theta in radian
    float y_seg_len = 1.0f / p1;
    for (int i = 0; i < p1; i++) {
        for (int j = 0; j <= p2; j++) {
            float rc = i * y_seg_len * (1.0f / slope);
            //add position
            tempV.push_back(rc * cosf(-j * d_theta));
            tempV.push_back(0.5f - i * y_seg_len);
            tempV.push_back(rc * sinf(-j * d_theta));

            //add normal
            float h_component = 2 / sqrt(5);
            float v_componet = 1 / sqrt(5);
            tempV.push_back(h_component * cosf(-j * d_theta));
            tempV.push_back(v_componet);
            tempV.push_back(h_component * sinf(-j * d_theta));

            //add uv
            addUV(-j * d_theta, 0.5f - i * y_seg_len, tempV);

            // vertex below
            float rn = (i + 1) * y_seg_len * (1 / slope);
            //add position
            tempV.push_back(rn * cosf(-j * d_theta));
            tempV.push_back(0.5f - (i + 1) * y_seg_len);
            tempV.push_back(rn * sinf(-j * d_theta));

            //add normal
            tempV.push_back(h_component * cosf(-j * d_theta));
            tempV.push_back(v_componet);
            tempV.push_back(h_component * sinf(-j * d_theta));

            //add uv
            addUV(-j * d_theta, 0.5f - (i + 1) * y_seg_len, tempV);

            count += 2;
        }
    }

    //add a center point, otherwise the bot face will flip
    tempV.push_back(0.0f);
    tempV.push_back(-0.5f);
    tempV.push_back(0.0f);
    //normal
    tempV.push_back(0.0f);
    tempV.push_back(-1.0f);
    tempV.push_back(0.0f);
    //uv
    tempV.push_back(0.5f);
    tempV.push_back(0.5f);
    count++;

    count += calcBottom(p1, p2, -.5f, tempV, true);

    v.clear();
    // Add tangent and bitangent in v
    for (unsigned int i = 0; i < tempV.size(); i++) {
        //upper triangle
        glm::vec3 v1pos = {tempV[i++], tempV[i++], tempV[i++]};
        glm::vec3 v1normal = {tempV[i++], tempV[i++], tempV[i++]};
        glm::vec2 v1uv = {tempV[i++], tempV[i++]};
        glm::vec3 v2pos = {tempV[i++], tempV[i++], tempV[i++]};
        glm::vec3 v2normal = {tempV[i++], tempV[i++], tempV[i++]};
        glm::vec2 v2uv = {tempV[i++], tempV[i++]};
        glm::vec3 v3pos ={tempV[i++], tempV[i++], tempV[i++]};
        glm::vec3 v3normal = {tempV[i++], tempV[i++], tempV[i++]};
        glm::vec2 v3uv = {tempV[i++], tempV[i++]};
        i--;
        add3VertexInV(v, v1pos, v1normal, v1uv, v2pos, v2normal, v2uv, v3pos, v3normal, v3uv);
    }
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
    setAttribute(CS123::GL::ShaderAttrib::TEXCOORD0, 2, 6*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    setAttribute(CS123::GL::ShaderAttrib::TANGENT, 3, 8*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    setAttribute(CS123::GL::ShaderAttrib::BINORMAL, 3, 11*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    buildVAO();
}

void Cone::addUV(float theta, float y, std::vector<float> &vertices) {
    float v = y + 0.5f;
    float u = 0.f;
    u = theta < 0 ? u = -theta / (2 * M_PI) : u = 1 -theta / (2 * M_PI);
    vertices.push_back(u);
    vertices.push_back(v);
}

