/**
 * @file   ConstantBrush.cpp
 *
 * Implementation of a brush with a constant mask distribution.
 *
 * You should fill this file in while completing the Brush assignment.
 */

#include "ConstantBrush.h"
#include <cmath>

using namespace std;

ConstantBrush::ConstantBrush(BGRA color, int radius)
    : Brush(color, radius)
{
    // @TODO: [BRUSH] You'll probably want to set up the mask right away.
    makeMask();
}


ConstantBrush::~ConstantBrush()
{
}

void ConstantBrush::makeMask() {
    // @TODO: [BRUSH] Set up the mask for your Constant brush here...
    int rowcounter;
    int colcounter;
    // the dimension of the mask, mask is a square
    int maskDimen = 2 * m_radius + 1;
    int rowCenter = maskDimen / 2; // the row of the mask center
    int colCenter = maskDimen / 2; // the col of the mask center
    for (rowcounter = 0; rowcounter < maskDimen; rowcounter++) {
        for (colcounter = 0; colcounter < maskDimen; colcounter++) {
            int index = rowcounter * maskDimen + colcounter;
            int dis = sqrt(pow(rowCenter - rowcounter, 2) + pow(colCenter - colcounter, 2)); // the distance from the pixel to the mask center
            m_mask[index] = m_radius - dis >= 0 ? 1 : 0;
        }
    }
}


