#include "cylinder.h"
#include <iostream>
#include <math.h>

using namespace std;

Cylinder::Cylinder(int p1, int p2)
{
    update(p1, p2);
}

int Cylinder::calcVertices(int p1, int p2) {
    tempV.clear();
    p2 = p2 < 3 ? 3 : p2;
    int count = 0;
    //calc side
    for (float i = 0; i < p1; i++) {
        float deg = 360.0f;
        for (int j = 0; j <= p2; j++) {
            deg -= 360 / static_cast<float>(p2);
            float rad = deg * M_PI / 180;
            //upper
            tempV.push_back(r * cos(rad));
            tempV.push_back(0.5f - i / p1);
            tempV.push_back( r * sin(rad));
            addNormal(rad, tempV);
            addUV(rad, 0.5f - i / p1, tempV);

            //lower point
            tempV.push_back(r * cos(rad));
            tempV.push_back(0.5f - (i + 1) / p1);
            tempV.push_back( r * sin(rad));
            addNormal(rad, tempV);
            addUV(rad, 0.5f - (i + 1) / p1, tempV);
            count += 2;

        }
    }

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

    // draw bottom
    std::vector<float> tmp = {0.0f, -.5f, 0.0f, //position
                              0.0f, -1.0f, 0.0f,  // normal
                              0.5f, 0.5f // uv
                             };
    tempV.insert(tempV.end(), tmp.begin(), tmp.end());
    count++;

    count += calcBottom(p1, p2, -.5f, tempV, true);
    count += calcBottom(p1, p2, 0.5f, tempV, false);

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
    setAttribute(CS123::GL::ShaderAttrib::TEXCOORD0, 2, 6*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    setAttribute(CS123::GL::ShaderAttrib::TANGENT, 3, 8*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    setAttribute(CS123::GL::ShaderAttrib::BINORMAL, 3, 11*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    buildVAO();
}


void Cylinder::addNormal(float deg, std::vector<float> &vertices) {
    vertices.push_back(cos(deg));
    vertices.push_back(0);
    vertices.push_back(sin(deg));
}

void Cylinder::addUV(float theta, float y, std::vector<float> &vertices) {
    float v = y + 0.5f;
    float u = 0.f;
    u = theta < 0 ? u = -theta / (2 * M_PI) : u = 1 -theta / (2 * M_PI);
    vertices.push_back(u);
    vertices.push_back(v);
}

