#ifndef GRAYSCALEFILTER_H
#define GRAYSCALEFILTER_H
#include "filter.h"

class GrayscaleFilter : public Filter
{
public:
    GrayscaleFilter();
    void applyFilter(Canvas2D* canvas, int x1, int y1, int x2, int y2) override;
};

#endif // GRAYSCALEFILTER_H
