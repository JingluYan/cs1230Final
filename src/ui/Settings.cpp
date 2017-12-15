/*!

 Settings.h
 CS123 Support Code

 @author  Evan Wallace (edwallac)
 @date    9/1/2010

 This file contains various settings and enumerations that you will need to
 use in the various assignments. The settings are bound to the GUI via static
 data bindings.

**/

#include "Settings.h"
#include <QFile>
#include <QSettings>

Settings settings;


/**
 * Loads the application settings, or, if no saved settings are available, loads default values for
 * the settings. You can change the defaults here.
 */
void Settings::loadSettingsOrDefaults() {
    // Set the default values below
    QSettings s("CS123", "CS123");

    // Shapes
    shapeType = s.value("shapeType", SHAPE_SPHERE).toInt();
    shapeParameter1 = s.value("shapeParameter1", 15).toInt();
    shapeParameter2 = s.value("shapeParameter2", 15).toInt();
    shapeParameter3 = s.value("shapeParameter3", 15).toDouble();
    useLighting = s.value("useLighting", true).toBool();
    drawWireframe = s.value("drawWireframe", true).toBool();
    drawNormals = s.value("drawNormals", false).toBool();

    // Camtrans
    useOrbitCamera = s.value("useOrbitCamera", true).toBool();
    cameraFov = s.value("cameraFov", 55).toDouble();
    cameraNear = s.value("cameraNear", 0.1).toDouble();
    cameraFar = s.value("cameraFar", 50).toDouble();

    // Features
    sceneType = s.value("sceneType", SCENE_1).toInt();
    useFeatureLighting = s.value("useFeatureLighting", useFeatureLighting).toBool();
    deferredLight = s.value("deferredLight", false).toBool();
    textureMapping = s.value("textureMapping", true).toBool();
    bumpMapping = s.value("bumpMapping", false).toBool();
    ambient = s.value("ambient", ambient).toFloat();
    SSAO = s.value("SSAO", SSAO).toFloat();
    radius = s.value("radius", radius).toFloat();
    bias = s.value("bias", bias).toFloat();
    visualizeSSAO = s.value("visualizeSSAO", visualizeSSAO).toBool();
    blin = s.value("blin",blin).toBool();

    // Ray
    useSuperSampling = s.value("useSuperSampling", false).toBool();
    numSuperSamples = s.value("numSuperSamples", 2).toInt();
    useAntiAliasing = s.value("useAntiAliasing", true).toBool();
    useShadows = s.value("useShadows", false).toBool();
    useTextureMapping = s.value("useTextureMapping", false).toBool();
    useReflection = s.value("useReflection", false).toBool();
    useRefraction = s.value("useRefraction", false).toBool();
    useMultiThreading = s.value("useMultiThreading", true).toBool();
    usePointLights = s.value("usePointLights", true).toBool();
    useDirectionalLights = s.value("useDirectionalLights", true).toBool();
    useSpotLights = s.value("useSpotLights", true).toBool();

    currentTab = s.value("currentTab", TAB_2D).toBool();

    // These are for computing deltas and the values don't matter, so start all dials in the up
    // position
    cameraPosX = 0;
    cameraPosY = 0;
    cameraPosZ = 0;
    cameraRotU = 0;
    cameraRotV = 0;
    cameraRotN = 0;
}

void Settings::saveSettings() {
    QSettings s("CS123", "CS123");

    // Shapes
    s.setValue("shapeType", shapeType);
    s.setValue("shapeParameter1", shapeParameter1);
    s.setValue("shapeParameter2", shapeParameter2);
    s.setValue("shapeParameter3", shapeParameter3);
    s.setValue("useLighting", useLighting);
    s.setValue("drawWireframe", drawWireframe);
    s.setValue("drawNormals", drawNormals);

    // Camtrans
    s.setValue("useOrbitCamera", useOrbitCamera);
    s.setValue("cameraFov", cameraFov);
    s.setValue("cameraNear", cameraNear);
    s.setValue("cameraFar", cameraFar);

    // Features
    s.setValue("sceneType", sceneType);
    s.setValue("useFeatureLighting", useFeatureLighting);
    s.setValue("deferredLight", deferredLight);
    s.setValue("textureMapping", textureMapping);
    s.setValue("bumpMapping", bumpMapping);
    s.setValue("ambient", ambient);
    s.setValue("SSAO", SSAO);
    s.setValue("radius", radius);
    s.setValue("bias", bias);
    s.setValue("visualizeSSAO", visualizeSSAO);
    s.setValue("blin", blin);

    // Ray
    s.setValue("useSuperSampling", useSuperSampling);
    s.setValue("numSuperSamples", numSuperSamples);
    s.setValue("useAntiAliasing", useAntiAliasing);
    s.setValue("useShadows", useShadows);
    s.setValue("useTextureMapping", useTextureMapping);
    s.setValue("useReflection", useReflection);
    s.setValue("useRefraction", useRefraction);
    s.setValue("useMultiThreading", useMultiThreading);
    s.setValue("usePointLights", usePointLights);
    s.setValue("useDirectionalLights", useDirectionalLights);
    s.setValue("useSpotLights", useSpotLights);

    s.setValue("currentTab", currentTab);
}

int Settings::getSceneMode() {
    if (this->useSceneviewScene)
        return SCENEMODE_SCENEVIEW;
    else
        return SCENEMODE_SHAPES;
}

int Settings::getCameraMode() {
    if (this->useOrbitCamera)
        return CAMERAMODE_ORBIT;
    else
        return CAMERAMODE_CAMTRANS;
}
