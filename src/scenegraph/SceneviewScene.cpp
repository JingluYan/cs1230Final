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

#include "lib/errorchecker.h"
#include "gl/datatype/FBO.h"
#include "gl/textures/Texture2D.h"
#include <random>

using namespace CS123::GL;


float lerp(float a, float b, float f)
{
    return a + f * (b - a);
}


 std::vector<glm::vec3> generateSampleKernel() {
     std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0); // generates random floats between 0.0 and 1.0
     std::vector<glm::vec3> ssaoKernel;
     std::default_random_engine generator;
     for (unsigned int i = 0; i < 128; ++i)
     {
         glm::vec3 sample(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
         sample = glm::normalize(sample);
         sample *= randomFloats(generator);
         float scale = float(i) / 128.0;

         // scale samples s.t. they're more aligned to center of kernel
         scale = lerp(0.1f, 1.0f, scale * scale);
         sample *= scale;
         ssaoKernel.push_back(sample);
     }
     return ssaoKernel;
 }


unsigned int generateNoiseTexture() {
     // generate noise texture
     // ----------------------
     std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0); // generates random floats between 0.0 and 1.0
     std::default_random_engine generator;
     std::vector<glm::vec3> ssaoNoise;
     for (unsigned int i = 0; i < 16; i++)
     {
         glm::vec3 noise(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, 0.0f); // rotate around z-axis (in tangent space)
         ssaoNoise.push_back(noise);
     }
     unsigned int noiseTexture; glGenTextures(1, &noiseTexture);
     glBindTexture(GL_TEXTURE_2D, noiseTexture);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     return noiseTexture;
 }

SceneviewScene::SceneviewScene()
{
}

SceneviewScene::SceneviewScene(int w, int h, float ratio) :
    m_width(w),
    m_height(h),
    m_ratio(ratio)
{
    loadPhongShader();
    loadDeferredShader();
    loadSSAOShader();
//    loadWireframeShader();
//    loadNormalsShader();
//    loadNormalsArrowShader();

    m_cube = std::make_unique<Cube>(settings.shapeParameter1);

    m_cone = std::make_unique<Cone>(settings.shapeParameter1, settings.shapeParameter2);

    m_cylinder = std::make_unique<Cylinder>(settings.shapeParameter1,settings.shapeParameter2);

    m_sphere = std::make_unique<Sphere>(settings.shapeParameter1, settings.shapeParameter2);

    // build full screen quad
    m_quad = std::make_unique<Quad>();


    //TODO: to be cleaned up
    m_ratio = 1.0f;

    // generate sample kernel
    // ----------------------
    ssaoKernel = generateSampleKernel();
    noiseTexture = generateNoiseTexture();
    m_gbuffer_FBO = std::make_unique<FBO>(6,
                                          FBO::DEPTH_STENCIL_ATTACHMENT::DEPTH_ONLY,
                                          m_width,
                                          m_height,
                                          TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE,
                                          TextureParameters::FILTER_METHOD::LINEAR,
                                          GL_FLOAT);
    m_SSAO_FBO = std::make_unique<FBO>(1,
                                          FBO::DEPTH_STENCIL_ATTACHMENT::DEPTH_ONLY,
                                          m_width,
                                          m_height,
                                          TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE,
                                          TextureParameters::FILTER_METHOD::LINEAR,
                                          GL_FLOAT);
    m_blur_FBO = std::make_unique<FBO>(1,
                                          FBO::DEPTH_STENCIL_ATTACHMENT::DEPTH_ONLY,
                                          m_width,
                                          m_height,
                                          TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE,
                                          TextureParameters::FILTER_METHOD::LINEAR,
                                          GL_FLOAT);

    // initialize ssaoFBO and its color attachment,
    // -----------------------------------------------------
    glGenFramebuffersEXT(1, &ssaoFBO);
    glBindFramebufferEXT(GL_FRAMEBUFFER, ssaoFBO);
    // SSAO color buffer
    glGenTextures(1, &ssaoColorBuffer);
    glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBuffer, 0);
    if (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "SSAO Framebuffer not complete!" << std::endl;
    // generate ssaoBlurFBO and its color attachment
    glGenFramebuffersEXT(1, &ssaoBlurFBO);
    glBindFramebufferEXT(GL_FRAMEBUFFER, ssaoBlurFBO);
    // SSAOColorBufferBlur
    glGenTextures(1, &ssaoColorBufferBlur);
    glBindTexture(GL_TEXTURE_2D, ssaoColorBufferBlur);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBufferBlur, 0);
    if (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "SSAO Blur Framebuffer not complete!" << std::endl;
    glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
}

