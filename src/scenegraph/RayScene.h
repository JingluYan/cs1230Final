#ifndef RAYSCENE_H
#define RAYSCENE_H

#include "Scene.h"

#include <vector>
#include "ray/light.h"
#include "ray/rayshape.h"
#include <QImage>
#include <unordered_map>

class Camera;
class BGRA;

/**
 * @class RayScene
 *
 *  Students will implement this class as necessary in the Ray project.
 */
class RayScene : public Scene {
public:
    RayScene(Scene &scene);
//    void render(int width, int height, Camera *camera, BGRA* canvas);
//    BGRA renderPixel(glm::vec3 eye_w,
//                glm::vec3 ray_w,
//                int recurDepth);

    virtual ~RayScene();

    std::vector<RayShape*> m_rayShapes;
    std::vector<Light*> m_rayLights;
    std::vector<QImage*> m_textures;
//    std::vector<QImage*> m_bumpmaps;
    std::unordered_map<std::string, QImage> m_fileNameToTexture;
    std::unordered_map<std::string, QImage> m_fileNameToBumpMap;
};

#endif // RAYSCENE_H
