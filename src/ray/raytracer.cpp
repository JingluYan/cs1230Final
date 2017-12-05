#include "raytracer.h"
#include <iostream>
#include "ray/rayutils.h"
#include <limits>
#include "rayshape.h"
#include "light.h"
#include "Settings.h"
#include <QThreadPool>
#include "rendertask.h"
#include <QColor>

RayTracer::RayTracer(std::vector<RayShape *> rayShapes,
                     std::vector<Light *> rayLights,
                     std::unordered_map<std::string, QImage> fileImageHash,
                     Camera *camera,
                     BGRA *canvas,
                     int width,
                     int height) :
    m_rayShapes(rayShapes),
    m_rayLights(rayLights),
    m_camera(camera),
    m_canvas(canvas),
    m_fileNameToTexture(fileImageHash),
    canvas_width(width),
    canvas_height(height)
{

}

void RayTracer::render() {
    QThreadPool threadPool;
    int tiles = 2; // num of tiles in each direction, so total tiles = 4
                    // dept machine is 4 cores, so no point of going more than 4
    int tileSize = std::max(canvas_height / tiles, canvas_width / tiles) + 1;
    for (int y = 0; y < canvas_height; y += tileSize) {
        for (int x = 0; x < canvas_width; x += tileSize) {
            int x2 = std::min(canvas_width, x + tileSize);
            int y2 = std::min(canvas_height, y + tileSize);
            if (settings.useMultiThreading) {
                threadPool.start(new RenderTask(this, x, y, x2, y2));
            } else {
                render(x, y, x2, y2);
            }
        }
    }
}


void RayTracer::render(int x1, int y1, int x2, int y2) {
    glm::mat4 inverseViewMat = glm::inverse(m_camera->getViewMatrix());
    glm::mat4 inverseScaleMat = glm::inverse(m_camera->getScaleMatrix());
    glm::mat4 inverseViewScaleMat = inverseViewMat * inverseScaleMat;
    glm::vec3 eye = (inverseViewScaleMat * glm::vec4(0,0,0,1)).xyz(); //world space cam pos

    int pixIndx = y1 * canvas_width + x1;
    for (int y = y1; y < y2; y++) {
        for (int x = x1; x < x2; x++) {
            glm::vec3 pfilm = glm::vec3((2 * (float)x / (float)canvas_width) - 1, 1 - (2 * (float)y / (float)canvas_height), -1);
            glm::vec3 pworld = mat4DotVec3(inverseViewScaleMat, pfilm, true);
            glm::vec3 ray = pworld - eye;
            glm::vec3 color = renderPixel(eye, ray, 0);
            m_canvas[pixIndx] = BGRA(static_cast<unsigned char>(color.r), static_cast<unsigned char>(color.g), static_cast<unsigned char>(color.b));
            pixIndx++;
        }
        pixIndx += canvas_width - (x2 - x1);
    }
}

glm::vec3 RayTracer::renderPixel(glm::vec3 eye_w, glm::vec3 ray_w, int recurDepth) {
    if (recurDepth > MAX_RECURSION_DEPTH) return glm::vec3(0.0f);

    double t = std::numeric_limits<double>::max();
    // find the closest intersect shape
    RayShape *closestShape = nullptr;
    for (RayShape *shape : m_rayShapes) {
        glm::mat4 inverseModelMat = glm::inverse(shape->modelMatrix);
        glm::vec3 obj_eye = mat4DotVec3(inverseModelMat, eye_w, true);
        // DO NOT normalize obj_ray
        glm::vec3 obj_ray = mat4DotVec3(inverseModelMat, ray_w, false);
        double tmp_t = std::numeric_limits<double>::max();
        if (shape->intersect(obj_eye, obj_ray, tmp_t)) {
            if (tmp_t < t && tmp_t > 0) {
                t = tmp_t;
                closestShape = shape;
            }

        }
    }

    //tmp_color is the color of current pixel
    glm::vec3 tmp_color;

    //if there is an intersect
    if (closestShape) {
        //add ambient here and then add light contribution for each light
        // ka has been multiplied into the material's ambient color
        // so no need to multiple by ka again, but still leave it in to comply with formula
        float ka = 1.0f;
        tmp_color.r = ka * closestShape->material->cAmbient.r * 255;
        tmp_color.b = ka * closestShape->material->cAmbient.b * 255;
        tmp_color.g = ka * closestShape->material->cAmbient.g * 255;

        //get the hit point in world space
        glm::vec3 hit_w = eye_w + ray_w * static_cast<float>(t);
        // transform the hit point from world space to object space
        glm::vec3 hit_obj = mat4DotVec3(glm::inverse(closestShape->modelMatrix), hit_w, true);

        // get the world space normal of the hit point
        //closestShape->getNormal returns normal in obj space
        glm::vec3 normal_world = closestShape->getNormal(hit_obj);

        // add texture
        glm::vec3 textureColor(0);
        if (settings.useTextureMapping && closestShape->material->textureMap.isUsed) {
            glm::vec2 uv = closestShape->getUV(hit_obj);
            float repeatU = closestShape->material->textureMap.repeatU;
            float repeatV = closestShape->material->textureMap.repeatV;
            QImage tex = m_fileNameToTexture[closestShape->material->textureMap.filename];
            int w = tex.width();
            int h = tex.height();
            int s = ((int)(uv[0] * repeatU * w)) % w;
            int t = ((int)(uv[1] * repeatV * h)) % h;
            QRgb rgb = tex.pixel(s, t);
            float r = (float)qRed(rgb);
            float g = (float)qGreen(rgb);
            float b = (float)qBlue(rgb);
            textureColor.r = r;
            textureColor.g = g;
            textureColor.b = b;
        }

        // need to transform the normal from object space to world space
        // by discarding the translation of the modelmatrix
        // and then inverse transpose. See slide for details
        glm::mat4 model = closestShape->modelMatrix;
        glm::mat3 M3 = glm::mat3(model); // init M3 with the upper left 3x3 cells of model
        M3 = glm::inverse(glm::transpose(M3));
        // NOTE: It is WRONG to apply inverse model transform to the normal
        // because scale will distort object's normal in the opposite direction
        // but applyting inverse model will distort the normal in the same direction
        // as how the obj is distorted
        normal_world = glm::normalize(M3 * normal_world);
        // apply light to the color
        for (Light *light : m_rayLights) {
            if (light) {
                light->lit(tmp_color, closestShape, normal_world, hit_w, eye_w, textureColor, m_rayShapes);
            }
        }

        // apply reflection
        if (settings.useReflection) {
            float ks = 1.0f;
            glm::vec3 reflectColor = renderPixel(hit_w + 5 * EPSILON_F * ray_w,
                                            glm::reflect(glm::normalize(ray_w), glm::normalize(normal_world)), // normal must be normalized
                                                                                                                //to achieve correct result
                                            recurDepth + 1);
            tmp_color.r +=  ks * closestShape->material->cReflective.r * reflectColor.r;
            tmp_color.g +=  ks * closestShape->material->cReflective.g * reflectColor.g;
            tmp_color.b +=  ks * closestShape->material->cReflective.b * reflectColor.b;
        }
    }

    // clamp max color value to 255
    tmp_color.r = glm::clamp(tmp_color.r, .0f, 255.f);
    tmp_color.g = glm::clamp(tmp_color.g, .0f, 255.f);
    tmp_color.b = glm::clamp(tmp_color.b, .0f, 255.f);

    return tmp_color;
}
