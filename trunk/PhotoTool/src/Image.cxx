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

