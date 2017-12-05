#ifndef SCALEFILTER_H
#define SCALEFILTER_H
#include "filter/filter.h"

class ScaleFilter : public Filter
{
public:
    ScaleFilter();
    ScaleFilter(float x, float y);

    void applyFilter(Canvas2D *canvas, int x1, int y1, int x2, int y2) override;
    float scaleX;
    float scaleY;

private:
    float lerp(float t, float a, float b);
};

#endif // SCALEFILTER_H
