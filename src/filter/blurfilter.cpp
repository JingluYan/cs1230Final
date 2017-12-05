#include "blurfilter.h"
#include "Canvas2D.h"

BlurFilter::BlurFilter()
{
    BlurFilter(1);
}

BlurFilter::BlurFilter(int radius) :
    r(radius)
{

}

void BlurFilter::applyFilter(Canvas2D* canvas, int x1, int y1, int x2, int y2) {
    BGRA* pix = canvas->data();
    int w = canvas->width();
    int h = canvas->height();
    int selectionWidth = x2 - x1 + 1;
    int selectionHeight = y2 - y1 + 1;
    int kernel[2 * r + 1];
    for (int i = 0; i <= 2*r; i++) {
        if (i <= r) {
            kernel[i] = i + 1;
        } else {
            kernel[i] = 2 * r - i + 1;
        }
    }

    //vertical convolution pass of triangle filter
    for (int x = x1; x <= x2; x++) { // for each col of pixels in selection
        int Rv[selectionHeight] = {0}; // if not init to 0, will get garbage random value as default
        int Gv[selectionHeight] = {0};
        int Bv[selectionHeight] = {0};
        for (int y = y1; y <= y2; y++) { // for each pixel in the col
            int top = y - r >= 0 ? y - r : 0; // row index of top row
            int bot = y + r < h ? y + r : h - 1; // row index of bot row
            float weightSum = 0.f;
            for (int i = top; i <= bot; i++) {
                int weight = kernel[i - top];
                weightSum += static_cast<float>(weight);
                Rv[y - y1] += weight * pix[i * w + x].r;
                Gv[y - y1] += weight * pix[i * w + x].g;
                Bv[y - y1] += weight * pix[i * w + x].b;
            }

            Rv[y - y1] = static_cast<int>( Rv[y - y1] / weightSum);
            Gv[y - y1] = static_cast<int>( Gv[y - y1] / weightSum);
            Bv[y - y1] = static_cast<int>( Bv[y - y1] / weightSum);
        }
        //copy the vertical blur back to pix buffer
        for (int i = 0; i < selectionHeight; i++) {
            int index = (y1 + i) * w + x;
            pix[index].r = Rv[i];
            pix[index].g = Gv[i];
            pix[index].b = Bv[i];
        }
    }


    //horizontal convolution pass of triangle filter
    for (int y = y1; y <=y2; y++) {
        int Rh[selectionWidth] = {0};
        int Gh[selectionWidth] = {0};
        int Bh[selectionWidth] = {0};
        for (int x = x1; x <= x2; x++) { // for each pixel in the col
            int left = x - r >= 0 ? x - r : 0;
            int right = x + r < w ? x + r : w -1;
            float weightSum = 0.f;
            for (int i = left; i <= right; i++) {
                int weight = kernel[i - left];
                weightSum += static_cast<float>(weight);
                Rh[x - x1] += weight * pix[y * w + i].r;
                Gh[x - x1] += weight * pix[y * w + i].g;
                Bh[x - x1] += weight * pix[y * w + i].b;
            }
            Rh[x - x1] = static_cast<int>( Rh[x - x1] / weightSum);
            Gh[x - x1] = static_cast<int>( Gh[x - x1] / weightSum);
            Bh[x - x1] = static_cast<int>( Bh[x - x1] / weightSum);
        }
        //copy the vertical blur back to pix buffer
        for (int i = 0; i < selectionWidth; i++) {
            int index = y * w + x1 + i;
            pix[index].r = Rh[i];
            pix[index].g = Gh[i];
            pix[index].b = Bh[i];
        }
    }


    canvas->update();
}

