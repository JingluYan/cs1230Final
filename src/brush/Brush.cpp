/**
 * @file   Brush.cpp
 *
 * Implementation of common functionality of bitmap brushes.
 *
 * You should fill this file in while scompleting the Brush assignment.
 */

#include "Brush.h"
#include "Canvas2D.h"
#include "Settings.h"
#include <cmath>


static unsigned char lerp(unsigned char a, unsigned char b, float percent) {
    float fa = static_cast<float>(a) / 255.0f;
    float fb = static_cast<float>(b) / 255.0f;
    return static_cast<unsigned char>((fa + (fb - fa) * percent) * 255.0f + 0.5f);
}



Brush::Brush(BGRA color, int radius) :
    // Pro-tip: Initialize all variables in the initialization list
    m_color(color),
    m_radius(radius),
    m_mask(pow((2 * radius + 1), 2))
{
    // Pro-tip: By the time you get to the constructor body, all of the
    // member variables have already been initialized.
}


Brush::~Brush()
{
    // Pro-tip: The destructor (here) is where you free all the resources
    // you allocated during the lifetime of the class
    // Pro-tip: If you use std::unique_ptr or std::vector, you probabably
    // won't need to put anything in here.
}

int Brush::getAlpha() const {
    return m_color.a;
}

BGRA Brush::getBGRA() const {
    return m_color;
}

int Brush::getBlue() const {
    return m_color.b;
}

int Brush::getGreen() const {
    return m_color.g;
}

int Brush::getRadius() const {
    return m_radius;
}

int Brush::getRed() const {
    return m_color.r;
}

void Brush::setAlpha(int alpha) {
    m_color.a = alpha;
}

void Brush::setBGRA(const BGRA &bgra) {
    m_color = bgra;
}

void Brush::setBlue(int blue) {
    m_color.b = blue;
}

void Brush::setGreen(int green) {
    m_color.g = green;
}

void Brush::setRed(int red) {
    m_color.r = red;
}

void Brush::setRadius(int radius) {
    m_radius = radius;
    makeMask();
}




void Brush::brushDragged(int mouseX, int mouseY, Canvas2D* canvas) {
    // @TODO: [BRUSH] You can do any painting on the canvas here. Or, you can
    //        override this method in a subclass and do the painting there.
    //
    // Example: You'll want to delete or comment out this code, which
    // sets all the pixels on the canvas to red.
    //cmath

    BGRA *pix = canvas->data();
//    int size = canvas->width() * canvas->height();
//    for (int i = 0; i < size; i++) {cmath
//        pix[i] = BGRA(255, 0, 0, 255);
//    }
    m_color = settings.brushColor;
    int colStart = std::max(mouseX - m_radius, 0);
    int rowStart = std::max(mouseY - m_radius, 0);
    int rowEnd = std::min(canvas->height(), mouseY + m_radius + 1);
    int colEnd = std::min(canvas->width(), mouseX + m_radius + 1);
    int maskDim = 2 * m_radius + 1;
    for (int rowcounter = rowStart; rowcounter < rowEnd; rowcounter++) {
        for (int colcounter = colStart; colcounter < colEnd; colcounter++) {
            int index = rowcounter * canvas->width() + colcounter;
            int hDis = mouseX - colcounter;
            int vDis = mouseY - rowcounter;
            int dis = sqrt(pow(hDis, 2) + pow(vDis, 2));
            if (dis <= m_radius) {
                int maskX = colcounter - (mouseX - m_radius);
                int maskY = rowcounter - (mouseY - m_radius);
                int maskIndx = maskDim * maskY + maskX;
                float alpha = (float)getAlpha() / 255.0;
                pix[index] = pix[index] * (1 - alpha* m_mask[maskIndx]) + getBGRA() * alpha * m_mask[maskIndx];
            }
        }
    }


    canvas->update();

}
