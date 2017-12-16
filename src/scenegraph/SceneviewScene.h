#ifndef SCENEVIEWSCENE_H
#define SCENEVIEWSCENE_H

#include "OpenGLScene.h"

#include <memory>
#include <map>

#include "scenegraph/shapes/cone.h"
#include "scenegraph/shapes/cube.h"
#include "scenegraph/shapes/cylinder.h"
#include "scenegraph/shapes/sphere.h"
#include "scenegraph/shapes/quad.h"
#include "scenegraph/shapes/plane.h"

namespace CS123 { namespace GL {

    class Shader;
    class CS123Shader;
    class Texture2D;
    class FBO;
}}

/**
 *
 * @class SceneviewScene
 *
 * A complex scene consisting of multiple objects. Students will implement this class in the
 * Sceneview assignment.
 *
 * Here you will implement your scene graph. The structure is up to you - feel free to create new
 * classes and data structures as you see fit. We are providing this SceneviewScene class for you
 * to use as a stencil if you like.
 *
 * Keep in mind that you'll also be rendering entire scenes in the next two assignments, Intersect
 * and Ray. The difference between this assignment and those that follow is here, we are using
 * OpenGL to do the rendering. In Intersect and Ray, you will be responsible for that.
 */
class SceneviewScene : public OpenGLScene {
public:
    SceneviewScene();
    SceneviewScene(int w, int h, float ratio);
    void init();
    virtual ~SceneviewScene();

    virtual void render(SupportCanvas3D *context) override;
    virtual void settingsChanged() override;

    // Use this method to set an internal selection, based on the (x, y) position of the mouse
    // pointer.  This will be used during the "modeler" lab, so don't worry about it for now.
    void setSelection(int x, int y);

    void setWindowDim(int w, int h, float ratio);

private:

    void loadPhongShader();
    void loadDeferredShader();
    void loadSSAOShader();

    void setSceneUniforms(SupportCanvas3D *context);\
    void setMatrixUniforms(CS123::GL::Shader *shader, SupportCanvas3D *context);
    void setLights();
    void renderGeometry();

    std::unique_ptr<CS123::GL::CS123Shader> m_phongShader;
    std::unique_ptr<CS123::GL::Shader> m_wireframeShader;
    std::unique_ptr<CS123::GL::Shader> m_normalsShader;
    std::unique_ptr<CS123::GL::Shader> m_normalsArrowShader;
    std::unique_ptr<CS123::GL::CS123Shader> m_gBufferShader;
    std::unique_ptr<CS123::GL::CS123Shader> m_deferredLightingShader;
    std::unique_ptr<CS123::GL::CS123Shader> m_SSAOShader;
    std::unique_ptr<CS123::GL::CS123Shader> m_blurShader;
    std::unique_ptr<Cube> m_cube;               ///cube
    std::unique_ptr<Cylinder> m_cylinder;       ///cylinder
    std::unique_ptr<Cone> m_cone;               ///cone
    std::unique_ptr<Sphere> m_sphere;           ///sphere
    std::unique_ptr<Plane> m_plane;             ///plane

    std::unique_ptr<OpenGLShape> m_quad;        /// full screen quad

    // texture map
    std::map<std::string,CS123::GL::Texture2D> m_textures;
    void tryApplyDiffuseTexture( const CS123SceneFileMap &map );
    void loadDiffuseMapData( const CS123SceneMaterial &material );

    // bump map
    std::map<std::string,CS123::GL::Texture2D> m_bumpmaps;
    void tryApplyBumpTexture( const CS123SceneFileMap &map );
    void loadBumpMapData( const CS123SceneMaterial &material );

    void buildTexture( const CS123::GL::Texture2D &texture );

    int m_width;  /// window width
    int m_height;
    float m_ratio; // resolution
    std::unique_ptr<FBO> m_gbuffer_FBO;
    std::unique_ptr<FBO> m_tmp_FBO;
    std::unique_ptr<FBO> m_SSAO_FBO;
    std::unique_ptr<FBO> m_blur_FBO;

    std::vector<glm::vec3> ssaoKernel;
    unsigned int noiseTexture;
    unsigned int ssaoFBO, ssaoBlurFBO;
    unsigned int ssaoColorBuffer, ssaoColorBufferBlur;

};

#endif // SCENEVIEWSCENE_H
