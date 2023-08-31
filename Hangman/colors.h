#pragma once
#include <ostream>


struct RGBColor {
public:
    int r;
    int g;
    int b;
    RGBColor(int r, int g, int b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    RGBColor() = default;
};

struct HSLColor {
public:
    int h;
    float  s;
    float  l;
};


static float Min(float a, float b) {
    return a <= b ? a : b;
}

static float Max(float a, float b) {
    return a >= b ? a : b;
}

HSLColor RgbToHsl(RGBColor* rgb);