#include "scalefilter.h"
#include <math.h>
#include "Canvas2D.h"
#include <iostream>

ScaleFilter::ScaleFilter()
{
    ScaleFilter(1.f,1.f);
}

ScaleFilter::ScaleFilter(float x, float y) :
    scaleX(x),
    scaleY(y)
{

}

void ScaleFilter::applyFilter(Canvas2D *canvas, int x1, int y1, int x2, int y2) {
    BGRA* pix = canvas->data();
    int w = canvas->width();

    int selectionWidth = x2 - x1 + 1;
    int selectionHeight = y2 - y1 + 1;
//    int selectedPixcount = selectionWidth * selectionHeight;
    int outHeight = static_cast<int>(static_cast<float>(selectionHeight) * scaleY + .5f);
    int outWidth = static_cast<int>(static_cast<float>(selectionWidth) * scaleX + .5f);
//    BGRA* buffer = new BGRA[outHeight * outWidth];
    BGRA* bufferX = new BGRA[outWidth * selectionHeight];

    int rX = static_cast<int>(1 / scaleX);
    int kernelX[2 * rX + 1];
    for (int i = 0; i <= 2*rX; i++) {
        if (i <= rX) {
            kernelX[i] = i + 1;
        } else {
            kernelX[i] = 2 * rX - i + 1;
        }
    }

    int rY = static_cast<int>(1 / scaleY);
    int kernelY[2 * rY + 1];
    for (int i = 0; i <= 2*rY; i++) {
        if (i <= rY) {
            kernelY[i] = i + 1;
        } else {
            kernelY[i] = 2 * rY - i + 1;
        }
    }


    //first scale in x-axis direction
    if (scaleX >= 1) {
        for (int y = y1; y <= y2; y++) {
            for (float x = 0; x < outWidth ; x++) {
                //make sure the index is back mapped to a valid range
                float backMapIdx = std::max(0.f, x1 + x / scaleX + (1.f - scaleX) / (2.f * scaleX));
                backMapIdx = std::min(static_cast<float>(x2), backMapIdx);
                int xL = static_cast<int>(std::floor(backMapIdx));
                int xR = static_cast<int>(std::ceil(backMapIdx));
                int indexL = y * w + xL;
                int indexR = y * w + xR;
                float fract = backMapIdx - std::floor(backMapIdx);
                int outIndex = (y - y1) * outWidth + x;
                bufferX[outIndex].r = lerp(fract, pix[indexL].r, pix[indexR].r);
                bufferX[outIndex].g = lerp(fract, pix[indexL].g, pix[indexR].g);
                bufferX[outIndex].b = lerp(fract, pix[indexL].b, pix[indexR].b);
            }
        }
    } else if (scaleX < 1) {
        for (int y = y1; y <=y2; y++) {
            for (float x = 0; x < outWidth; x++) {
                float backMapIdx = std::max(0.f, x1 + x / scaleX + (1.f - scaleX) / (2.f * scaleX));
                backMapIdx = std::min(static_cast<float>(x2), backMapIdx);
                int leftBound = static_cast<int>(std::roundf(backMapIdx - rX));
                int rightBound = static_cast<int>(std::roundf(backMapIdx + rX));
                leftBound = std::max(leftBound, 0);
                rightBound = std::min(rightBound, x2);
                int outIndex = (y - y1) * outWidth + x;
                float weightSum = 0.f;
                float r = 0;
                float g = 0;
                float b = 0;
                for (int i = leftBound, kernelIdx = 0; i <= rightBound, kernelIdx < 2 * rX; i++, kernelIdx++) {
                    weightSum += static_cast<float>(kernelX[kernelIdx]);
                    r += pix[y * w + i].r * kernelX[kernelIdx];
                    g += pix[y * w + i].g * kernelX[kernelIdx];
                    b += pix[y * w + i].b * kernelX[kernelIdx];
                }
                r /= weightSum;
                g /= weightSum;
                b /= weightSum;

                bufferX[outIndex].r = static_cast<unsigned char>(r);
                bufferX[outIndex].g = static_cast<unsigned char>(g);
                bufferX[outIndex].b = static_cast<unsigned char>(b);
            }
        }
    }

    //then scale in y-axis direction
    BGRA* bufferY = new BGRA[outWidth * outHeight];
    if (scaleY >= 1) {
        for (int x = 0; x < outWidth; x++) {
            for (float y = 0; y < outHeight ; y++) {
                //make sure the index is back mapped to a valid range
                float backMapIdx = std::max(0.f, y / scaleY + (1.f - scaleY) / (2.f * scaleY));
                backMapIdx = std::min(static_cast<float>(selectionHeight - 1), backMapIdx);
                int yL = static_cast<int>(std::floor(backMapIdx));
                int yR = static_cast<int>(std::ceil(backMapIdx));
                int indexL = yL * outWidth + x;
                int indexR = yR * outWidth + x;
                float fract = backMapIdx - std::floor(backMapIdx);
                int outIndex = y * outWidth + x;
                bufferY[outIndex].r = lerp(fract, bufferX[indexL].r, bufferX[indexR].r);
                bufferY[outIndex].g = lerp(fract, bufferX[indexL].g, bufferX[indexR].g);
                bufferY[outIndex].b = lerp(fract, bufferX[indexL].b, bufferX[indexR].b);
            }
        }
    } else if (scaleY < 1) {
        for (int x = 0; x < outWidth; x++) {
            for (float y = 0; y < outHeight; y++) {
                float backMapIdx = std::max(0.f, y / scaleY + (1.f - scaleY) / (2.f * scaleY));
                backMapIdx = std::min(static_cast<float>(selectionHeight - 1), backMapIdx);
                int leftBound = static_cast<int>(std::roundf(backMapIdx - rY));
                int rightBound = static_cast<int>(std::roundf(backMapIdx + rY));
                leftBound = std::max(leftBound, 0);
                rightBound = std::min(rightBound, selectionHeight - 1);
                int outIndex = y * outWidth + x;
                float weightSum = 0.f;
                float r = 0;
                float g = 0;
                float b = 0;
                for (int i = leftBound, kernelIdx = 0; i <= rightBound, kernelIdx < 2 * rY; i++, kernelIdx++) {
                    weightSum += static_cast<float>(kernelY[kernelIdx]);
                    r += bufferX[i * outWidth + x].r * kernelY[kernelIdx];
                    g += bufferX[i * outWidth + x].g * kernelY[kernelIdx];
                    b += bufferX[i * outWidth + x].b * kernelY[kernelIdx];
                }
                r /= weightSum;
                g /= weightSum;
                b /= weightSum;

                bufferY[outIndex].r = static_cast<unsigned char>(r);
                bufferY[outIndex].g = static_cast<unsigned char>(g);
                bufferY[outIndex].b = static_cast<unsigned char>(b);
            }
        }
    }

   canvas->resize(outWidth, outHeight);
   mempcpy(canvas->data(), bufferY, outWidth * outHeight * sizeof(BGRA));

   delete[] bufferX;
   delete[] bufferY;
   canvas->update();
}

float ScaleFilter::lerp(float t, float a, float b) {
    if (t > 1 || t < 0) {
        std::cout << "Error in lerp: invalid t!" << std::endl;
    }
    t = std::max(0.f, t);
    t = std::min(1.0f, t);
    return (1-t) * a + t * b;
}
