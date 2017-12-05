/**
 * @file Canvas2D.cpp
 *
 * CS123 2-dimensional canvas. Contains support code necessary for Brush, Filter, Intersect, and
 * Ray.
 *
 * YOU WILL NEED TO FILL THIS IN!
 *
 */

// For your convenience, a few headers are included for you.
#include <assert.h>
#include <iostream>
#include <math.h>
#include <memory>
#include <unistd.h>
#include "Canvas2D.h"
#include "Settings.h"
#include "RayScene.h"


#include <QPainter>
#include "brush/Brush.h"
#include "brush/ConstantBrush.h"
#include "brush/LinearBrush.h"
#include "brush/QuadraticBrush.h"
#include "brush/SmudgeBrush.h"
#include "filter/filter.h"
#include "filter/invertfilter.h"
#include "filter/grayscalefilter.h"
#include "filter/edgedetectfilter.h"
#include "filter/blurfilter.h"
#include "filter/scalefilter.h"
#include "filter/sharpenfilter.h"
#include "filter/embossfilter.h"

#include "ray/raytracer.h"

Canvas2D::Canvas2D() :
    // @TODO: Initialize any pointers in this class here.
    m_rayScene(nullptr),
    m_brush(nullptr)
{
}

Canvas2D::~Canvas2D()
{
}

// This is called when the canvas size is changed. You can change the canvas size by calling
// resize(...). You probably won't need to fill this in, but you can if you want to.
void Canvas2D::notifySizeChanged(int w, int h) {
}

void Canvas2D::paintEvent(QPaintEvent *e) {
    // You probably won't need to fill this in, but you can if you want to override any painting
    // events for the 2D canvas. For now, we simply call the superclass.
    SupportCanvas2D::paintEvent(e);

}

// ********************************************************************************************
// ** BRUSH
// ********************************************************************************************


void Canvas2D::mouseDown(int x, int y) {
    // @TODO: [BRUSH] Mouse interaction for brush. You will probably want to create a separate
    //        class for each of your brushes. Remember that you can use the static Settings
    //        object to get the currently selected brush and its parameters.

    // You're going to need to leave the alpha value on the canvas itself at 255, but you will
    // need to use the actual alpha value to compute the new color of the pixel

//    bool fixAlphaBlending = settings.fixAlphaBlending; // for extra/half credit
    switch (settings.brushType) {
        case BRUSH_CONSTANT:
            m_brush = std::make_unique<ConstantBrush>(settings.brushColor, settings.brushRadius);
            break;
        case BRUSH_LINEAR:
            m_brush = std::make_unique<LinearBrush>(settings.brushColor, settings.brushRadius);
            break;
        case BRUSH_QUADRATIC:
            m_brush = std::make_unique<QuadraticBrush>(settings.brushColor, settings.brushRadius);
            break;
        case BRUSH_SMUDGE:
            m_brush = std::make_unique<SmudgeBrush>(settings.brushColor, settings.brushRadius);
            m_brush->brushDown(x, y, this);
            break;
    }
}

void Canvas2D::mouseDragged(int x, int y) {
    // TODO: [BRUSH] Mouse interaction for Brush.
    m_brush->brushDragged(x, y, this);
}

void Canvas2D::mouseUp(int x, int y) {
    // TODO: [BRUSH] Mouse interaction for Brush.
    update();
}



// ********************************************************************************************
// ** FILTER
// ********************************************************************************************

void Canvas2D::filterImage() {
    // TODO: [FILTER] Filter the image. Some example code to get the filter type is provided below.
    //get marquee selection
    int x1 = marqueeStart().x();
    int y1 = marqueeStart().y();
    int x2 = marqueeStop().x();
    int y2 = marqueeStop().y();

    //no selection
    if (marqueeStart() == marqueeStop()) {
        x1 = y1 = 0;
        x2 = this->width() - 1;
        y2 = this->height() - 1;
    } else { // otherwise validate selection
        //check top left bound
        x1 = std::max(x1, 0);
        y1 = std::max(y1, 0);
        x2 = std::max(x2, 0);
        y2 = std::max(y2, 0);

        //check bottom right bound
        x1 = std::min(x1, this->width() - 1);
        x2 = std::min(x2, this->width() - 1);
        y1 = std::min(y1, this->height() - 1);
        y2 = std::min(y2, this->height() - 1);

        //check if selection is in reversed orde, i.e.
        //make sure that x1, y1 is the upper right, and x2, y2 is the bottom right
        int n1 = std::min(x1, x2);
        int m1 = std::min(y1, y2);

        int n2 = std::max(x1, x2);
        int m2 = std::max(y1, y2);

        x1 = n1;
        y1 = m1;
        x2 = n2;
        y2 = m2;
    }

    //init different filter types based on selection
    std::unique_ptr<Filter> filter;
    switch(settings.filterType) {
        case FILTER_INVERT:
            filter = std::make_unique<InvertFilter>();
            break;

        case FILTER_GRAYSCALE:
            filter = std::make_unique<GrayscaleFilter>();
            break;

        case FILTER_EDGE_DETECT:
            filter = std::make_unique<EdgeDetectFilter>(settings.edgeDetectSensitivity);
            break;

        case FILTER_BLUR:
            filter = std::make_unique<BlurFilter>(settings.blurRadius);           
            break;

        case FILTER_SCALE:
            filter = std::make_unique<ScaleFilter>(settings.scaleX, settings.scaleY);
            break;

        case FILTER_SPECIAL_1:
            filter = std::make_unique<SharpenFilter>();
            break;

        case FILTER_SPECIAL_2:
            filter = std::make_unique<EmbossFilter>();
            break;
    }

    filter->applyFilter(this, x1, y1, x2, y2);

}


void Canvas2D::setScene(RayScene *scene) {
    m_rayScene.release();
    m_rayScene.reset(scene);
}

void Canvas2D::renderImage(Camera *camera, int width, int height) {
    if (m_rayScene) {
        // @TODO: raytrace the scene based on settings
        //        YOU MUST FILL THIS IN FOR INTERSECT/RAY

        // If you want the interface to stay responsive, make sure to call
        // QCoreApplication::processEvents() periodically during the rendering.
        resize(width, height);
        RayTracer tracer(m_rayScene->m_rayShapes,
                         m_rayScene->m_rayLights,
                         m_rayScene->m_fileNameToTexture,
                         camera,
                         this->data(),
                         width, height);
        tracer.render();
        update();
    }
}

void Canvas2D::cancelRender() {
    // TODO: cancel the raytracer (optional)
}



void Canvas2D::settingsChanged() {
    // TODO: Process changes to the application settings.
}
