#include <iostream>
#include <tuple>
#include <windows.h>
#include "renderer.h"

using namespace std;

TextImg::TextImg() {

}
TextImg* TextImg::addLine(string line) {
    this->lines.push_back(line);
    return this;
}
void TextImg::render() {
    system("cls");

    for (auto i = 0; i < this->lines.size(); i++)               //Konflikt signed unsigned untersuchen
    {
        auto line = this->lines.at(i);
        cout << line << endl;
    }
}



AsciiRenderer::AsciiRenderer()
{

}

AsciiRenderer* AsciiRenderer::clear()
{
    this->lines.clear();
    return this;
}

AsciiRenderer* AsciiRenderer::push(RGBChar text)
{
    auto currentLn = this->lines.size();
    this->lines[currentLn - 1].push_back(text);
    return this;
}

AsciiRenderer* AsciiRenderer::push(RGBColor color)
{
    this->push(RGBChar{ color, NULL });
    return this;
}

AsciiRenderer* AsciiRenderer::push(string text, RGBColor color)
{
    for (size_t i = 0; i < text.length(); i++)
    {
        this->push(RGBChar{ color, text.at(i) });
    }
    return this;
}

AsciiRenderer* AsciiRenderer::pushLn(string text, RGBColor color)
{
    vector<RGBChar> line = vector<RGBChar>(text.size());
    for (size_t i = 0; i < text.length(); i++)
    {
        line[i] = RGBChar{ color, text.at(i) };
    }
    this->lines.push_back(line);
    return this;
}

AsciiRenderer* AsciiRenderer::newLine()
{
    vector<RGBChar> line;
    this->lines.push_back(line);
    return this;
}

AsciiRenderer* AsciiRenderer::render()
{
    vector<string> buffer = vector<string>(Max(this->lines.size(), this->framesize.size()));

    int colorCode = 0;
    for (auto i = 0; i < this->lines.size(); i++) 
    {
        auto line = this->lines.at(i);
        for (size_t j = 0; j < line.size(); j++)
        {
            auto c = processChar(&line.at(j));
            if (c.colorCode != colorCode) {
                buffer[i].append("\033[");
                buffer[i].append(to_string(c.colorCode));
                buffer[i].append("m");
                colorCode = c.colorCode;
            }
            buffer[i].push_back(c.character);
        }
        if (i < this->framesize.size()) {
            for (auto j = line.size(); j < this->framesize.at(i); j++) {
                buffer[i].push_back(' ');
            }
        }
        if (this->framesize.size() > i) {
            this->framesize[i] = line.size();
        }
        else {
            this->framesize.push_back(line.size());
        }
    }

    for (auto j = this->lines.size(); j < this->framesize.size(); j++) {
        for (auto k = 0; k < this->framesize.at(j); k++) {
            buffer[j].push_back(' ');
        }
    }

    while (this->framesize.size() > this->lines.size()) {
        this->framesize.pop_back();
    }

    COORD p = { 0, 0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);

    for (size_t i = 0; i < buffer.size(); i++)
    {
        cout << buffer[i] << endl;
    }

    return this;
}


tuple<const ConsoleColor*, float> findClosest(RGBColor* color) {
    int distSquared = INT_MAX;
    HSLColor hsl = RgbToHsl(color);
    const ConsoleColor* out = &COLORS[0];
    float lerr = 1.0f;
    for (size_t i = 0; i < (sizeof(COLORS) / sizeof(COLORS[0])); i++)
    {
        auto candidate = COLORS[i];
        int ds = hsl.s - candidate.s;
        int dh = hsl.h - candidate.h;

        int currDist = (ds * ds) + (dh * dh);
        if (currDist < distSquared) {
            distSquared = currDist;
            out = &COLORS[i];
            lerr = 1 - Max(candidate.l - hsl.l, 0);
        }
    }
    return {out, lerr};
}

char findCharByOpacity(float opacity) {
    char out = NULL;
    float dist = 1.0f;
    for (size_t i = 0; i < (sizeof(OPACITIES) / sizeof(OPACITIES[0])); i++) {
        auto o = OPACITIES[i];
        auto currentDist = abs(o.opacity - opacity);
        if (currentDist < dist) {
            out = o.code;
            dist = currentDist;
        }
    }   
    return out;
}

RenderChar processChar(RGBChar* input) {
    const ConsoleColor* color;
    float lerr;
    tie(color, lerr) = findClosest(&input->color);

    if (input->character != NULL) {
        return RenderChar{ .colorCode = color->code, .character = input->character };
    }
    char c = findCharByOpacity(lerr);
    return RenderChar{ .colorCode = color->code, .character = c };
}

