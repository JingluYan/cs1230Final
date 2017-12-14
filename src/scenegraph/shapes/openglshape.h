#ifndef OPENGLSHAPE_H
#define OPENGLSHAPE_H

#include "GL/glew.h"
#include <glm.hpp>

#include <memory>
#include <vector>

#include "../../gl/datatype/VBO.h"
#include "../../gl/datatype/VBOAttribMarker.h"

namespace CS123 { namespace GL {

class VAO;

}}

using namespace CS123::GL;

class OpenGLShape {
public:
    OpenGLShape();

    ~OpenGLShape();

    /** Initialize the VBO with the given vertex data. */
    void setVertexData(GLfloat *data, int size, VBO::GEOMETRY_LAYOUT drawMode, int numVertices);


    /** Initialize IBO with given vertex indices */
    void setIndicesData(int *data, int size);

    /** Enables the specified attribute and calls glVertexAttribPointer with the given arguments. */
    void setAttribute(GLuint index, GLuint numElementsPerVertex, int offset, VBOAttribMarker::DATA_TYPE type,
                      bool normalize);

    /** Build the VAO given the specified vertex data and atrributes */
    void buildVAO();

    /** Draw the initialized geometry. */
    void draw();


protected:
    GLfloat *m_data;                            /// vector of floats containing the vertex data.
    int *m_indices;                           /// vector of ints containing the vertex indices
    int m_indices_size;                       /// size of the indices vector
    std::vector<float> v;
    const double EPSILON = std::numeric_limits<double>::epsilon();


    void add3VertexInV(std::vector<float> &v,
                       glm::vec3 v1pos, glm::vec3 v1normal, glm::vec2 v1uv,
                       glm::vec3 v2pos, glm::vec3 v2normal, glm::vec2 v2uv,
                       glm::vec3 v3pos, glm::vec3 v3normal, glm::vec2 v3uv);

    // helper functions
    void addVertex(std::vector<float> vertex, std::vector<float>& vertices);
    void addglmVec3ToVector(glm::vec3 src, std::vector<float>& dest);
    void addglmVec2ToVector(glm::vec2 src, std::vector<float>& dest);
private:
    GLsizeiptr m_size;                          /// size of the data array, in bytes.
    VBO::GEOMETRY_LAYOUT m_drawMode;            /// drawing mode
    int m_numVertices;                          /// number of vertices to be rendered
    std::vector<VBOAttribMarker> m_markers;     /// list of VBOAttribMarkers that describe how the data is laid out.
    std::unique_ptr<CS123::GL::VAO> m_VAO;      /// a wrapper for the vertex array object (VAO)

};

#endif // OPENGLSHAPE_H
