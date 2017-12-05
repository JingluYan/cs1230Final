#ifndef BLURFILTER_H
#define BLURFILTER_H
#include "filter.h"
class BlurFilter : public Filter
{
public:
    BlurFilter();

    BlurFilter(int radius);

    void applyFilter(Canvas2D* canvas, int x1, int y1, int x2, int y2) override;

private:
    int r; // radius
};

#endif // BLURFILTER_H
