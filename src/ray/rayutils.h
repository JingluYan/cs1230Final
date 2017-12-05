#ifndef RAYUTILS_H
#define RAYUTILS_H

#include <glm.hpp>



glm::vec3 mat4DotVec3(glm::mat4 m, glm::vec3 v, bool isPoint);


// NOTE that higher EPSILON is not necessarily better,
// need to account for errors in our calculation, i.e
// our calculated intersect point may be off by more than the smallest EPSILON
// because the accuracy of our calculation is not as good
//    const double EPSILON = std::numeric_limits<double>::epsilon();
const double EPSILON = 0.00001;

const float EPSILON_F = 0.00001f;

const int MAX_RECURSION_DEPTH = 5;


#endif // RAYUTILS_H
