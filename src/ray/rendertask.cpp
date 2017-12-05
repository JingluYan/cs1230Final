#include "rendertask.h"

RenderTask::RenderTask(RayTracer *tracer, int x1, int y1, int x2, int y2) :
    m_tracer(tracer),
    m_x1(x1),
    m_y1(y1),
    m_x2(x2),
    m_y2(y2)
{

}

void RenderTask::run(){
    m_tracer->render(m_x1, m_y1, m_x2, m_y2);
}

