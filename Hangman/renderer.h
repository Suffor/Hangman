#pragma once

#include <vector>
#include <string>
#include "colors.h"

using namespace std;

class TextImg {
    vector<string> lines = {};

public:

    TextImg();
    TextImg* addLine(string line);
    void render();
};


struct ConsoleColor: public RGBColor, public HSLColor{
    int code;
    ConsoleColor(int code, int r, int g, int b) {
        this->code = code;
        this->r = r;
        this->g = g;
        this->b = b;
        auto hsl = RgbToHsl(this);
        this->h = hsl.h;
        this->s = hsl.s;
        this->l = hsl.l;
    }
};

const ConsoleColor COLORS[] = {
    ConsoleColor(31, 170, 0, 0),
    ConsoleColor(32, 197, 15, 31),
    ConsoleColor(33, 193, 156, 0),
    ConsoleColor(34, 0, 55, 218),
    ConsoleColor(35, 136, 23, 152),
    ConsoleColor(36, 58, 150, 221),
    ConsoleColor(37, 204, 204, 204),
    ConsoleColor(97, 255, 255, 255)
};



struct CharOpacity {
    char code;
    float opacity;
};

const CharOpacity OPACITIES[]{
    CharOpacity{.code = ' ', .opacity = 0.f},
    CharOpacity{.code = '.', .opacity = 0.1f},
    CharOpacity{.code = ':', .opacity = 0.2f},
    CharOpacity{.code = '-', .opacity = 0.3f},
    CharOpacity{.code = '=', .opacity = 0.5f},
    CharOpacity{.code = '+', .opacity = 0.6f},
    CharOpacity{.code = '#', .opacity = 0.8f},
    CharOpacity{.code = '%', .opacity = 0.9f},
    CharOpacity{.code = '@', .opacity = 1.0f}
};


struct RGBChar {
    RGBColor color;
    char character;
};

struct RenderChar {
    int colorCode;
    char character;
};


class AsciiRenderer {

    vector<vector<RGBChar>> lines;
    vector<int> framesize;

public:
    AsciiRenderer();
    AsciiRenderer* clear();
    AsciiRenderer* push(RGBChar text);
    AsciiRenderer* push(RGBColor color);
    AsciiRenderer* push(string text, RGBColor color);
    AsciiRenderer* pushLn(string text, RGBColor color);
    AsciiRenderer* newLine();
    AsciiRenderer* render();
};

RenderChar processChar(RGBChar* input);
