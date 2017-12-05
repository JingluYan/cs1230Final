#ifndef SHARPENFILTER_H
#define SHARPENFILTER_H
#include "filter.h"

class SharpenFilter : public Filter
{
public:
    SharpenFilter();
    void applyFilter(Canvas2D *canvas, int x1, int y1, int x2, int y2) override;
};

#endif // SHARPENFILTER_H
