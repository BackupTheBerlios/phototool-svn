
#include "Image.h"

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

