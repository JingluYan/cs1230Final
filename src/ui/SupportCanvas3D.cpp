#include "SupportCanvas3D.h"

#include <QFileDialog>
#include <QMouseEvent>
#include <QMessageBox>
#include <QApplication>

#include "BGRA.h"
#include "CamtransCamera.h"
#include "OrbitingCamera.h"
#include "SceneviewScene.h"
#include "Settings.h"
#include "ShapesScene.h"

#include <iostream>
#include "gl/GLDebug.h"
#include "CS123XmlSceneParser.h"
#include "lib/cubeData.h"
#include "ResourceLoader.h"
//#include "lib/errorchecker.h"


UniformVariable *SupportCanvas3D::s_skybox = NULL;
UniformVariable *SupportCanvas3D::s_projection = NULL;
UniformVariable *SupportCanvas3D::s_model = NULL;
UniformVariable *SupportCanvas3D::s_view = NULL;
UniformVariable *SupportCanvas3D::s_mvp = NULL;
UniformVariable *SupportCanvas3D::s_time = NULL;
UniformVariable *SupportCanvas3D::s_size = NULL;
UniformVariable *SupportCanvas3D::s_mouse = NULL;
std::vector<UniformVariable*> *SupportCanvas3D::s_staticVars = NULL;

SupportCanvas3D::SupportCanvas3D(QGLFormat format, QWidget *parent) : QGLWidget(format, parent),
    m_isDragging(false),
    m_settingsDirty(true),
    m_defaultPerspectiveCamera(new CamtransCamera()),
    m_defaultOrbitingCamera(new OrbitingCamera()),
    m_currentScene(nullptr)
{
    //for skybox
    s_staticVars = new std::vector<UniformVariable*>();
    m_ratio = static_cast<QGuiApplication*>(QCoreApplication::instance())->devicePixelRatio();

}

SupportCanvas3D::~SupportCanvas3D()
{
    delete skybox_shader;
    delete current_shader;
    for(unsigned int i = 0; i < s_staticVars->size(); i++) {
        UniformVariable* item = (*s_staticVars)[i];
        delete item;
    }
    delete s_staticVars;
}

Camera *SupportCanvas3D::getCamera() {
    switch(settings.getCameraMode()) {
        case CAMERAMODE_CAMTRANS:
            return m_defaultPerspectiveCamera.get();

        case CAMERAMODE_ORBIT:
            return m_defaultOrbitingCamera.get();

        default:
            return nullptr;
    }
}

OrbitingCamera *SupportCanvas3D::getOrbitingCamera() {
    return m_defaultOrbitingCamera.get();
}


CamtransCamera *SupportCanvas3D::getCamtransCamera() {
    return m_defaultPerspectiveCamera.get();
}

