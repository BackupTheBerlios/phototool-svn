
#ifndef IMAGE_H
#define IMAGE_H

#include <wx/wx.h>

class Image : public wxImage 
{
public:
    Image(const wxImage& image) : wxImage(image) { }

    Image ScaleAspect(int width, int height) const;

    Image& RescaleAspect(int width, int height) 
    {
        return *this = ScaleAspect(width, height);
    }

    wxPoint Centered(int width, int height);
};

#endif

