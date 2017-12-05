/**
 * @file   Brush.cpp
 *
 * Implementation of a brush that smudges the image on the canvas as the mouse is dragged.
 *
 * You should fill this file in for the Brush assignment.
 */

#include "SmudgeBrush.h"

#include "Canvas2D.h"
#include <cmath>


SmudgeBrush::SmudgeBrush(BGRA color, int radius) :
    QuadraticBrush(color, radius)
{
    // @TODO: [BRUSH] Initialize any memory you are going to use here. Hint - you are going to
    //       need to store temporary image data in memory. Remember to use automatically managed memory!
    m_tmpBuffer.reserve(m_mask.size());
    makeMask();
}


SmudgeBrush::~SmudgeBrush()
{
    // @TODO: [BRUSH] Be sure not to leak memory!  If you're using automatic memory management everywhere,
    //       this will be empty.
}

void SmudgeBrush::brushUp(int x, int y, Canvas2D* canvas) {
}


//! create a mask with a distribution of your choice (probably want to use quadratic for best results)
void SmudgeBrush::makeMask() {
    // @TODO: [BRUSH] Set up the mask for your brush here. For this brush you will probably want
    //        to use a quadratic distribution for the best results. Linear or Gaussian would
    //        work too, however. Feel free to paste your code from the Linear or Quadratic brushes
    //        or modify the class inheritance to be able to take advantage of one of those class's
    //        existing implementations. The choice is yours!
    //

    int rowcounter;
    int colcounter;
    // the dimension of the mask, mask is a square
    int maskDimen = 2 * m_radius + 1;
    int rowCenter = maskDimen / 2; // the row of the mask center
    int colCenter = maskDimen / 2; // the col of the mask center
    for (rowcounter = 0; rowcounter < maskDimen; rowcounter++) {
        for (colcounter = 0; colcounter < maskDimen; colcounter++) {
            int index = rowcounter * maskDimen + colcounter;
            float dis = sqrt(pow(rowCenter - rowcounter, 2) + pow(colCenter - colcounter, 2)); // the distance from the pixel to the mask center
            m_mask[index] = (dis / m_radius) >= 1 ? 0 : pow(1 - dis / m_radius, 2);
        }
    }
}

void SmudgeBrush::brushDown(int x, int y, Canvas2D *canvas) {
    pickUpPaint(x, y, canvas);
}

//! Picks up paint from the canvas before drawing begins.
void SmudgeBrush::pickUpPaint(int x, int y, Canvas2D* canvas) {
    int width = canvas->width();
    int height = canvas->height();

    // @TODO: [BRUSH] Perform the "pick up paint" step described in the assignment handout here.
    //        In other words, you should store the "paint" under the brush mask in a temporary
    //        buffer (which you'll also have to figure out where and how to allocate). Then,
    //        in the paintOnce() method, you'll paste down the paint that you picked up here.
    //
    BGRA *pix = canvas->data();
    int colStart = std::max(x - m_radius, 0);
    int rowStart = std::max(y - m_radius, 0);
    int rowEnd = std::min(height, y + m_radius + 1);
    int colEnd = std::min(width, x + m_radius + 1);
    int maskDim = 2 * m_radius + 1; //mask dimension
    for (int rowcounter = rowStart; rowcounter < rowEnd; rowcounter++) {
        for (int colcounter = colStart; colcounter < colEnd; colcounter++) {
            int index = rowcounter * width + colcounter; // index of the pix vector
            int hDis = x - colcounter;
            int vDis = y - rowcounter;
            int dis = std::sqrt(std::pow(hDis, 2) + std::pow(vDis, 2));
            if (dis <= m_radius) {
                int maskX = colcounter - (x - m_radius);
                int maskY = rowcounter - (y - m_radius);
                int maskIndx = maskDim * maskY + maskX;
                m_tmpBuffer[maskIndx] = pix[index] /** m_mask[maskIndx]*/;
            }
        }
    }
}

void SmudgeBrush::brushDragged(int mouseX, int mouseY, Canvas2D* canvas) {
    // @TODO: [BRUSH] Here, you'll need to paste down the paint you picked up in
    //        the previous method. Be sure to take the mask into account! You can
    //        ignore the alpha parameter, but you can also use it (smartly) if you
    //        would like to.
    BGRA *pix = canvas->data();
    int colStart = std::max(mouseX - m_radius, 0);
    int rowStart = std::max(mouseY - m_radius, 0);
    int rowEnd = std::min(canvas->height(), mouseY + m_radius + 1);
    int colEnd = std::min(canvas->width(), mouseX + m_radius + 1);
    int maskDim = 2 * m_radius + 1;
    for (int rowcounter = rowStart; rowcounter < rowEnd; rowcounter++) {
        for (int colcounter = colStart; colcounter < colEnd; colcounter++) {
            int index = rowcounter * canvas->width() + colcounter; // index of the pix vector
            int hDis = mouseX - colcounter;
            int vDis = mouseY - rowcounter;
            int dis = std::sqrt(std::pow(hDis, 2) + std::pow(vDis, 2));
            if (dis <= m_radius) {
                int maskX = colcounter - (mouseX - m_radius);
                int maskY = rowcounter - (mouseY - m_radius);
                int maskIndx = maskDim * maskY + maskX;
                pix[index] = pix[index] * (1 - m_mask[maskIndx]) + m_tmpBuffer[maskIndx] * m_mask[maskIndx];
            }
        }
    }
    canvas->update();
    // now pick up paint again...
    pickUpPaint(mouseX, mouseY, canvas);

}


