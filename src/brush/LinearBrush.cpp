/**
 * @file   LinearBrush.cpp
 *
 * Implementation of a brush with a linear mask distribution.
 *
 * You should fill this file in while completing the Brush assignment.
 */

#include "LinearBrush.h"

#include <math.h>
using namespace std;

LinearBrush::LinearBrush(BGRA color, int radius)
    : Brush(color, radius)
{
    // @TODO: [BRUSH] You'll probably want to set up the mask right away.
    makeMask();
}


LinearBrush::~LinearBrush()
{
}

void LinearBrush::makeMask() {
    // @TODO: [BRUSH] Set up the mask for your Linear brush here...
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
            m_mask[index] = (dis / m_radius) >= 1 ? 0 : (1 - dis / m_radius);
        }
    }
}


