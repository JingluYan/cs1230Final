#ifndef RAYSHAPE_H
#define RAYSHAPE_H

#include <glm.hpp>
#include <CS123SceneData.h>
#include <memory>

class RayShape
{
public:
    RayShape();
    PrimitiveType type;     // not used
    glm::mat4 modelMatrix;
    std::unique_ptr<CS123SceneMaterial> material;

    // hit, eye, and ray must be in object space
    virtual glm::vec3 getNormal(glm::vec3 hit) = 0;
    virtual bool intersect(const glm::vec3 eye, const glm::vec3 ray, double &t) = 0;
    virtual glm::vec2 getUV(glm::vec3 hit) = 0;
    bool solveT(double a, double b, double c, double &t);
};


class RayCube : public RayShape
{
public:
    glm::vec3 getNormal(glm::vec3 hit) override;
    virtual bool intersect(const glm::vec3 eye, const glm::vec3 ray, double &t) override;
    glm::vec2 getUV(glm::vec3 hit);
};


class RaySphere : public RayShape
{
public:
    bool intersect(const glm::vec3 eye, const glm::vec3 ray, double &t) override;
    glm::vec3 getNormal(glm::vec3 hit) override;
    glm::vec2 getUV(glm::vec3 hit);
};


class RayCone : public RayShape
{
public:
    glm::vec3 getNormal(glm::vec3 hit) override;
    bool intersect(const glm::vec3 eye, const glm::vec3 ray, double &t) override;
    glm::vec2 getUV(glm::vec3 hit);
};


class RayCylinder : public RayShape
{
public:
    glm::vec3 getNormal(glm::vec3 hit) override;
    bool intersect(const glm::vec3 eye, const glm::vec3 ray, double &t) override;
    glm::vec2 getUV(glm::vec3 hit);
};


#endif // RAYSHAPE_H
