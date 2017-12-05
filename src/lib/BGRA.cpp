#include "BGRA.h"

BGRA BGRA::operator+(const BGRA &that) const {
    return BGRA(this->r + that.r, this->g + that.g, this->b + that.b, this->a + that.a);
}

BGRA BGRA::operator-(const BGRA &that) const {
    return BGRA(this->r - that.r, this->g - that.g, this->b - that.b, this->a - that.a);
}

BGRA BGRA::operator*(const BGRA &that) const {
    return BGRA(this->r * that.r, this->g * that.g, this->b * that.b, this->a * that.a);
}

BGRA BGRA::operator*(float v) const {
    return BGRA(this->r * v, this->g * v, this->b * v, this->a);
}

BGRA BGRA::operator/(const BGRA &that) const {
    return BGRA(this->r / that.r, this->g / that.g, this->b / that.b, this->a / that.a);
}

BGRA BGRA::operator /(const float v) const {
    return BGRA(this->r / v, this->g / v, this->b / v, this->a);
}

bool operator==(const BGRA &c1, const BGRA &c2) {
    return (c1.r == c2.r) && (c1.g == c2.g) && (c1.b == c2.b) && (c1.a == c2.a);
}

bool operator!=(const BGRA &c1, const BGRA &c2) {
    return !operator==(c1, c2);
}

void BGRA::invert() {
    b = 255 - b;
    r = 255 - r;
    g = 255 - g;
}

void BGRA::toGrayScale() {
    int I = 0.3 * r + 0.6 * g + 0.1 * b;
    r = I;
    g = I;
    b = I;
}

int BGRA::grayscaleIntensity() {
    return 0.3 * r + 0.6 * g + 0.1 * b;
}