SceneviewScene::~SceneviewScene()
{
}

void SceneviewScene::loadPhongShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/default.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/default.frag");
    m_phongShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void SceneviewScene::loadDeferredShader() {
    //load first pass
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/gbuffer.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/gbuffer.frag");
    m_gBufferShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);

    //load second pass
    std::string vertexSource2 = ResourceLoader::loadResourceFileToString(":/shaders/lighting.vert");
    std::string fragmentSource2 = ResourceLoader::loadResourceFileToString(":/shaders/lighting.frag");
    m_deferredLightingShader = std::make_unique<CS123Shader>(vertexSource2, fragmentSource2);
}

void SceneviewScene::loadSSAOShader() {
    //load SSAO pass
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/SSAO.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/SSAO.frag");
    m_SSAOShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);

    //load Blur pass
    std::string vertexSource2 = ResourceLoader::loadResourceFileToString(":/shaders/blur.vert");
    std::string fragmentSource2 = ResourceLoader::loadResourceFileToString(":/shaders/blur.frag");
    m_blurShader = std::make_unique<CS123Shader>(vertexSource2, fragmentSource2);
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

    // use deferred lighting
    if (settings.deferredLight) {
        // first pass
        m_gbuffer_FBO->bind();
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.5f, 0.5f, 0.5f, 0.5f); // has to go before glClear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_gBufferShader->bind();

        setSceneUniforms(context);
        renderGeometry();

        m_gBufferShader->unbind();
        m_gbuffer_FBO->unbind();

        // 2. generate SSAO texture
        // ------------------------
        glBindFramebufferEXT(GL_FRAMEBUFFER, ssaoFBO);
        glClearColor(0.5f, 0.5f, 0.5f, 0.5f); // has to go before glClear
        glClear(GL_COLOR_BUFFER_BIT);
        m_SSAOShader->bind();

        // Send kernel + rotation
        for (unsigned int i = 0; i < 64; ++i)
            m_SSAOShader->setUniformArrayByIndex("samples", ssaoKernel[i], i);
        m_SSAOShader->setUniform("projection", context->getCamera()->getProjectionMatrix());
        m_SSAOShader->setUniform("v", context->getCamera()->getViewMatrix());
        m_SSAOShader->setUniform("width", m_width);
        m_SSAOShader->setUniform("height", m_height);
        m_SSAOShader->setUniform("bias", settings.bias);
        m_SSAOShader->setUniform("radius", settings.radius);

        glActiveTextureARB(GL_TEXTURE0);
        m_gbuffer_FBO->getColorAttachment(0).bind();
        glActiveTextureARB(GL_TEXTURE1);
        m_gbuffer_FBO->getColorAttachment(1).bind();
        glActiveTextureARB(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, noiseTexture);

        m_quad->draw();

        m_SSAOShader->unbind();
        glBindFramebufferEXT(GL_FRAMEBUFFER, 0);


        // 3. blur SSAO texture to remove noise
        // ------------------------------------
        glBindFramebufferEXT(GL_FRAMEBUFFER, ssaoBlurFBO);
        glClear(GL_COLOR_BUFFER_BIT);
        m_blurShader->bind();

        glActiveTextureARB(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
        m_quad->draw();

        m_blurShader->unbind();
        glBindFramebufferEXT(GL_FRAMEBUFFER, 0);

        // second pass: lighting pass
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//        glDisable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, m_width * m_ratio, m_height * m_ratio);
        m_deferredLightingShader->bind();

        // setup uniforms in m_deferredLightingShader
        m_deferredLightingShader->setUniform("v", context->getCamera()->getViewMatrix());
        m_deferredLightingShader->setUniform("useLighting", settings.useFeatureLighting);
        m_deferredLightingShader->setUniform("lightCount", (int)lights.size()); 
        m_deferredLightingShader->setUniform("useSSAO", settings.SSAO);
        m_deferredLightingShader->setUniform("visualizeSSAO", settings.visualizeSSAO);
        m_deferredLightingShader->setUniform("ambient", settings.ambient);
        m_deferredLightingShader->setUniform("useBumpTexture", settings.bumpMapping);
        setLights();
        // bind the m_gbuffer_FBO texture attachments
        glActiveTextureARB(GL_TEXTURE0);
        m_gbuffer_FBO->getColorAttachment(0).bind();
        glActiveTextureARB(GL_TEXTURE1);
        m_gbuffer_FBO->getColorAttachment(1).bind();
        glActiveTextureARB(GL_TEXTURE2);
        m_gbuffer_FBO->getColorAttachment(2).bind();
        glActiveTextureARB(GL_TEXTURE3);
        m_gbuffer_FBO->getColorAttachment(3).bind();
        glActiveTextureARB(GL_TEXTURE4);
        m_gbuffer_FBO->getColorAttachment(4).bind();
        glActiveTextureARB(GL_TEXTURE5);
        m_gbuffer_FBO->getColorAttachment(5).bind();
        glActiveTextureARB(GL_TEXTURE6); // add extra SSAO texture to lighting pass
        glBindTexture(GL_TEXTURE_2D, ssaoColorBufferBlur);

        // pass the m_gbuffer_FBO texture attachments to uniforms
        // notice the 0, 1, 2 matches the index of the m_gbuffer_FBO->getColorAttachment(index)
        glUniform1iARB(glGetUniformLocationARB(m_deferredLightingShader->getID(), "gPosition"), 0);
        glUniform1iARB(glGetUniformLocationARB(m_deferredLightingShader->getID(), "gNormal"), 1);
        glUniform1iARB(glGetUniformLocationARB(m_deferredLightingShader->getID(), "gAlbedoSpec"), 2);
        glUniform1iARB(glGetUniformLocationARB(m_deferredLightingShader->getID(), "gTangent"), 3);
        glUniform1iARB(glGetUniformLocationARB(m_deferredLightingShader->getID(), "gBinormal"), 4);
        glUniform1iARB(glGetUniformLocationARB(m_deferredLightingShader->getID(), "gBumpNormal"), 5);
        glUniform1iARB(glGetUniformLocationARB(m_deferredLightingShader->getID(), "ssaoColor"), 6);
        m_quad->draw();

        m_deferredLightingShader->unbind();

    } else { // use default phong shader
        m_phongShader->bind();
        setSceneUniforms(context);
        setLights();

        renderGeometry();
        glBindTexture(GL_TEXTURE_2D, 0);
        m_phongShader->unbind();
    }
}

