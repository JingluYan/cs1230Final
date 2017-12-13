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
    setAttribute(CS123::GL::ShaderAttrib::TEXCOORD0, 2, 6*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    setAttribute(CS123::GL::ShaderAttrib::TANGENT, 3, 8*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    setAttribute(CS123::GL::ShaderAttrib::BINORMAL, 3, 11*sizeof(float), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    buildVAO();
}

void Cube::calcVertex(int tess) {
    v.clear();
    float seg = static_cast<float>(tess);
    std::vector<float> tmp;
//    //front face
//    for (int i = 0; i < tess; i++) {
//        for (int j = 0; j < tess; j++) {
//            //upper triangle    }
//            tmp = {-.5f + j / seg, -.5f + i / seg, .5f,
//                  0.0f, 0.0f, 1.0f,
//                   j / seg, i / seg};
//            addVertex(tmp, v);

//            tmp = {-.5f + (j + 1) / seg, -.5f + (i + 1) / seg, .5f,
//                  0.0f, 0.0f, 1.0f,
//                   (j + 1) / seg, (i + 1) / seg};
//            addVertex(tmp, v);

//            tmp = {-.5f + j / seg, -.5f + (i + 1) / seg , .5f,
//                  0.0f, 0.0f, 1.0f,
//                   j / seg, (i + 1) / seg};
//            addVertex(tmp, v);

//            //lower triangle
//            tmp = {-.5f + j / seg, -.5f + i / seg , .5f,
//                  0.0f, 0.0f, 1.0f,
//                   j / seg, i / seg};
//            addVertex(tmp, v);

//            tmp = {-.5f + (j + 1) / seg , -.5f + i / seg, .5f,
//                  0.0f, 0.0f, 1.0f,
//                   (j + 1) / seg, i / seg};
//            addVertex(tmp, v);

//            tmp = { -.5f + (j + 1) / seg, -.5f + (i + 1) / seg, .5f,
//                  0.0f, 0.0f, 1.0f,
//                    (j + 1) / seg, (i + 1) / seg};
//            addVertex(tmp, v);

//        }
//    }

//    //back face
//    for (int i = 0; i < tess; i++) {
//        for (int j = 0; j < tess; j++) {
//            //upper triangle
//            tmp = { .5f - j / seg, -.5f + i / seg, -.5f,
//                  0.0f, 0.0f, -1.0f,
//                    - j / seg, i / seg};
//            addVertex(tmp, v);

//            tmp = { .5f - (j + 1) / seg, -.5f + (i + 1) / seg, -.5f,
//                  0.0f, 0.0f, -1.0f,
//                    - (j + 1) / seg, + (i + 1) / seg};
//            addVertex(tmp, v);

//            tmp = { .5f - j / seg, -.5f + (i + 1) / seg, -.5f,
//                  0.0f, 0.0f, -1.0f,
//                    - j / seg, (i + 1) / seg};
//            addVertex(tmp, v);

//            //lower triangle
//            tmp = { .5f - j / seg, -.5f + i / seg, -.5f,
//                  0.0f, 0.0f, -1.0f,
//                    - j / seg, i / seg};
//            addVertex(tmp, v);

//            tmp = { .5f - (j + 1) / seg, -.5f + i / seg, -.5f,
//                  0.0f, 0.0f, -1.0f,
//                    - (j + 1) / seg, i / seg};
//            addVertex(tmp, v);

//            tmp = {.5f - (j + 1) / seg, -.5f + (i + 1) / seg, -.5f,
//                  0.0f, 0.0f, -1.0f,
//                   - (j + 1) / seg, (i + 1) / seg};
//            addVertex(tmp, v);

//        }
//    }

//    //right face
//    for (int i = 0; i < tess; i++) {
//        for (int j = 0; j < tess; j++) {
//            //upper triangle
//            tmp = {.5f, -.5f + j / seg, -.5f + i / seg,
//                  1.0f, 0.0f, 0.0f,
//                   -(i / seg), j / seg};
//            addVertex(tmp, v);

//            tmp = {.5f, -.5f + (j + 1) / seg, -.5f + (i + 1) / seg,
//                  1.0f, 0.0f, 0.0f,
//                   -(i + 1) / seg, (j + 1) / seg};
//            addVertex(tmp, v);

//            tmp = {.5f, -.5f + j / seg, -.5f + (i + 1) / seg,
//                  1.0f, 0.0f, 0.0f,
//                  - (i + 1) / seg, j / seg};
//            addVertex(tmp, v);

//            //lower triangle
//            tmp = {.5f, -.5f + j / seg, -.5f + i / seg,
//                  1.0f, 0.0f, 0.0f,
//                  -i / seg, j / seg};
//            addVertex(tmp, v);

//            tmp = {.5f, -.5f + (j + 1) / seg, -.5f + i / seg,
//                  1.0f, 0.0f, 0.0f,
//                  -i / seg, (j + 1) / seg};
//            addVertex(tmp, v);

//            tmp = {.5f, -.5f + (j + 1) / seg, -.5f + (i + 1) / seg,
//                  1.0f, 0.0f, 0.0f,
//                  -(i + 1) / seg, (j + 1) / seg};
//            addVertex(tmp, v);

//        }
//    }


//    //left face
//    for (int i = 0; i < tess; i++) {
//        for (int j = 0; j < tess; j++) {
//            //upper triangle
//            tmp = {-.5f, -.5f + i / seg, -.5f + j / seg,
//                  -1.0f, 0.0f, 0.0f,
//                  j / seg, i / seg};
//            addVertex(tmp, v);

//            tmp = {-.5f, -.5f + (i + 1) / seg, -.5f + (j + 1) / seg,
//                  -1.0f, 0.0f, 0.0f,
//                  (j + 1) / seg, (i + 1) / seg};
//            addVertex(tmp, v);

//            tmp = {-.5f, -.5f + (i + 1) / seg, -.5f + j / seg,
//                  -1.0f, 0.0f, 0.0f,
//                  j / seg, (i + 1) / seg};
//            addVertex(tmp, v);

//            //lower triangle
//            tmp = {-.5f, -.5f + i / seg, -.5f + j / seg,
//                  -1.0f, 0.0f, 0.0f,
//                  j / seg, i / seg};
//            addVertex(tmp, v);

//            tmp = {-.5f, -.5f + i / seg, -.5f + (j + 1) / seg,
//                  -1.0f, 0.0f, 0.0f,
//                  (j  + 1) / seg, i / seg};
//            addVertex(tmp, v);

//            tmp = {-.5f, -.5f + (i + 1) / seg, -.5f + (j + 1) / seg,
//                  -1.0f, 0.0f, 0.0f,
//                  (j + 1) / seg, (i + 1) / seg};
//            addVertex(tmp, v);

//        }
//    }



//    //bottom face
//    for (int i = 0; i < tess; i++) {
//        for (int j = 0; j < tess; j++) {
//            //upper triangle
//            tmp = { -.5f + j / seg, -.5f, -.5f + i / seg,
//                  0.0f, -1.0f, 0.0f,
//                    j / seg, i / seg};
//            addVertex(tmp, v);

//            tmp = { -.5f + (j + 1) / seg, -.5f, -.5f + (i + 1) / seg,
//                  0.0f, -1.0f, 0.0f,
//                  (j + 1) / seg, (i + 1) / seg};
//            addVertex(tmp, v);

//            tmp = { -.5f + j / seg, -.5f, -.5f + (i + 1) / seg,
//                  0.0f, -1.0f, 0.0f,
//                  j / seg, (i + 1) / seg};
//            addVertex(tmp, v);

//            //lower triangle
//            tmp = { -.5f + j / seg, -.5f, -.5f + i / seg,
//                  0.0f, -1.0f, 0.0f,
//                  j / seg, i / seg};
//            addVertex(tmp, v);

//            tmp = { -.5f + (j + 1) / seg, -.5f, -.5f + i / seg,
//                  0.0f, -1.0f, 0.0f,
//                  (j + 1) / seg,  i / seg};
//            addVertex(tmp, v);

//            tmp = { -.5f + (j + 1) / seg, -.5f, -.5f + (i + 1) / seg,
//                  0.0f, -1.0f, 0.0f,
//                  (j + 1) / seg,  (i + 1) / seg};
//            addVertex(tmp, v);


//        }
//    }


    //upper face
    for (int i = 0; i < tess; i++) {
        for (int j = 0; j < tess; j++) {
            //upper triangle
            glm::vec3 normal = {0.0f, 1.0f, 0.0f};

            glm::vec3 v1pos = {-.5f + j / seg, .5f, -.5f + i / seg};
            glm::vec2 v1uv = {j / seg, -i / seg};
            glm::vec3 v2pos = { -.5f + (j + 1) / seg, .5f, -.5f + (i + 1) / seg};
            glm::vec2 v2uv = { (j + 1) / seg, -(i + 1) / seg};
            glm::vec3 v3pos = {-.5f + (j + 1) / seg, .5f, -.5f + i / seg};
            glm::vec2 v3uv = {(j + 1) / seg, -i / seg};

            // Edges of the triangle : postion delta
            glm::vec3 deltaPos1 = v2pos-v1pos;
            glm::vec3 deltaPos2 = v3pos-v1pos;
            glm::vec2 deltaUV1 = v2uv-v1uv;
            glm::vec2 deltaUV2 = v3uv-v1uv;

            float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
            glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
            glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;

            std::vector<float> v1;
            addglmVec3ToVector(v1pos, v1);
            addglmVec3ToVector(normal, v1);
            addglmVec2ToVector(v1uv, v1);
            addglmVec3ToVector(tangent, v1);
            addglmVec3ToVector(bitangent, v1);
            addVertex(v1, v);

            std::vector<float> v2;
            addglmVec3ToVector(v2pos, v2);
            addglmVec3ToVector(normal, v2);
            addglmVec2ToVector(v2uv, v2);
            addglmVec3ToVector(tangent, v2);
            addglmVec3ToVector(bitangent, v2);
            addVertex(v2, v);

            std::vector<float> v3;
            addglmVec3ToVector(v3pos, v3);
            addglmVec3ToVector(normal, v3);
            addglmVec2ToVector(v3uv, v3);
            addglmVec3ToVector(tangent, v3);
            addglmVec3ToVector(bitangent, v3);
            addVertex(v3, v);


            //lower triangle            
            v1pos = {-.5f + j / seg, .5f, -.5f + i / seg};
            v1uv = {j / seg, -i / seg};
            v2pos = { -.5f + j / seg, .5f, -.5f + (i + 1) / seg};
            v2uv = {j / seg, -(i + 1) / seg};
            v3pos = {-.5f + (j + 1) / seg, .5f, -.5f + (i + 1) / seg};
            v3uv = {(j + 1) / seg, -(i + 1) / seg};

            // Edges of the triangle : postion delta
            deltaPos1 = v2pos-v1pos;
            deltaPos2 = v3pos-v1pos;
            deltaUV1 = v2uv-v1uv;
            deltaUV2 = v3uv-v1uv;

            r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
            tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
            bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;

            std::vector<float> v4;
            addglmVec3ToVector(v1pos, v4);
            addglmVec3ToVector(normal, v4);
            addglmVec2ToVector(v1uv, v4);
            addglmVec3ToVector(tangent, v4);
            addglmVec3ToVector(bitangent, v4);
            addVertex(v4, v);

            std::vector<float> v5;
            addglmVec3ToVector(v2pos, v5);
            addglmVec3ToVector(normal, v5);
            addglmVec2ToVector(v2uv, v5);
            addglmVec3ToVector(tangent, v5);
            addglmVec3ToVector(bitangent, v5);
            addVertex(v5, v);

            std::vector<float> v6;
            addglmVec3ToVector(v3pos, v6);
            addglmVec3ToVector(normal, v6);
            addglmVec2ToVector(v3uv, v6);
            addglmVec3ToVector(tangent, v6);
            addglmVec3ToVector(bitangent, v6);
            addVertex(v6, v);

        }
    }
}

void Cube::addVertex(std::vector<float> vertex, std::vector<float>& vertices) {
    for (int i = 0; i < vertex.size(); i++) {
        vertices.push_back(vertex[i]);
    }
}

void Cube::addglmVec3ToVector(glm::vec3 src, std::vector<float>& dest) {
    for (int i = 0; i < src.length(); i++) {
        dest.push_back(src[i]);
    }
}

void Cube::addglmVec2ToVector(glm::vec2 src, std::vector<float>& dest) {
    for (int i = 0; i < src.length(); i++) {
        dest.push_back(src[i]);
    }
}
