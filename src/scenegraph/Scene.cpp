#include "Scene.h"
#include "Camera.h"
#include "CS123ISceneParser.h"

#include "glm/gtx/transform.hpp"


Scene::Scene()
{
}

Scene::Scene(Scene &scene)
{
    // We need to set the global constants to one when we duplicate a scene,
    // otherwise the global constants will be double counted (squared)
    CS123SceneGlobalData global = { 1, 1, 1, 1};
    setGlobal(global);

    // TODO [INTERSECT]
    // Make sure to copy over the lights and the scenegraph from the old scene,
    // as well as any other member variables your new scene will need.
    for (CS123SceneLightData light : scene.lights) {
        this->lights.push_back(light);
    }

    for (PrimTransPair pair: scene.primTransPairs) {
        addPrimitive(pair.primitive, pair.tranformation);
    }

}

Scene::~Scene()
{
    // Do not delete m_camera, it is owned by SupportCanvas3D
}

void Scene::parse(Scene *sceneToFill, CS123ISceneParser *parser) {
    // TODO: load scene into sceneToFill using setGlobal(), addLight(), addPrimitive(), and
    //   finishParsing()
    CS123SceneGlobalData globalData;
    parser->getGlobalData(globalData);
    sceneToFill->setGlobal(globalData);

    CS123SceneLightData lightData;
    int lightCount = parser->getNumLights();
    for (int i = 0; i < lightCount; i++) {
        parser->getLightData(i, lightData);
        sceneToFill->addLight(lightData);
    }

    CS123SceneNode *rootNode = parser->getRootNode();
    traverseTree(sceneToFill, rootNode, glm::mat4x4());
}

void Scene::traverseTree(Scene *sceneTofill, CS123SceneNode *node, glm::mat4x4 transMatrix) {
    for (CS123SceneTransformation *trans : node->transformations) {
        switch (trans->type) {
            case TRANSFORMATION_ROTATE:
                transMatrix *= glm::rotate(trans->angle, trans->rotate);
            break;
            case TRANSFORMATION_TRANSLATE:
                transMatrix *= glm::translate(trans->translate);
            break;
            case TRANSFORMATION_SCALE:
                transMatrix *= glm::scale(trans->scale);
            break;
            case TRANSFORMATION_MATRIX:
                transMatrix *= trans->matrix;
            break;
        }
    }

    for (CS123ScenePrimitive *prim : node->primitives) {
        sceneTofill->addPrimitive(*prim, transMatrix);
    }

    for (CS123SceneNode *child : node->children) {
        traverseTree(sceneTofill, child, transMatrix);
    }
}

void Scene::addPrimitive(const CS123ScenePrimitive &scenePrimitive, const glm::mat4x4 &matrix) {
    CS123ScenePrimitive newPrim;
    newPrim.type = scenePrimitive.type;
    newPrim.meshfile = scenePrimitive.meshfile;
    newPrim.material = scenePrimitive.material;
    // deep copy material
    // NOTE that these r, g, b are in [0,1] instead of [0,255]
    // which is needed by BGRA
    newPrim.material.cAmbient.r *= global.ka;
    newPrim.material.cAmbient.g *= global.ka;
    newPrim.material.cAmbient.b *= global.ka;
    newPrim.material.cDiffuse.r *= global.kd;
    newPrim.material.cDiffuse.g *= global.kd;
    newPrim.material.cDiffuse.b *= global.kd;
    newPrim.material.cSpecular.r *= global.ks;
    newPrim.material.cSpecular.g *= global.ks;
    newPrim.material.cSpecular.b *= global.ks;
    newPrim.material.cReflective.r *= global.ks;
    newPrim.material.cReflective.g *= global.ks;
    newPrim.material.cReflective.b *= global.ks;
    newPrim.material.textureMap = scenePrimitive.material.textureMap;
    newPrim.material.bumpMap = scenePrimitive.material.bumpMap;

    PrimTransPair pair(newPrim, matrix);
    primTransPairs.push_back(pair);
}

void Scene::addLight(const CS123SceneLightData &sceneLight) {
    lights.push_back(sceneLight);
}

void Scene::setGlobal(const CS123SceneGlobalData &global) {
    this->global = global;
}

void Scene::finishParsing() {

}