void SceneviewScene::setSceneUniforms(SupportCanvas3D *context) {
    Camera *camera = context->getCamera();
    if (settings.deferredLight) {
//        ErrorChecker::printGLErrors("line 154");
        m_gBufferShader->setUniform("p" , camera->getProjectionMatrix());
        m_gBufferShader->setUniform("v", camera->getViewMatrix());
//        ErrorChecker::printGLErrors("line 157");
    } else {
        m_phongShader->setUniform("useLighting", settings.useFeatureLighting);
        m_phongShader->setUniform("useArrowOffsets", false);
        m_phongShader->setUniform("p" , camera->getProjectionMatrix());
        m_phongShader->setUniform("v", camera->getViewMatrix());
    }
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
        if (settings.deferredLight) {
            m_deferredLightingShader->setLight(light);
        } else {
            m_phongShader->setLight(light);
        }
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
        if (settings.deferredLight) {
            m_gBufferShader->setUniform("m", pair.tranformation);
            m_gBufferShader->applyMaterial(pair.primitive.material);

        } else {
            m_phongShader->setUniform("m", pair.tranformation);
            m_phongShader->applyMaterial(pair.primitive.material);
        }

        //texture mapping
        if (settings.textureMapping){
            loadDiffuseMapData( pair.primitive.material );
            tryApplyDiffuseTexture( pair.primitive.material.textureMap );
        }

        //bump mapping
        if (settings.bumpMapping){
            loadBumpMapData ( pair.primitive.material );
            tryApplyBumpTexture( pair.primitive.material.bumpMap );
        }

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

//        ErrorChecker::printGLErrors("line 239");
    }
}