void SupportCanvas3D::initializeGL() {
    m_ratio = static_cast<QGuiApplication*>(QCoreApplication::instance())->devicePixelRatio();

    // Track the camera settings so we can generate deltas
    m_oldPosX = settings.cameraPosX;
    m_oldPosY = settings.cameraPosY;
    m_oldPosZ = settings.cameraPosZ;
    m_oldRotU = settings.cameraRotU;
    m_oldRotV = settings.cameraRotV;
    m_oldRotN = settings.cameraRotN;

    initializeGlew();

    initializeOpenGLSettings();
    initializeScenes();
    setSceneFromSettings();

    settingsChanged();

    //init skybox
    skybox_shader = ResourceLoader::newShaderProgram(context(), ":/shaders/skybox.vert", ":/shaders/skybox.frag");

    s_skybox = new UniformVariable(this->context()->contextHandle());
    s_skybox->setName("skybox");
    s_skybox->setType(UniformVariable::TYPE_TEXCUBE);
    //top, bottom, left, right, front, back
    s_skybox->parse(":/skybox/posy.jpg,:/skybox/negy.jpg,:/skybox/negx.jpg,:/skybox/posx.jpg,:/skybox/posz.jpg,:/skybox/negz.jpg");

    s_model = new UniformVariable(this->context()->contextHandle());
    s_model->setName("model");
    s_model->setType(UniformVariable::TYPE_MAT4);
    s_model->parse("1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1");

    s_projection = new UniformVariable(this->context()->contextHandle());
    s_projection->setName("projection");
    s_projection->setType(UniformVariable::TYPE_MAT4);

    s_view = new UniformVariable(this->context()->contextHandle());
    s_view->setName("view");
    s_view->setType(UniformVariable::TYPE_MAT4);

    s_mvp = new UniformVariable(this->context()->contextHandle());
    s_mvp->setName("mvp");
    s_mvp->setType(UniformVariable::TYPE_MAT4);

    s_time = new UniformVariable(this->context()->contextHandle());
    s_time->setName("time");
    s_time->setType(UniformVariable::TYPE_TIME);

    s_size = new UniformVariable(this->context()->contextHandle());
    s_size->setName("size");
    s_size->setType(UniformVariable::TYPE_FLOAT2);

    s_mouse = new UniformVariable(this->context()->contextHandle());
    s_mouse->setName("mouse");
    s_mouse->setType(UniformVariable::TYPE_FLOAT3);

    s_staticVars->push_back(s_skybox);
    s_staticVars->push_back(s_model);
    s_staticVars->push_back(s_projection);
    s_staticVars->push_back(s_view);
    s_staticVars->push_back(s_mvp);
    s_staticVars->push_back(s_time);
    s_staticVars->push_back(s_size);
    s_staticVars->push_back(s_mouse);


    gl = QOpenGLFunctions(context()->contextHandle());

    QString error;
    loadShader(":/shaders/default.vert", ":/shaders/default.frag", &error);

    //init a sphere to test why nothing shows up
    std::vector<GLfloat> sphereData = SPHERE_VERTEX_POSITIONS;
    m_sphere = std::make_unique<OpenGLShape>();
    m_sphere->setVertexData(&sphereData[0], sphereData.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, NUM_SPHERE_VERTICES);
    m_sphere->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_sphere->setAttribute(ShaderAttrib::NORMAL, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_sphere->buildVAO();

    std::vector<float> cubeData = CUBE_DATA_POSITIONS;
    skybox_cube = std::make_unique<OpenGLShape>();
    skybox_cube->setVertexData(&cubeData[0], cubeData.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, NUM_CUBE_VERTICES);
    skybox_cube->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    skybox_cube->setAttribute(ShaderAttrib::NORMAL, 3, 3*sizeof(GLfloat), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    skybox_cube->buildVAO();

    s_projection = new UniformVariable(this->context()->contextHandle());
    s_projection->setName("projection");
    s_projection->setType(UniformVariable::TYPE_MAT4);

    s_view = new UniformVariable(this->context()->contextHandle());
    s_view->setName("view");
    s_view->setType(UniformVariable::TYPE_MAT4);

    //end skybox init code
}


bool SupportCanvas3D::loadShader(QString vert, QString frag, QString *errors)
{
    QGLShaderProgram *new_shader = ResourceLoader::newShaderProgram(context(), vert, frag, errors);
    if (new_shader == NULL) {
        return false;
    }

//    delete wireframe_shader2;
//    wireframe_shader2 = ResourceLoader::newShaderProgram(context(), vert, ":/shaders/color.frag", errors);

//    UniformVariable::s_numTextures = 2;

//    UniformVariable::resetTimer();

    // http://stackoverflow.com/questions/440144/in-opengl-is-there-a-way-to-get-a-list-of-all-uniforms-attribs-used-by-a-shade

    std::vector<GLchar> nameData(256);
    GLint numActiveUniforms = 0;
    gl.glGetProgramiv(new_shader->programId(), GL_ACTIVE_UNIFORMS, &numActiveUniforms);

    for (int unif = 0; unif < numActiveUniforms; unif++) {
        GLint arraySize = 0;
        GLenum type = 0;
        GLsizei actualLength = 0;
        gl.glGetActiveUniform(new_shader->programId(), unif, nameData.size(), &actualLength, &arraySize, &type, &nameData[0]);
        std::string name((char*)&nameData[0], actualLength);

        UniformVariable::Type uniformType = UniformVariable::typeFromGLEnum(type);

        QString qname = QString::fromStdString(name);
        if (qname.startsWith("gl_")) continue;
        emit(addUniform(uniformType, qname, true, arraySize));
    }

//    delete current_shader;
    current_shader = new_shader;
//    camera->mouseScrolled(0);
//    camera->updateMats();
    update();
    return true;
}


void SupportCanvas3D::initializeGlew() {
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    glGetError(); // Clear errors after call to glewInit
    if (GLEW_OK != err) {
      // Problem: glewInit failed, something is seriously wrong.
      fprintf(stderr, "Error initializing glew: %s\n", glewGetErrorString(err));
    }
}

void SupportCanvas3D::initializeOpenGLSettings() {
    // Enable depth testing, so that objects are occluded based on depth instead of drawing order.
    glEnable(GL_DEPTH_TEST);

    // Move the polygons back a bit so lines are still drawn even though they are coplanar with the
    // polygons they came from, which will be drawn before them.
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-1, -1);

    // Enable back-face culling, meaning only the front side of every face is rendered.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Specify that the front face is represented by vertices in counterclockwise order (this is
    // the default).
    glFrontFace(GL_CCW);

    //init for the skybox
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_CUBE_MAP);

    glDisable(GL_COLOR_MATERIAL);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    // end skybox code

    // Calculate the orbiting camera matrices.
    getOrbitingCamera()->updateMatrices();
}

