#include "openglshape.h"

#include "../../gl/datatype/VAO.h"
#include "../../gl/datatype/IBO.h"

using namespace CS123::GL;

OpenGLShape::OpenGLShape() :
    m_size(0),
    m_drawMode(VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES),
    m_numVertices(0),
    m_VAO(nullptr),
    v(0)
{
    // You shouldn't need to do anything here
    // Aren't initializer lists amazing?
}

OpenGLShape::~OpenGLShape()
{
    // You shouldn't need to do anything here
    // m_VAO's destructor will automatically be called
    // Aren't smart pointers amazing?
}


/**
 * @param data - Vector of floats containing the vertex data.
 * @param size - number of elements in the array.
 * @param drawMode - Drawing mode
 * @param numVertices - Number of vertices to be rendered.
 */
void OpenGLShape::setVertexData(GLfloat *data, int size, VBO::GEOMETRY_LAYOUT drawMode, int numVertices) {
    // Store the vertex data and other values to be used later when constructing the VAO
    m_data = data;
    m_size = size;
    m_drawMode = drawMode;
    m_numVertices = numVertices;
}


/**
 * @param index OpenGL handle to the attribute location. These are specified in ShaderAttribLocations.h
 * @param numElementsPerVertex Number of elements per vertex. Must be 1, 2, 3 or 4 (e.g. position = 3 for x,y,z)
 * @param offset Offset in BYTES from the start of the array to the beginning of the first element
 * @param type Primitive type (FLOAT, INT, UNSIGNED_BYTE)
 * @param normalize
 */
void OpenGLShape::setAttribute(
         GLuint index, GLuint numElementsPerVertex, int offset, VBOAttribMarker::DATA_TYPE type, bool normalize) {
    m_markers.push_back(VBOAttribMarker(index, numElementsPerVertex, offset, type, normalize));
}

void OpenGLShape::buildVAO() {
    CS123::GL::VBO vbo = VBO(m_data, m_size, m_markers, m_drawMode);
    m_VAO = std::make_unique<VAO>(vbo,m_numVertices);
}

void OpenGLShape::draw() {
    if (m_VAO) {
        // TODO [Task 5]
        m_VAO->bind();
        m_VAO->draw();
        m_VAO->unbind();
    }
}

void::OpenGLShape::add3VertexInV(std::vector<float> &v,
                                 glm::vec3 v1pos, glm::vec3 v1normal, glm::vec2 v1uv,
                                 glm::vec3 v2pos, glm::vec3 v2normal, glm::vec2 v2uv,
                                 glm::vec3 v3pos, glm::vec3 v3normal, glm::vec2 v3uv){
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
    addglmVec3ToVector(v1normal, v1);
    addglmVec2ToVector(v1uv, v1);
    addglmVec3ToVector(tangent, v1);
    addglmVec3ToVector(bitangent, v1);
    addVertex(v1, v);

    std::vector<float> v2;
    addglmVec3ToVector(v2pos, v2);
    addglmVec3ToVector(v2normal, v2);
    addglmVec2ToVector(v2uv, v2);
    addglmVec3ToVector(tangent, v2);
    addglmVec3ToVector(bitangent, v2);
    addVertex(v2, v);

    std::vector<float> v3;
    addglmVec3ToVector(v3pos, v3);
    addglmVec3ToVector(v3normal, v3);
    addglmVec2ToVector(v3uv, v3);
    addglmVec3ToVector(tangent, v3);
    addglmVec3ToVector(bitangent, v3);
    addVertex(v3, v);
}


void OpenGLShape::addVertex(std::vector<float> vertex, std::vector<float>& vertices) {
    for (int i = 0; i < vertex.size(); i++) {
        vertices.push_back(vertex[i]);
    }
}

void OpenGLShape::addglmVec3ToVector(glm::vec3 src, std::vector<float>& dest) {
    for (int i = 0; i < src.length(); i++) {
        dest.push_back(src[i]);
    }
}

void OpenGLShape::addglmVec2ToVector(glm::vec2 src, std::vector<float>& dest) {
    for (int i = 0; i < src.length(); i++) {
        dest.push_back(src[i]);
    }
}

