#include "light.h"
#include <iostream>
#include "Settings.h"
#include "rayshape.h"
#include "rayutils.h"
#include <cmath>

using namespace std;
Light::Light()
{
}

// point light

void PointLight::lit(glm::vec3 &curColor,
                     RayShape* hitObj,
                     glm::vec3 normal_world,
                     glm::vec3 hit_world,
                     glm::vec3 eye,
                     glm::vec3 textureColor, // already in [0, 255]
                     const std::vector<RayShape*> shapes) {
    // kd has been multiplied into the material's diffuse color
    // so no need to multiple by kd again
    // Because the formula given has Kd, I set Kd to 1 to keep the formula
    double kd = 1.0f;
    double ks = 1.0f;

    glm::vec3 L = position - hit_world;
    float lightHitDis = glm::length(L);
    L = glm::normalize(L);
    normal_world = glm::normalize(normal_world);

    // shadow
    if (settings.useShadows) {
        double lightIntersectDis = glm::length(position - hit_world);
        for (RayShape *shape : shapes) {
            double t = std::numeric_limits<double>::max();
            glm::mat4 inverseModelMat = glm::inverse(shape->modelMatrix);
            glm::vec3 L_obj = mat4DotVec3(inverseModelMat, L, false);
            glm::vec3 hit_obj = mat4DotVec3(inverseModelMat, hit_world, true) + 5.0f * EPSILON_F * L_obj; // 5 is arbitrary

            if (shape->intersect(hit_obj, L_obj, t)) {
                if (t < lightIntersectDis && t > 0) {
                    return;
                }
            }

        }
    }

    // attenuation
    float attenuation = std::min(1 / (function.x + function.y * lightHitDis + function.z * lightHitDis * lightHitDis), 1.0f);

    // diffuse color
    glm::vec3 objDiffuse = hitObj->material->cDiffuse.xyz();
    // blend texture color
    if (settings.useTextureMapping) {
        objDiffuse.r = glm::mix(objDiffuse.r, (textureColor.r / 255.f), hitObj->material->blend);
        objDiffuse.g = glm::mix(objDiffuse.g, (textureColor.g / 255.f), hitObj->material->blend);
        objDiffuse.b = glm::mix(objDiffuse.b, (textureColor.b / 255.f), hitObj->material->blend);
    }

    float diffuse_contrib_r = attenuation * color.r * (kd * objDiffuse.r * glm::max(glm::dot(normal_world, L), 0.0f));
    float diffuse_contrib_g = attenuation * color.g * (kd * objDiffuse.g * glm::max(glm::dot(normal_world, L), 0.0f));
    float diffuse_contrib_b = attenuation * color.b * (kd * objDiffuse.b * glm::max(glm::dot(normal_world, L), 0.0f));


    curColor.r += static_cast<float>(diffuse_contrib_r * 255);
    curColor.g += static_cast<float>(diffuse_contrib_g * 255);
    curColor.b += static_cast<float>(diffuse_contrib_b * 255);




    // specular light
    if (hitObj->material->shininess > EPSILON_F) {
        glm::vec3 objSpecular = hitObj->material->cSpecular.xyz();
        float shininess = hitObj->material->shininess;
        glm::vec3 hitToEye = glm::normalize(eye - hit_world);
        glm::vec3 R = glm::reflect(-L, normal_world); // reflection dir of light from light to intersect
        R = glm::normalize(R);
        double spec_contrib_r = attenuation * color.r *(ks * objSpecular.r * std::pow(glm::max(glm::dot(hitToEye, R),0.0f), shininess));
        double spec_contrib_g = attenuation * color.g *(ks * objSpecular.g * std::pow(glm::max(glm::dot(hitToEye, R),0.0f), shininess));
        double spec_contrib_b = attenuation * color.b *(ks * objSpecular.b * std::pow(glm::max(glm::dot(hitToEye, R),0.0f), shininess));\

        spec_contrib_b = glm::clamp(spec_contrib_b, 0.0, 1.0);
        spec_contrib_g = glm::clamp(spec_contrib_g, 0.0, 1.0);
        spec_contrib_r = glm::clamp(spec_contrib_r, 0.0, 1.0);
        curColor.r += static_cast<float>(spec_contrib_r * 255);
        curColor.g += static_cast<float>(spec_contrib_g * 255);
        curColor.b += static_cast<float>(spec_contrib_b * 255);
    }

}