void SupportCanvas3D::initializeScenes() {
    m_sceneviewScene = std::make_unique<SceneviewScene>(width(), height(), m_ratio);
    m_shapesScene = std::make_unique<ShapesScene>(width(), height());
}

void SupportCanvas3D::paintGL() {

    if (m_settingsDirty) {
        setSceneFromSettings();
    }
//    ErrorChecker::printGLErrors("line 95");

    float ratio = static_cast<QGuiApplication*>(QCoreApplication::instance())->devicePixelRatio();
    glViewport(0, 0, width() * ratio, height() * ratio);
    getCamera()->setAspectRatio(static_cast<float>(width()) / static_cast<float>(height()));
    m_currentScene->render(this);

    // draw skybox
    skybox_shader->bind();
    s_skybox->setValue(skybox_shader);
    s_projection->setValue(skybox_shader);
    s_view->setValue(skybox_shader);
    glCullFace(GL_FRONT);
    skybox_cube->draw();
    glCullFace(GL_BACK);
    skybox_shader->release();

    // draw test sphere
    if (current_shader) {
        current_shader->bind();

//        foreach (const UniformVariable *var, *activeUniforms) {
//            var->setValue(current_shader);
//        }
    }

    m_sphere->draw();
    if (current_shader) {
        current_shader->release();
    }

    // end skybox draw
}

void SupportCanvas3D::settingsChanged() {
    m_settingsDirty = true;
    if (m_currentScene != nullptr) {
        // Just calling this function so that the scene is always updated.
        setSceneFromSettings();
        m_currentScene->settingsChanged();
    }
    update(); /* repaint the scene */
}

void SupportCanvas3D::setSceneFromSettings() {
    switch(settings.getSceneMode()) {
        case SCENEMODE_SHAPES:
            setSceneToShapes();
            break;
        case SCENEMODE_SCENEVIEW:
            setSceneToSceneview();
            break;
    }
    m_settingsDirty = false;
}

void SupportCanvas3D::loadSceneviewSceneFromParser(CS123XmlSceneParser &parser) {
    m_sceneviewScene = std::make_unique<SceneviewScene>(width(), height(), m_ratio);
    Scene::parse(m_sceneviewScene.get(), &parser);
    m_settingsDirty = true;
}

void SupportCanvas3D::setSceneToSceneview() {
    assert(m_sceneviewScene.get());
    m_currentScene = m_sceneviewScene.get();
}

void SupportCanvas3D::setSceneToShapes() {
    assert(m_shapesScene.get());
    m_currentScene = m_shapesScene.get();
}

void SupportCanvas3D::copyPixels(int width, int height, BGRA *data) {
    glReadPixels(0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, data);
    std::cout << "copied " << width << "x" << height << std::endl;

    // Flip the image and since OpenGL uses an origin in the lower left and we an origin in the
    // upper left.
    for (int y = 0; y < (height + 1) / 2; y++)
        for (int x = 0; x < width; x++)
            std::swap(data[x + y * width], data[x + (height - y - 1) * width]);
}

