#include "embossfilter.h"
#include "Canvas2D.h"

EmbossFilter::EmbossFilter()
{
}

void EmbossFilter::applyFilter(Canvas2D *canvas, int x1, int y1, int x2, int y2) {
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
           int r = (x + 1 <= x2) ? (index + 1) : index;
           int rd = (x + 1 <= x2 && y + 1 <= y2) ? (index + w + 1) : index;
           int u = (y - 1 >= y1) ? (index - w) : index;
           int d = (y + 1 <= y2) ? (index + w) : index;
           // horizontal gradient
           int red = pix[index].r - pix[u].r + pix[d].r - pix[l].r + pix[r].r - 2 * pix[lu].r + 2 * pix[rd].r;
           int green = pix[index].g - pix[u].g + pix[d].g - pix[l].g + pix[r].g - 2 * pix[lu].g + 2 * pix[rd].g;
           int blue = pix[index].b- pix[u].b + pix[d].b - pix[l].b + pix[r].b - 2 * pix[lu].b + 2 * pix[rd].b;

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
