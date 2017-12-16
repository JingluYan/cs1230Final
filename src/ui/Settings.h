/**
 * @file    Settings.h
 *
 * This file contains various settings and enumerations that you will need to use in the various
 * assignments. The settings are bound to the GUI via static data bindings.
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include "BGRA.h"

// Enumeration values for the Shapes that the user can select in the GUI.
enum ShapeType {
    SHAPE_CUBE,
    SHAPE_CONE,
    SHAPE_SPHERE,
    SHAPE_CYLINDER,
    SHAPE_TORUS,
    SHAPE_SPECIAL_1,
    SHAPE_SPECIAL_2,
    NUM_SHAPE_TYPES
};

// Enumeration values for the two tabs (2D, 3D) at the bottom of the Window.
enum UITab {
    TAB_2D,
    TAB_3D,
    NUM_TABS
};

// Enumeration values for the currently selected scene type
enum SceneMode {
    SCENEMODE_SHAPES,
    SCENEMODE_SCENEVIEW
};

// Enumeration values for the currently selected camera type
enum CameraMode {
    CAMERAMODE_ORBIT,
    CAMERAMODE_CAMTRANS
};

/**
 * @struct Settings
 *
 * Stores application settings for the CS123 GUI.
 *
 * You can access all app settings through the "settings" global variable.
 * The settings will be automatically updated when things are changed in the
 * GUI (the reverse is not true however: changing the value of a setting does
 * not update the GUI).
*/
struct Settings {
    // Loads settings from disk, or fills in default values if no saved settings exist.
    void loadSettingsOrDefaults();

    // Saves the current settings to disk.
    void saveSettings();

    // Shapes
    bool useSceneviewScene;
    int shapeType;              // Selected shape type
    int shapeParameter1;
    int shapeParameter2;
    float shapeParameter3;
    bool useLighting;           // Enable default lighting
    bool drawWireframe;         // Draw wireframe only
    bool drawNormals;           // Turn normals on and off

    // Camtrans
    bool useOrbitCamera;        // Use the built-in orbiting camera instead of the Camtrans camera
    float cameraPosX;
    float cameraPosY;
    float cameraPosZ;
    float cameraRotU;
    float cameraRotV;
    float cameraRotN;
    float cameraFov;            // The camera's field of view, which is twice the height angle.
    float cameraNear;           // The distance from the camera to the near clipping plane.
    float cameraFar;            // The distance from the camera to the far clipping plane.

    // Modeler
    int objTool;                // The currently selected modeler tool.

    // Features
    bool useFeatureLighting;    // Enable default lighting
    bool textureMapping;        // Turn on texture mapping
    bool bumpMapping;           // Turn on bump mapping
    bool deferredLight;         // Turn on deferred lighting
    float ambient;              // Param for deferred light
    bool SSAO;                  // Turn on SSAO
    float radius;               // Param for SSAO
    float bias;                 // Param for SSAO
    bool visualizeSSAO;         // Visualize SSAO
    bool blinn;

    // Ray
    bool useSuperSampling;      // Enable or disable super-sampling.
    int numSuperSamples;        // Controls the number of samples per pixel.
    bool useAntiAliasing;       // Enable or disable anti-aliasing.
    bool useShadows;            // Enable or disable shadows.
    bool useTextureMapping;     // Enable or disable texture mapping.
    bool useReflection;         // Enable or disable reflection.
    bool useRefraction;         // Enable or disable refraction (this is extra credit).
    bool useMultiThreading;     // Enable or disable multi-threading (extra credit).
    bool usePointLights;        // Enable or disable point lighting.
    bool useDirectionalLights;  // Enable or disable directional lighting (extra credit).
    bool useSpotLights;         // Enable or disable spot lights (extra credit).

    int getSceneMode();
    int getCameraMode();

    int currentTab;

};

// The global Settings object, will be initialized by MainWindow
extern Settings settings;

#endif // SETTINGS_H
