/**
 * PhotoTool is an application for organizing and publishing a collection of
 * digital images. 
 *
 * Copyright (C) 2005  Bryan Bulten (bryan@bulten.ca)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "Image.h"

#include <cmath>

#define MIN_XY(x,y) ((x < y) ? (x) : (y))
#define MIN_XYZ(x,y,z) (MIN_XY(MIN_XY(x,y), z))

#define MAX_XY(x,y) ((x < y) ? (y) : (x))
#define MAX_XYZ(x,y,z) (MAX_XY(MAX_XY(x,y), z))

#define UNDEFINED 1.0

void Pixel::GetHSL(float &h, float &s, float &l)
{
    float r, g, b;
    GetRGB(r, g, b);

    float min = MIN_XYZ(r, g, b),
          max = MAX_XYZ(r, g, b),
          del = max - min;

    // Set luminosity
    l = (max + min) / 2.0;

    if (del == 0.0) {
        // Colour is gray
        h = s = 0;
    } else {
        // Set saturation
        if (l < 0.5) s = del / (max + min);
        else         s = del / (2 - max - min);

        // Set hue
        float delR = (((max - r) / 6.0) + (del / 2.0)) / del;
        float delG = (((max - g) / 6.0) + (del / 2.0)) / del;
        float delB = (((max - b) / 6.0) + (del / 2.0)) / del;

        if (r == max)      h = delB - delG;
        else if (g == max) h = (1 / 3) + delR - delB;
        else if (b == max) h = (2 / 3) + delG - delR;

        if (h < 0) h += 1;
        if (h > 1) h -= 1;
    }
}

float h2rgb(float v1, float v2, float h)
{
    if (h < 0.0) h += 1;
    if (h > 1.0) h -= 1;

    if ((6.0 * h) < 1.0) return v1 + (v2 - v1) * 6.0 * h;
    if ((2.0 * h) < 1.0) return v2;
    if ((3.0 * h) < 2.0) return v1 + (v2 - v1) * ((2.0 / 3.0) - h) * 6.0;

    return v1;
}

void Pixel::SetHSL(float h, float s, float l)
{
    float r, g, b;

    if (s == 0) {
        // Gray scale
        r = g = b = l;
    } else {
        float v1, v2;

        if (l < 0.5) v2 = l * (1.0 + s);
        else         v2 = (l + s) - (s * l);

        v1 = 2 * l - v2;

        r = h2rgb(v1, v2, h + (1.0 / 3.0));
        g = h2rgb(v1, v2, h);
        b = h2rgb(v1, v2, h - (1.0 / 3.0));
    }

    SetRGB(r, g, b);
}

Image Image::ScaleAspect(int width, int height) const
{
    // Retain image aspect ratio
    double aspect = (double)GetHeight() / (double)GetWidth();

    if (aspect < 1.0) {
        height = (int)((double)width * aspect);
    } else {
        width = (int)((double)height * aspect);
    }

    // Scale...
    return Scale(width, height);
}

wxPoint Image::Centered(int width, int height)
{
    return wxPoint((width / 2) - (GetWidth() / 2), 
                   (height / 2) - (GetHeight() / 2));
}

Pixel Image::GetPixel(int x, int y)
{
    return GetPixel(y * GetWidth() + x);
}

Pixel Image::GetPixel(int n)
{
    if (n >= GetWidth() * GetHeight())
        return Pixel();

    return Pixel(GetData() + n * 3);
}

void Image::ConvertToGrayScale()
{
    for(int x = 0; x < GetWidth(); x++) {
        for(int y = 0; y < GetHeight(); y++) {
            Pixel p = GetPixel(x, y);

            // TODO: Which method is better?
#if 0
            float h, s, l;
            p.GetHSL(h, s, l);
            p.SetHSL(h, 0, l);
#endif
            float r, g, b;
            p.GetRGB(r,g,b);
            r = (r + g + b) / 3.0;
            p.SetRGB(r,r,r);
        }
    }
}

void Image::AdjustHSL(int h, int s, int l)
{
#if 0
    for(int x = 0; x < GetWidth(); x++) {
        for(int y = 0; y < GetHeight(); y++) {
            Pixel p = GetPixel(x, y);

            float h_orig, s_orig, l_orig;
            p.GetHSL(h_orig, s_orig, l_orig);

            l_orig += ((float)l / 100.0);
            if (l_orig < 0.0) l_orig += 1.0;
            if (l_orig > 1.0) l_orig -= 1.0;

            p.SetHSL(h_orig, s_orig, l_orig);
        }
    }
#endif
}

void Image::AdjustRGB(int r, int g, int b)
{
    (void)r; (void)g; (void)b;
}

