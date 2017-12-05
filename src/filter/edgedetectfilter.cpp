#include "edgedetectfilter.h"
#include "Canvas2D.h"
#include <math.h>

EdgeDetectFilter::EdgeDetectFilter()
{
}

EdgeDetectFilter::EdgeDetectFilter(float param) :
    sensitivity(param)
{

}


void EdgeDetectFilter::applyFilter(Canvas2D *canvas, int x1, int y1, int x2, int y2) {
    BGRA *pix = canvas->data();
    int h = canvas->height();
    int w = canvas->width();
    int selectionWidth = x2 - x1 + 1;

    BGRA *buffer = new BGRA[w * h];

    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            int index = x + y * w;
           // [lu,  u   , ru]
           // [l , index, r ]
           // [ld,  d   , rd]
           int lu = (x - 1 >= x1 && y - 1 >= y1) ? (index - w - 1) : index;
           int l = (x - 1 >= x1) ? (index - 1) : index;
           int ld = (x - 1 >= x1 && y + 1 <= y2) ? (index + w - 1) : index;
           int ru = (x + 1 <= x2 && y - 1 >= y1) ? (index - w + 1) : index;
           int r = (x + 1 <= x2) ? (index + 1) : index;
           int rd = (x + 1 <= x2 && y + 1 <= y2) ? (index + w + 1) : index;
           int u = (y - 1 >= y1) ? (index - w) : index;
           int d = (y + 1 <= y2) ? (index + w) : index;
           // horizontal gradient
           float Gx = -pix[lu].grayscaleIntensity() - 2.f * (pix[l].grayscaleIntensity()) - pix[ld].grayscaleIntensity()
                       + pix[ru].grayscaleIntensity() + 2.f * pix[r].grayscaleIntensity() + pix[rd].grayscaleIntensity();
           Gx /= 255; // normalize
           // vertical gradient
           float Gy = -pix[lu].grayscaleIntensity() - 2.f *(pix[u].grayscaleIntensity()) - pix[ru].grayscaleIntensity()
                   + pix[ld].grayscaleIntensity() + 2.f * pix[d].grayscaleIntensity() + pix[rd].grayscaleIntensity();
           Gy /= 255;
           //multiply by filter sensitivity before capping off G
           float G = std::sqrt(Gx * Gx + Gy * Gy) * sensitivity;
           G = G > 1 ? 1 : G;
           G = G < 0 ? 0 : G;
           int intensity = static_cast<int>(G * 255);
           buffer[index].r = buffer[index].g = buffer[index].b = intensity;
        }
    }

    //copy pixel row by row
    for (int row = y1; row <= y2; row++) {
        int offset = x1 + row * w;
        memcpy(pix + offset, buffer + offset, selectionWidth * sizeof(BGRA));
    }

    delete[] buffer;
    canvas->update();
}

