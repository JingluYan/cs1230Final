#ifndef RENDERTASK_H
#define RENDERTASK_H

#include <QRunnable>
#include "raytracer.h"
class RenderTask : public QRunnable
{
public:
    RenderTask(RayTracer* tracer, int x1, int y1, int x2, int y2);

    RayTracer* m_tracer;
    int m_x1;
    int m_y1;
    int m_x2;
    int m_y2;

    void run();
};

#endif // RENDERTASK_H
