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

