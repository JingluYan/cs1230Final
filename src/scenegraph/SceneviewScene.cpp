#include "SceneviewScene.h"
#include "GL/glew.h"
#include <QGLWidget>
#include "Camera.h"

#include "Settings.h"
#include "SupportCanvas3D.h"
#include "ResourceLoader.h"
#include "gl/shaders/CS123Shader.h"
#include <set>
#include <iostream>

#include "gl/textures/Texture2D.h"
#include "gl/textures/TextureParameters.h"
#include "gl/textures/TextureParametersBuilder.h"

using namespace CS123::GL;


SceneviewScene::SceneviewScene()
{
    // TODO: [SCENEVIEW] Set up anything you need for your Sceneview scene here...
    loadPhongShader();
    loadWireframeShader();
    loadNormalsShader();
    loadNormalsArrowShader();

    m_cube = std::make_unique<Cube>(settings.shapeParameter1);

    m_cone = std::make_unique<Cone>(settings.shapeParameter1, settings.shapeParameter2);

    m_cylinder = std::make_unique<Cylinder>(settings.shapeParameter1,settings.shapeParameter2);

    m_sphere = std::make_unique<Sphere>(settings.shapeParameter1, settings.shapeParameter2);
}

SceneviewScene::~SceneviewScene()
{
}

void SceneviewScene::loadPhongShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/default.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/default.frag");
    m_phongShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void SceneviewScene::loadWireframeShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/wireframe.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/wireframe.frag");
    m_wireframeShader = std::make_unique<Shader>(vertexSource, fragmentSource);
}

void SceneviewScene::loadNormalsShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/normals.vert");
    std::string geometrySource = ResourceLoader::loadResourceFileToString(":/shaders/normals.gsh");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/normals.frag");
    m_normalsShader = std::make_unique<Shader>(vertexSource, geometrySource, fragmentSource);
}

void SceneviewScene::loadNormalsArrowShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/normalsArrow.vert");
    std::string geometrySource = ResourceLoader::loadResourceFileToString(":/shaders/normalsArrow.gsh");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/normalsArrow.frag");
    m_normalsArrowShader = std::make_unique<Shader>(vertexSource, geometrySource, fragmentSource);
}

void SceneviewScene::render(SupportCanvas3D *context) {
    setClearColor();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_phongShader->bind();
    setSceneUniforms(context);
    setLights();
    renderGeometry();
    glBindTexture(GL_TEXTURE_2D, 0);
    m_phongShader->unbind();

}

void SceneviewScene::setSceneUniforms(SupportCanvas3D *context) {
    Camera *camera = context->getCamera();
    m_phongShader->setUniform("useLighting", settings.useLighting);
    m_phongShader->setUniform("useArrowOffsets", false);
    m_phongShader->setUniform("p" , camera->getProjectionMatrix());
    m_phongShader->setUniform("v", camera->getViewMatrix());
}

void SceneviewScene::setMatrixUniforms(Shader *shader, SupportCanvas3D *context) {
    shader->setUniform("p", context->getCamera()->getProjectionMatrix());
    shader->setUniform("v", context->getCamera()->getViewMatrix());
}

void SceneviewScene::setLights()
{
    // TODO: [SCENEVIEW] Fill this in...
    //
    // Set up the lighting for your scene using m_phongShader.
    // The lighting information will most likely be stored in CS123SceneLightData structures.
    //
    for (CS123SceneLightData light : lights) {
        m_phongShader->setLight(light);
    }
}

void SceneviewScene::renderGeometry() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // TODO: [SCENEVIEW] Fill this in...
    // You shouldn't need to write *any* OpenGL in this class!
    //
    //
    // This is where you should render the geometry of the scene. Use what you
    // know about OpenGL and leverage your Shapes classes to get the job done.
    //

    for (PrimTransPair pair : primTransPairs) {
        m_phongShader->setUniform("m", pair.tranformation);
        m_phongShader->applyMaterial(pair.primitive.material);

        //texture map
        loadMaterialData( pair.primitive.material );
        tryApplyTexture( pair.primitive.material.textureMap );

        switch (pair.primitive.type) {
            case PrimitiveType::PRIMITIVE_CUBE:
            m_cube->draw();
            break;
            case PrimitiveType::PRIMITIVE_CONE:
            m_cone->draw();
            break;
            case PrimitiveType::PRIMITIVE_CYLINDER:
            m_cylinder->draw();
            break;
            case PrimitiveType::PRIMITIVE_SPHERE:
            m_sphere->draw();
            break;
            default:
            //TODO: Should I do anything here? will I encounter odd shapes
            continue;
        }
    }
}

void SceneviewScene::settingsChanged() {
    // TODO: [SCENEVIEW] Fill this in if applicable.
    m_cube->update(settings.shapeParameter1);
    m_cylinder->update(settings.shapeParameter1, settings.shapeParameter2);
    m_sphere->update(settings.shapeParameter1, settings.shapeParameter2);
    m_cone->update(settings.shapeParameter1, settings.shapeParameter2);
}

void SceneviewScene::tryApplyTexture( const CS123SceneFileMap &map ) {
    if( !map.isUsed ) {
        m_phongShader->setUniform( "useTexture", 0 );
        return;
    }
    m_phongShader->setUniform( "useTexture", 1 );
    m_phongShader->setUniform( "repeatUV", glm::vec2{1,1});
    m_phongShader->setTexture( "tex", m_textures.at( map.filename ) );
}

void SceneviewScene::loadMaterialData( const CS123SceneMaterial &material ) {
    // If texture is not used
    if(!(material.textureMap.isUsed ) && (material.textureMap.filename.compare( "" )) )
             return;

    // If texture had already been loaded
    if( m_textures.find( material.textureMap.filename ) != m_textures.end() )
        return;

    QImage image = QImage( material.textureMap.filename.data() );
    QImage convertedImage = QGLWidget::convertToGLFormat( image );

    if( convertedImage.isNull() ) {
        std::cerr << "Could not read file: " << material.textureMap.filename << std::endl;
        return;
    }

    Texture2D texture( convertedImage.bits(), convertedImage.width(), convertedImage.height() );
    buildTexture( texture );
    m_textures.insert( std::make_pair( material.textureMap.filename, std::move( texture ) ) );
}

void SceneviewScene::buildTexture( const Texture2D &texture ) {
    TextureParametersBuilder builder;
    builder.setFilter( TextureParameters::FILTER_METHOD::LINEAR );
    builder.setWrap( TextureParameters::WRAP_METHOD::REPEAT );
    TextureParameters parameters = builder.build();
    parameters.applyTo( texture );
}
