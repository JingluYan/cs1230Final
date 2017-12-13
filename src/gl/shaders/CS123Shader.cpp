#include "CS123Shader.h"

#include "CS123SceneData.h"
#include "Settings.h"


#include "gl/GLDebug.h"
#include <sstream>

//TODO: to be deleted
#include "lib/errorchecker.h"


namespace CS123 { namespace GL {


CS123Shader::CS123Shader(const std::string &vertexSource, const std::string &fragmentSource) :
    Shader(vertexSource, fragmentSource)
{
}

CS123Shader::CS123Shader(const std::string &vertexSource, const std::string &geometrySource, const std::string &fragmentSource) :
    Shader(vertexSource, geometrySource, fragmentSource)
{
}

glm::vec3 toGLMVec3(const CS123SceneColor &c) {
    return glm::vec3(c.r, c.g, c.b);
}

void CS123Shader::applyMaterial(const CS123SceneMaterial &material) {
    ErrorChecker::printGLErrors("line 1");
    setUniform("ambient_color", toGLMVec3(material.cAmbient));
    ErrorChecker::printGLErrors("line 2");

    setUniform("diffuse_color", toGLMVec3(material.cDiffuse));
    ErrorChecker::printGLErrors("line 3");

    setUniform("specular_color", toGLMVec3(material.cSpecular));
    ErrorChecker::printGLErrors("line 4");

    setUniform("shininess", material.shininess);
//    setUniform( "repeatUV", glm::vec2{1,1});
}

void CS123Shader::setLight(const CS123SceneLightData &light) {
    bool ignoreLight = false;

    GLint lightType;
    std::string name;
    glm::vec3 ndir;
    switch(light.type) {
        case LightType::LIGHT_POINT:
            lightType = 0;
            name = "lightPositions";
            setUniformArrayByIndex(name, light.pos.xyz(), light.id);
            if (!settings.usePointLights) ignoreLight = true;
            break;
        case LightType::LIGHT_DIRECTIONAL:
            lightType = 1;
            ndir = glm::normalize(light.dir.xyz());
            name = "lightDirections";
            setUniformArrayByIndex(name, ndir, light.id);
            if (!settings.useDirectionalLights) ignoreLight = true;
            break;
        default:
            lightType = 0;
            ignoreLight = true; // Light type not supported
            break;
    }

    CS123SceneColor color = light.color;
    if (ignoreLight) color.r = color.g = color.b = 0;

    setUniformArrayByIndex("lightTypes", lightType, light.id);
    setUniformArrayByIndex("lightColors", glm::vec3(color.r, color.g, color.b), light.id);
    setUniformArrayByIndex("lightAttenuations", light.function, light.id);
}

}}
