#include "sharpenfilter.h"
#include "Canvas2D.h"

SharpenFilter::SharpenFilter()
{
}

void SharpenFilter::applyFilter(Canvas2D *canvas, int x1, int y1, int x2, int y2) {
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
           int l = (x - 1 >= x1) ? (index - 1) : index;
           int r = (x + 1 <= x2) ? (index + 1) : index;
           int u = (y - 1 >= y1) ? (index - w) : index;
           int d = (y + 1 <= y2) ? (index + w) : index;
           // horizontal gradient
           int red = pix[index].r * 5 - pix[u].r - pix[d].r - pix[l].r - pix[r].r;
           int green = pix[index].g * 5 - pix[u].g - pix[d].g - pix[l].g - pix[r].g;
           int blue = pix[index].b * 5 - pix[u].b - pix[d].b - pix[l].b - pix[r].b;

           red = std::max(0, red);
           red = std::min(255, red);
           green = std::max(0, green);
           green = std::min(255, green);
           blue = std::max(0, blue);
           blue = std::min(255, blue);

           buffer[index] = BGRA(static_cast<unsigned char>(red), static_cast<unsigned char>(green),
                                static_cast<unsigned char>(blue), 255);
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
