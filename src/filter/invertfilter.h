#ifndef INVERTFILTER_H
#define INVERTFILTER_H

#include "filter.h"
#include "BGRA.h"

class Canvas2D;

class InvertFilter : public Filter
{
public:
    InvertFilter();

    void applyFilter(Canvas2D* canvas, int x1, int y1, int x2, int y2) override;
};

#endif // INVERTFILTER_H
