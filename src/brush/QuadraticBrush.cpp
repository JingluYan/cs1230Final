/**
 * @file   QuadraticBrush.cpp
 *
 * Implementation of a brush with a quadratic mask distribution.
 *
 * You should fill this file in while completing the Brush assignment.
 */

#include "QuadraticBrush.h"

#include <math.h>

QuadraticBrush::QuadraticBrush(BGRA color, int radius)
    : Brush(color, radius)
{
    // @TODO: [BRUSH] You'll probably want to set up the mask right away.
    makeMask();
}

QuadraticBrush::~QuadraticBrush()
{
}

void QuadraticBrush::makeMask() {
    // @TODO: [BRUSH] Set up the mask for your Quadratic brush here...
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


