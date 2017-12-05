#ifndef EDGEDETECTFILTER_H
#define EDGEDETECTFILTER_H
#include "filter.h"

class EdgeDetectFilter : public Filter
{
public:
    EdgeDetectFilter();
    EdgeDetectFilter(float param);
    void applyFilter(Canvas2D* canvas, int x1, int y1, int x2, int y2) override;

private:
    float sensitivity;
};

#endif // EDGEDETECTFILTER_H
