#ifndef LIGHT_H
#define LIGHT_H

#include <glm.hpp>
#include "CS123SceneData.h"

class RayShape;

class Light
{
public:
    Light();
    glm::vec3 color;
    virtual void lit(glm::vec3 &curColor,
                     RayShape *hitObj,
                     glm::vec3 normal_world,
                     glm::vec3 hit_world,
                     glm::vec3 eye,
                     glm::vec3 textureColor, // already in [0, 255]
                     const std::vector<RayShape*> shapes) = 0;

};


class PointLight : public Light {
public:
    glm::vec3 position;
    glm::vec3 function; //attenuation function

    void lit(glm::vec3 &curColor,
             RayShape *hitObj,
             glm::vec3 normal_world,
             glm::vec3 hit_world,
             glm::vec3 eye,
             glm::vec3 textureColor, // already in [0, 255]
             const std::vector<RayShape*> shapes) override;
};


class DirectionalLight : public Light {
public:
    glm::vec3 direction;
    void lit(glm::vec3 &curColor,
             RayShape *hitObj,
             glm::vec3 normal_world,
             glm::vec3 hit_world,
             glm::vec3 eye,
             glm::vec3 textureColor, // already in [0, 255]
             const std::vector<RayShape *> shapes) override;
};

#endif // LIGHT_H