void SceneviewScene::settingsChanged() {
    // TODO: [SCENEVIEW] Fill this in if applicable.
    m_cube->update(settings.shapeParameter1);
    m_cylinder->update(settings.shapeParameter1, settings.shapeParameter2);
    m_sphere->update(settings.shapeParameter1, settings.shapeParameter2);
    m_cone->update(settings.shapeParameter1, settings.shapeParameter2);
}

void SceneviewScene::tryApplyDiffuseTexture( const CS123SceneFileMap &map ) {
    if (settings.deferredLight) {
        if (!map.isUsed) {
            m_gBufferShader->setUniform( "useTexture", 0 );
            return;
        }
        m_gBufferShader->setUniform( "useTexture", 1 );
        m_gBufferShader->setUniform( "repeatUV", glm::vec2{map.repeatU, map.repeatV});
        m_gBufferShader->setTexture( "tex", m_textures.at( map.filename ) );
    } else {
        if( !map.isUsed ) {
            m_phongShader->setUniform( "useTexture", 0 );
            return;
        }
        m_phongShader->setUniform( "useTexture", 1 );
        m_phongShader->setUniform( "repeatUV", glm::vec2{map.repeatU, map.repeatV});
        m_phongShader->setTexture( "tex", m_textures.at( map.filename ) );
    }
}

void SceneviewScene::tryApplyBumpTexture( const CS123SceneFileMap &map ) {
    if (settings.deferredLight) {
        if (!map.isUsed) {
            m_gBufferShader->setUniform( "useBumpTexture", 0 );
            return;
        }
        m_gBufferShader->setUniform( "useBumpTexture", 1 );
        m_gBufferShader->setUniform( "repeatBumpUV", glm::vec2{map.repeatU, map.repeatV});
        m_gBufferShader->setTexture( "texBump", m_bumpmaps.at( map.filename ) );
    } else {
        if( !map.isUsed ) {
            m_phongShader->setUniform( "useBumpTexture", 0 );
            return;
        }
        m_phongShader->setUniform( "useBumpTexture", 1 );
        m_phongShader->setUniform( "repeatBumpUV", glm::vec2{map.repeatU, map.repeatV});
        m_phongShader->setTexture( "texBump", m_bumpmaps.at( map.filename ) );
    }
}

void SceneviewScene::loadDiffuseMapData( const CS123SceneMaterial &material ) {
    // If texture is not used
    if(!((material.textureMap.isUsed ) && (material.textureMap.filename.compare( "" ))) )
             return;

    // If texture had already been loaded
    if( m_textures.find( material.textureMap.filename ) != m_textures.end() )
        return;

    QImage image = QImage( material.textureMap.filename.data() );
    QImage convertedImage = QGLWidget::convertToGLFormat( image );

    if( convertedImage.isNull() ) {
        return;
    }

    Texture2D texture( convertedImage.bits(), convertedImage.width(), convertedImage.height() );
    buildTexture( texture );
    m_textures.insert( std::make_pair( material.textureMap.filename, std::move( texture ) ) );
}

void SceneviewScene::loadBumpMapData( const CS123SceneMaterial &material ) {
    // If texture is not used
    if(!((material.bumpMap.isUsed ) && (material.bumpMap.filename.compare( "" ))))
             return;

    // If texture had already been loaded
    if( m_bumpmaps.find( material.bumpMap.filename ) != m_bumpmaps.end() )
        return;

    QImage image = QImage( material.bumpMap.filename.data() );
    QImage convertedImage = QGLWidget::convertToGLFormat( image );

    if( convertedImage.isNull() ) {
        return;
    }

    Texture2D texture( convertedImage.bits(), convertedImage.width(), convertedImage.height() );
    buildTexture( texture );
    m_bumpmaps.insert( std::make_pair( material.bumpMap.filename, std::move( texture ) ) );
}

void SceneviewScene::buildTexture( const Texture2D &texture ) {
    TextureParametersBuilder builder;
    builder.setFilter( TextureParameters::FILTER_METHOD::LINEAR );
    builder.setWrap( TextureParameters::WRAP_METHOD::REPEAT );
    TextureParameters parameters = builder.build();
    parameters.applyTo( texture );
}

void SceneviewScene::setWindowDim(int w, int h, float ratio) {
    m_width = w;
    m_height = h;
    m_ratio = ratio;
}
