#include "invertfilter.h"
#include "Canvas2D.h"

InvertFilter::InvertFilter()
{

}

void InvertFilter::applyFilter(Canvas2D *canvas, int x1, int y1, int x2, int y2) {
    BGRA *pix = canvas->data();
    int w = canvas->width();

    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            int index = x + y * w;
            pix[index].invert();
        }
    }
    canvas->update();
}
