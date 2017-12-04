#include "RayScene.h"
#include "Settings.h"
//#include "CS123SceneData.h"
#include <iostream>
#include "camera/Camera.h"
#include "ray/rayutils.h"
#include <assert.h>
#include <limits>
#include "BGRA.h"


RayScene::RayScene(Scene &scene) :
    Scene(scene)
{
    // TODO [INTERSECT]
    // Remember that any pointers or OpenGL objects (e.g. texture IDs) will
    // be deleted when the old scene is deleted (assuming you are managing
    // all your memory properly to prevent memory leaks).  As a result, you
    // may need to re-allocate some things here.
    m_rayLights.clear();
    m_rayShapes.clear();
    for(PrimTransPair pair : primTransPairs) {
        RayShape *rayShape;

        bool customShape = false;
        //set the rayShape type
        switch(pair.primitive.type) {
            case PrimitiveType::PRIMITIVE_CONE:
                rayShape = new RayCone();
                break;
            case PrimitiveType::PRIMITIVE_CUBE:
                rayShape = new RayCube();
                break;
            case PrimitiveType::PRIMITIVE_CYLINDER:
                rayShape = new RayCylinder();
                break;
            case PrimitiveType::PRIMITIVE_SPHERE:
                rayShape = new RaySphere();
                break;
            //end when
            default:
                customShape = true;
        }
        // skip custom shapes
        if (customShape) {
            continue;
        }
        rayShape->type = pair.primitive.type;
        rayShape->modelMatrix = pair.tranformation;
        rayShape->material->cDiffuse = pair.primitive.material.cDiffuse;
        rayShape->material->cAmbient = pair.primitive.material.cAmbient;
        rayShape->material->cReflective = pair.primitive.material.cReflective;
        rayShape->material->cSpecular = pair.primitive.material.cSpecular;
        rayShape->material->cTransparent = pair.primitive.material.cTransparent;
        rayShape->material->cEmissive = pair.primitive.material.cEmissive;
        rayShape->material->textureMap = pair.primitive.material.textureMap;
        rayShape->material->blend = pair.primitive.material.blend;
        rayShape->material->bumpMap = pair.primitive.material.bumpMap;
        rayShape->material->shininess = pair.primitive.material.shininess;
        rayShape->material->ior = pair.primitive.material.ior;

        if (pair.primitive.material.textureMap.isUsed) {
            std::string fileName = pair.primitive.material.textureMap.filename;
            if (m_fileNameToTexture.find(fileName) == m_fileNameToTexture.end()) {
                // filename not found
                QString qFileName(fileName.c_str());
                m_fileNameToTexture[fileName] = QImage(qFileName);
            }
        }

        m_rayShapes.push_back(rayShape);
    }

    for (CS123SceneLightData light : lights) {
        Light *rayLight = nullptr;
        switch(light.type) {
        case LightType::LIGHT_POINT:
            rayLight = new PointLight();
            rayLight->color = light.color.rgb();
            ((PointLight*)rayLight)->position = light.pos.xyz();
            ((PointLight*)rayLight)->function = light.function.xyz();
            break;
        case LightType::LIGHT_DIRECTIONAL:
            rayLight = new DirectionalLight();
            rayLight->color = light.color.rgb();
            ((DirectionalLight*)rayLight)->direction = light.dir.xyz();
            break;
        case LightType::LIGHT_SPOT:
            // note required. Leave it here for now
            break;
        default:
            std::cout << "Error in rayScene: light type not handled!" << std::endl;
        }

        if (rayLight != nullptr) {
            m_rayLights.push_back(rayLight);
        }
    }
}



RayScene::~RayScene()
{
    for (RayShape *s : m_rayShapes) {
        delete s;
    }

    for (Light *l : m_rayLights) {
        delete l;
    }

}

//TODO: remove

//void RayScene::render(int width, int height, Camera *camera, BGRA *canvas) {
//    glm::mat4 inverseViewMat = glm::inverse(camera->getViewMatrix());
////    glm::mat4 inverseProjMat = glm::inverse(camera->getProjectionMatrix());
//    glm::mat4 inverseScaleMat = glm::inverse(camera->getScaleMatrix());
////    glm::mat4 inverseViewProjMat = inverseViewMat * inverseProjMat;
//    glm::mat4 inverseViewScaleMat = inverseViewMat * inverseScaleMat;
//    glm::vec3 eye = (inverseViewScaleMat * glm::vec4(0,0,0,1)).xyz(); //world space cam pos
////    glm::vec3 eye = (inverseViewProjMat * glm::vec4(0,0,0,1)).xyz(); //world space cam pos