void SupportCanvas3D::resetUpVector() {
    // Reset the up vector to the y axis
    glm::vec4 up = glm::vec4(0.f, 1.f, 0.f, 0.f);
    if (fabs(glm::length(m_defaultPerspectiveCamera->getUp() - up)) > 0.0001f) {
        m_defaultPerspectiveCamera->orientLook(
                    m_defaultPerspectiveCamera->getPosition(),
                    m_defaultPerspectiveCamera->getLook(),
                    up);
        update();
    }
}


void SupportCanvas3D::setCameraAxisX() {
    m_defaultPerspectiveCamera->orientLook(
                glm::vec4(2.f, 0.f, 0.f, 1.f),
                glm::vec4(-1.f, 0.f, 0.f, 0.f),
                glm::vec4(0.f, 1.f, 0.f, 0.f));
    update();
}

void SupportCanvas3D::setCameraAxisY() {
    m_defaultPerspectiveCamera->orientLook(
                glm::vec4(0.f, 2.f, 0.f, 1.f),
                glm::vec4(0.f, -1.f, 0.f, 0.f),
                glm::vec4(0.f, 0.f, 1.f, 0.f));
    update();
}

void SupportCanvas3D::setCameraAxisZ() {
    m_defaultPerspectiveCamera->orientLook(
                glm::vec4(0.f, 0.f, 2.f, 1.f),
                glm::vec4(0.f, 0.f, -1.f, 0.f),
                glm::vec4(0.f, 1.f, 0.f, 0.f));
    update();
}

void SupportCanvas3D::setCameraAxonometric() {
    m_defaultPerspectiveCamera->orientLook(
                glm::vec4(2.f, 2.f, 2.f, 1.f),
                glm::vec4(-1.f, -1.f, -1.f, 0.f),
                glm::vec4(0.f, 1.f, 0.f, 0.f));
    update();
}

void SupportCanvas3D::updateCameraHeightAngle() {
    // The height angle is half the overall field of view of the camera
    m_defaultPerspectiveCamera->setHeightAngle(settings.cameraFov/2);
}

void SupportCanvas3D::updateCameraTranslation() {
    m_defaultPerspectiveCamera->translate(
            glm::vec4(
                settings.cameraPosX - m_oldPosX,
                settings.cameraPosY - m_oldPosY,
                settings.cameraPosZ - m_oldPosZ,
                0));

    m_oldPosX = settings.cameraPosX;
    m_oldPosY = settings.cameraPosY;
    m_oldPosZ = settings.cameraPosZ;
}

void SupportCanvas3D::updateCameraRotationU() {
    m_defaultPerspectiveCamera->rotateU(settings.cameraRotU - m_oldRotU);
    m_oldRotU = settings.cameraRotU;
}

void SupportCanvas3D::updateCameraRotationV() {
    m_defaultPerspectiveCamera->rotateV(settings.cameraRotV - m_oldRotV);
    m_oldRotV = settings.cameraRotV;
}

void SupportCanvas3D::updateCameraRotationN() {
    m_defaultPerspectiveCamera->rotateW(settings.cameraRotN - m_oldRotN);
    m_oldRotN = settings.cameraRotN;
}

void SupportCanvas3D::updateCameraClip() {
    m_defaultPerspectiveCamera->setClip(settings.cameraNear, settings.cameraFar);
}


void SupportCanvas3D::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        getCamera()->mouseDown(event->x(), event->y());
        m_isDragging = true;
        update();
    }
}

void SupportCanvas3D::mouseMoveEvent(QMouseEvent *event) {
    if (m_isDragging) {
        getCamera()->mouseDragged(event->x(), event->y());
        update();
    }
}

void SupportCanvas3D::mouseReleaseEvent(QMouseEvent *event) {
    if (m_isDragging && event->button() == Qt::RightButton) {
        getCamera()->mouseUp(event->x(), event->y());
        m_isDragging = false;
        update();
    }
}

void SupportCanvas3D::wheelEvent(QWheelEvent *event) {
    getCamera()->mouseScrolled(event->delta());
    update();
}

void SupportCanvas3D::resizeEvent(QResizeEvent *event) {
    emit aspectRatioChanged();
    if (m_sceneviewScene.get())
        m_sceneviewScene->setWindowDim(this->width(), this->height(), m_ratio);
}