void DirectionalLight::lit(glm::vec3 &curColor,
                           RayShape *hitObj,
                           glm::vec3 normal_world,
                           glm::vec3 hit_world,
                           glm::vec3 eye, glm::vec3 textureColor,
                           const std::vector<RayShape *> shapes) {

    // kd has been multiplied into the material's diffuse color
    // so no need to multiple by kd again
    // Because the formula given has Kd, I set Kd to 1 to keep the formula
    double kd = 1.0f;
    double ks = 1.0f;

    glm::vec3 L = glm::normalize(direction);
    L = -L;
    normal_world = glm::normalize(normal_world);

    if (settings.useShadows) {
        for (RayShape *shape : shapes) {
            double t = std::numeric_limits<double>::max();
            glm::mat4 inverseModelMat = glm::inverse(shape->modelMatrix);
            glm::vec3 L_obj = mat4DotVec3(inverseModelMat, L, false);
            glm::vec3 hit_obj = mat4DotVec3(inverseModelMat, hit_world, true) + 5.0f * EPSILON_F * L_obj; // 5 is arbitrary

            if (shape->intersect(hit_obj, L_obj, t) && t > 0) {
                return;
            }

        }
    }

    // diffuse color
    glm::vec3 objDiffuse = hitObj->material->cDiffuse.xyz();
    // blend texture color
    if (settings.useTextureMapping) {
        objDiffuse.r = glm::mix(objDiffuse.r, (textureColor.r / 255.f), hitObj->material->blend);
        objDiffuse.g = glm::mix(objDiffuse.g, (textureColor.g / 255.f), hitObj->material->blend);
        objDiffuse.b = glm::mix(objDiffuse.b, (textureColor.b / 255.f), hitObj->material->blend);
    }

    float diffuse_contrib_r = color.r * (kd * objDiffuse.r * glm::max(glm::dot(normal_world, L), 0.0f));
    float diffuse_contrib_g = color.g * (kd * objDiffuse.g * glm::max(glm::dot(normal_world, L), 0.0f));
    float diffuse_contrib_b = color.b * (kd * objDiffuse.b * glm::max(glm::dot(normal_world, L), 0.0f));

    curColor.r += static_cast<float>(diffuse_contrib_r * 255);
    curColor.g += static_cast<float>(diffuse_contrib_g * 255);
    curColor.b += static_cast<float>(diffuse_contrib_b * 255);

    // specular light
    if (hitObj->material->shininess > EPSILON_F) {
        glm::vec3 objSpecular = hitObj->material->cSpecular.xyz();
        float shininess = hitObj->material->shininess;
        glm::vec3 hitToEye = glm::normalize(eye - hit_world);
        glm::vec3 R = glm::reflect(-L, normal_world); // reflection dir of light from light to intersect
        R = glm::normalize(R);
        double spec_contrib_r = color.r *(ks * objSpecular.r * std::pow(glm::max(glm::dot(hitToEye, R),0.0f), shininess));
        double spec_contrib_g = color.g *(ks * objSpecular.g * std::pow(glm::max(glm::dot(hitToEye, R),0.0f), shininess));
        double spec_contrib_b = color.b *(ks * objSpecular.b * std::pow(glm::max(glm::dot(hitToEye, R),0.0f), shininess));
        curColor.r += static_cast<float>(spec_contrib_r * 255);
        curColor.g += static_cast<float>(spec_contrib_g * 255);
        curColor.b += static_cast<float>(spec_contrib_b * 255);
    }

}