//    int pixIndx = 0;
//    for (int y = 0; y < height; y++) {
//        for (int x = 0; x < width; x++) {
//            glm::vec3 pfilm = glm::vec3((2 * (float)x / (float)width) - 1, 1 - (2 * (float)y / (float)height), -1);
//            glm::vec3 pworld = mat4DotVec3(inverseViewScaleMat, pfilm, true);
//            glm::vec3 ray = pworld - eye;
//            canvas[pixIndx] = renderPixel(eye, ray, 0);
//            pixIndx++;
//        }
//    }
//}

//BGRA RayScene::renderPixel(glm::vec3 eye_w, glm::vec3 ray_w, int recurDepth) {
//    if (recurDepth > MAX_RECURSION_DEPTH) return BGRA();

//    double t = std::numeric_limits<double>::max();
//    // find the closest intersect shape
//    RayShape *closestShape = nullptr;
//    for (RayShape *shape : m_rayShapes) {
//        glm::mat4 inverseModelMat = glm::inverse(shape->modelMatrix);
//        glm::vec3 obj_eye = mat4DotVec3(inverseModelMat, eye_w, true);
//        // DO NOT normalize obj_ray
//        glm::vec3 obj_ray = mat4DotVec3(inverseModelMat, ray_w, false);
//        double tmp_t = std::numeric_limits<double>::max();
//        if (shape->intersect(obj_eye, obj_ray, tmp_t)) {
//            if (tmp_t < t && tmp_t > 0) {
//                t = tmp_t;
//                closestShape = shape;
//            }

//        }
//    }

//    //tmp_color is the color of current pixel
//    BGRA tmp_color;

//    //if there is an intersect
//    if (closestShape) {
//        //add ambient here and then add light contribution for each light
//        // ka has been multiplied into the material's ambient color
//        // so no need to multiple by ka again, but still leave it in to comply with formula
//        float ka = 1.0f;
//        tmp_color.r = static_cast<unsigned char>(ka * closestShape->material->cAmbient.r * 255);
//        tmp_color.b = static_cast<unsigned char>(ka * closestShape->material->cAmbient.b * 255);
//        tmp_color.g = static_cast<unsigned char>(ka * closestShape->material->cAmbient.g * 255);

//        //get the hit point in world space
//        glm::vec3 hit_world = eye_w + ray_w * static_cast<float>(t);
//        // transform the hit point from world space to object space
//        glm::vec3 hit_obj = mat4DotVec3(glm::inverse(closestShape->modelMatrix), hit_world, true);

//        // get the world space normal of the hit point
//        //closestShape->getNormal returns normal in obj space
//        glm::vec3 normal_world = closestShape->getNormal(hit_obj);

//        // need to transform the normal from object space to world space
//        // by discarding the translation of the modelmatrix
//        // and then inverse transpose. See slide for details
//        glm::mat4 model = closestShape->modelMatrix;
//        glm::mat3 M3 = glm::mat3(model); // init M3 with the upper left 3x3 cells of model
//        M3 = glm::inverse(glm::transpose(M3));
//        // NOTE: It is WRONG to apply inverse model transform to the normal
//        // because scale will distort object's normal in the opposite direction
//        // but applyting inverse model will distort the normal in the same direction
//        // as how the obj is distorted
//        normal_world = M3 * normal_world;
//        // apply light to the color
//        for (Light *light : m_rayLights) {
//            if (light) {
////                light->lit(tmp_color, closestShape, normal_world, hit_world, eye_w, m_rayShapes);
//            }
//        }

//        // apply reflection
//        if (settings.useReflection) {
//            float ks = 1.0f;
//            BGRA reflectColor = renderPixel(hit_world + 5 * EPSILON_F * ray_w,
//                                            glm::reflect(glm::normalize(ray_w), glm::normalize(normal_world)), // normal must be normalized
//                                                                                                                //to achieve correct result
//                                            recurDepth + 1);
//            tmp_color.r +=  ks * closestShape->material->cReflective.r * reflectColor.r;
//            tmp_color.g +=  ks * closestShape->material->cReflective.g * reflectColor.g;
//            tmp_color.b +=  ks * closestShape->material->cReflective.b * reflectColor.b;
//        }
//    }

//    // clamp max color value to 255
//    tmp_color.r = glm::clamp(tmp_color.r, static_cast<unsigned char>(0), static_cast<unsigned char>(255));
//    tmp_color.g = glm::clamp(tmp_color.g, static_cast<unsigned char>(0), static_cast<unsigned char>(255));
//    tmp_color.b = glm::clamp(tmp_color.b, static_cast<unsigned char>(0), static_cast<unsigned char>(255));

//    return tmp_color;
//}
