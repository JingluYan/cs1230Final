#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <glm.hpp>
#include <vector>
#include <memory>
#include "camera/Camera.h"
#include "BGRA.h"
#include <unordered_map>
#include <QImage>

class Camera;
class BGRA;
class RayShape;
class Light;


class RayTracer
{
public:
    RayTracer(std::vector<RayShape*> rayShapes,
              std::vector<Light*> rayLights,
              std::unordered_map<std::string, QImage> fileImageHash,
              Camera* camera,
              BGRA* canvas,
              int width,
              int height);
    void render();
    void render(int x1, int y1, int x2, int y2);
    glm::vec3 renderPixel(glm::vec3 eye_w, glm::vec3 ray_w, int recurDepth);
    std::vector<RayShape*> m_rayShapes;
    std::vector<Light*> m_rayLights;
    std::unordered_map<std::string, QImage> m_fileNameToTexture;
    Camera* m_camera;
    BGRA* m_canvas;
    int canvas_width;
    int canvas_height;
};

#endif // RAYTRACER_H
