#include "flatbottomcurveshape.h"
#include <math.h>

FlatBottomCurveShape::FlatBottomCurveShape() :
    r(0.5f)
{
}


/**
* @param p1: settings.parameter1
* @param p1: settings.parameter2
* @param y: the y coord of the bottom
* @param vertices: the vbo vector
* @param down: if the bottom is facing up or not
**/
int FlatBottomCurveShape::calcBottom(int p1, int p2, float y, std::vector<float>& vertices, bool down) {
    int count = 0;
    float normal_y = down ? -1.0f : 1.0f;
    float draw_dir = down ? -1.0f : 1.0f;
    for (float i = 0; i < p1; i++) {
        float segment_len = 0.5f / static_cast<float>(p1);
        float deg = 360.0f;
        for (int j = 0; j < p2 + 1; j++) {
            deg += draw_dir * 360 / static_cast<float>(p2);
            float rad = deg * M_PI / 180;
            vertices.push_back(i * segment_len * cos(rad));
            vertices.push_back(y);
            vertices.push_back(i * segment_len * sin(rad));
            //add normal
            vertices.push_back(0.0f);
            vertices.push_back(normal_y);
            vertices.push_back(0.0f);

            vertices.push_back((i + 1) * segment_len * cos(rad));
            vertices.push_back(y);
            vertices.push_back((i + 1) * segment_len * sin(rad));
            //add normal
            vertices.push_back(0.0f);
            vertices.push_back(normal_y);
            vertices.push_back(0.0f);

            count += 2;
        }
    }

    return count;
}

