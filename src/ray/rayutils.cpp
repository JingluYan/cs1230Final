#include "rayutils.h"

glm::vec3 mat4DotVec3(glm::mat4 m, glm::vec3 v, bool isPoint) {
    float w = isPoint ? 1.0f : 0.0f;
    glm::vec4 product = m * glm::vec4(v.x, v.y, v.z, w);
    glm::vec3 res = isPoint ? glm::vec3(product.x, product.y, product.z) / product.w
                      : product.xyz();
    return res;
}


//EPSILON is defined in header only
//MAX RECURSION DEPTH is defined in header only
