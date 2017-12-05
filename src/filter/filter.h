#ifndef FILTER_H
#define FILTER_H

class Canvas2D;

class Filter
{
public:
    Filter();
    void virtual applyFilter(Canvas2D* canvas, int x1, int y1, int x2, int y2);
};

#endif // FILTER_H
