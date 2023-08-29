#include "colors.h"



HSLColor RgbToHsl(RGBColor* rgb) {
    HSLColor hsl;
    float r = (rgb->r / 255.0f);
    float g = (rgb->g / 255.0f);
    float b = (rgb->b / 255.0f);

    float min = Min(Min(r, g), b);
    float max = Max(Max(r, g), b);
    float delta = max - min;

    hsl.l = (max + min) / 2;

    if (delta == 0)
    {
        hsl.h = 0;
        hsl.s = 0.0f;
    }
    else
    {
        hsl.s = (hsl.l <= 0.5) ? (delta / (max + min)) : (delta / (2 - max - min));

        float hue;

        if (r == max)
        {
            hue = ((g - b) / 6) / delta;
        }
        else if (g == max)
        {
            hue = (1.0f / 3) + ((b - r) / 6) / delta;
        }
        else
        {
            hue = (2.0f / 3) + ((r - g) / 6) / delta;
        }

        if (hue < 0)
            hue += 1;
        if (hue > 1)
            hue -= 1;

        hsl.h = (int)(hue * 360);
    }

    return hsl;
}
