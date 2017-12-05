#ifndef EMBOSSFILTER_H
#define EMBOSSFILTER_H

#include "filter.h"

class EmbossFilter : public Filter
{
public:
    EmbossFilter();
    void applyFilter(Canvas2D *canvas, int x1, int y1, int x2, int y2);
};

#endif // EMBOSSFILTER_H
